#include <chrono>
#include <string>
#include <vector>
#include <time.h>
#include <CGAL/intersections.h>

#include "../headers/simulated_annealing.hpp"
#include "../headers/incremental.hpp"
#include "../headers/utils.hpp"

Polygon_2* simulated_annealing::simulatedAnnealing(std::vector<Point_2> &points, char* annealing, bool max, int L, double &initialArea, double &finalArea){

	srand(time(0));

	//get the starting simple polygon
	char initialization[2] = {'1', 'a'};
	int edgeSelection; 
	if(max)
		edgeSelection = 3;
	else
		edgeSelection = 2;
	Polygon_2 polygon, convexHullPolygon;
	incremental::incrementalAlgorithm(points, initialization, edgeSelection, polygon);
	incremental::getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);

	initialArea = polygon.area();

	double energy = 0, temperature = 1, DE, R = rand() / (RAND_MAX);
	double convexHullArea = convexHullPolygon.area();
	double polygonArea = polygon.area();
	double changeOfPolygonArea, energyAfterStep;

	//calculate energy
	energy = points.size() * polygonArea / convexHullArea;

	for(int i = 0; i < L; i++){

		int indexOfFirstPoint;	//the index of the point, that randomly choosen to be swapped with its next (for both steps)
		int indexOfNewPosition; //point to be moved, will be inserted before point with this index (only for global step) 

		// take a step
		if(strcmp(annealing, "local") == 0)
			localTransitionStep(polygon, changeOfPolygonArea, indexOfFirstPoint);
		else
			globalTransitionStep(polygon, changeOfPolygonArea, indexOfFirstPoint, indexOfNewPosition);

		// calculate new area
		polygonArea += changeOfPolygonArea;

		//calculate new energy
		energyAfterStep = points.size() * (polygonArea / convexHullArea);
		DE = energyAfterStep - energy;

		//check if step is acceptable
		if((DE > 0 && max) || (DE < 0 && !max) || exp(-DE / temperature > R))
			energy = energyAfterStep;
		else{
			 // if step is not acceptable, undo the step 
			if(strcmp(annealing, "local") == 0)
				swapTwoPoints(polygon, indexOfFirstPoint);
			else
				changePositionOfPoint(polygon, indexOfNewPosition, indexOfFirstPoint);
			polygonArea -= changeOfPolygonArea;
		}

		//reduce temperature	
		temperature = temperature - 1 / L;

	}

	return (new Polygon_2(polygon));
}

void simulated_annealing::getConvexHullPolygonFromPoints(const std::vector<Point_2> &points, int begin, int end, Polygon_2 &convexHullPolygon){
	convexHullPolygon.clear();
	std::vector<Point_2> p;
	CGAL::convex_hull_2(points.begin() + begin, points.begin() + end, std::back_inserter(p));
	for(auto it = p.begin(); it != p.end(); it++)
		convexHullPolygon.push_back(*it);
}

void simulated_annealing::localTransitionStep(Polygon_2 &polygon, double &changeOfPolygonArea, int &indexOfFirstPoint){
	//create kd-Tree
	Tree kdTree;
	for(Point_2 vertex : polygon.vertices())
		kdTree.insert(vertex);
	kdTree.build();

	bool validPointSwap;
	
	while(1){
		
		//take a random point in polygon to swap
		int randomPointIndex = 1 + (rand() % (polygon.size() - 3));

		Point_2 p, q, r, s; // q and r are the points to be exchanged. p is previous to q and s is next to r
		p = polygon[randomPointIndex-1];
		q = polygon[randomPointIndex];
		r = polygon[randomPointIndex+1];
		s = polygon[randomPointIndex+2];

		//find max and min coordianates to form the search box
		int maxX = maxCoordinateX(p, q, r, s);
		int minX = minCoordinateX(p, q, r, s);
		int maxY = maxCoordinateY(p, q, r, s);
		int minY = minCoordinateY(p, q, r, s);

		//find the points of polygon in the box
		std::vector<Point_2> pointsInBox;
		Fuzzy_iso_box searchBox(Point_2(minX, minY), Point_2(maxX, maxY));
		kdTree.search(std::back_inserter(pointsInBox), searchBox);

		// new lines
		Segment_2 line1 = Segment_2(p, r);
		Segment_2 line2 = Segment_2(q, s);

		//checks if the line before p intersects with line q s
		Point_2 t;
		if(randomPointIndex - 2 >= 0)
			t = polygon[randomPointIndex - 2];
		else
			t = polygon[polygon.size() - 1]; 	//if p is the first point in polygon
		Segment_2 lineT = Segment_2(t, p);
		if(CGAL::do_intersect(line2, lineT))
			continue;

		//checks if the line after s intersects with line p r 
		if(randomPointIndex + 3 < polygon.size())
			t = polygon[randomPointIndex + 3];
		else
			t = polygon[0];			//if s is the last point in polygon
		lineT = Segment_2(s, t);
		if(CGAL::do_intersect(line1, lineT))
			continue;

		// if new lines intersect each other try again
		if(CGAL::do_intersect(line1, line2))
			continue;
		
		//check if lines from points in box intersect with new lines
		for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){

			validPointSwap = true;

			for(std::vector<Point_2>::iterator point = pointsInBox.begin(); point != pointsInBox.end(); point++){
				if(*point == *vertex){
					Point_2 a = *vertex;	// point in box
					--vertex;
					Point_2 b = *vertex;	// previous point
					++vertex; 
					++vertex;
					Point_2 c = *vertex;	// next point
					--vertex;

					if(a == q || b == q || c == q || a == r || b == r || c == r)
						continue;

					// the two lines from point in box
					Segment_2 lineA = Segment_2(b, a);
					Segment_2 lineB = Segment_2(a, c);

					pointsInBox.erase(point);

					if(CGAL::do_intersect(line1, lineA) || CGAL::do_intersect(line1, lineB) || CGAL::do_intersect(line2, lineA) || CGAL::do_intersect(line2, lineB))
						validPointSwap = false;

					break;
				}
			}
			
			if(!validPointSwap)
				break;
		}

		// if a line intersect with one of the new lines, try again
		if(!validPointSwap)
			continue;

		//swap points
		swapTwoPoints(polygon, randomPointIndex);	

		double areaRemoved, areaAdded;

		/*
			calculate the area removed and area add because of swap
			if triangle p, q, r has the same orientation as the polygon
		 	then the area of the triangle is inside the polygon
			else it is outside.
		*/
		if(polygon.orientation() == triangleOrientation(p, q, r)){
			areaRemoved = CGAL::area(p, q, r);
			areaAdded = CGAL::area(q, r, s);
		}
		else{
			areaRemoved = CGAL::area(q, r, s);
			areaAdded = CGAL::area(p, q, r);
		}

		changeOfPolygonArea = areaAdded - areaRemoved;

		indexOfFirstPoint = randomPointIndex;

		break;
	}
}

void simulated_annealing::globalTransitionStep(Polygon_2 &polygon, double &changeOfPolygonArea, int &indexOfPoint, int &indexOfNewPosition){

	/*
		let q be the point to change position in the polygon
		let r and p be the points before and after q 
		let s and t be the points the q will be placed in between 
		indexOfPoint is the index of q
		indexOfNewPlace is the index of t
	*/

	while(1){

		// random pick a point to swap place
		indexOfPoint = 1 + (rand() % (polygon.size() - 1));

		// random pick a new place
		indexOfNewPosition = 1 + (rand() % (polygon.size() - 1));

		if(abs(indexOfPoint - indexOfNewPosition) < 2)
			continue;

		Point_2 q = *(polygon.begin() + indexOfPoint);
		Point_2 r = *(polygon.begin() + indexOfPoint - 1);
		Point_2 p = *(polygon.begin() + indexOfPoint + 1);
		Point_2 s = *(polygon.begin() + indexOfNewPosition - 1);	
		Point_2 t = *(polygon.begin() + indexOfNewPosition);	

		/*
		 because we temporarily remove the point from polygon, before
		 placing it to the new position, the size of polygon decrease
		 by 1, so all indexes decrease by one. That holds only when
		 the point to be move, is before the newPosition
		*/
		if(indexOfPoint < indexOfNewPosition)
			indexOfNewPosition--;

		// make the change
		changePositionOfPoint(polygon, indexOfPoint, indexOfNewPosition);

		// if the change of position was not valid, we undo the change
		if(!polygon.is_simple()){

			changePositionOfPoint(polygon, indexOfNewPosition, indexOfPoint);
			continue;
		}

		// calculate the change of area
		changeOfPolygonArea = CGAL::area(s, q, t) - CGAL::area(r, q, p); 
		
		break;
	}
}

void simulated_annealing::swapTwoPoints(Polygon_2 &polygon, int indexOfFirstPoint){

	// Let p, q, r, s be four consecutive points in polygon. We remove point q and place it before s
	Polygon_2::Vertex_iterator vertex = polygon.begin() + indexOfFirstPoint; 
	Point_2 q = Point_2(*vertex);

	//remove q point
	polygon.erase(vertex);

	vertex = polygon.begin() + indexOfFirstPoint + 1;

	// add point q after r (or before s)
	polygon.insert(vertex, q);
}

void simulated_annealing::changePositionOfPoint(Polygon_2 &polygon, int &indexOfPoint, int &indexOfNewPosition){

	// Let r, q, p be three consecutive points. We remove point q and place it in between points s and t
	Point_2 q = Point_2(*(polygon.begin() + indexOfPoint));

	//remove point q from polygon
	polygon.erase(polygon.begin() + indexOfPoint);

	//insert q between s and t
	polygon.insert(polygon.begin() + indexOfNewPosition, q);
}

int simulated_annealing::triangleOrientation(Point_2 &a, Point_2 &b, Point_2 &c){
	int orientation = (b.y() - a.y()) * (c.x() - b.x()) - (b.x() - a.x()) * (c.y() - b.y());
	if(orientation == 0) return 0;
	return orientation < 0 ? 1 : -1;	// 1 for counter-clockwise, -1 for clockwise
}

int simulated_annealing::maxCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int max = p.x();
	if(q.x() > max)	
		max = q.x();
	if(r.x() > max)
		max = r.x();
	if(s.x() > max)
		max = s.x();
	return max;
}

int simulated_annealing::maxCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int max = p.y();
	if(q.y() > max)	
		max = q.y();
	if(r.y() > max)
		max = r.y();
	if(s.y() > max)
		max = s.y();
	return max;
}

int simulated_annealing::minCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int min = p.x();
	if(q.x() < min)	
		min = q.x();
	if(r.x() < min)
		min = r.x();
	if(s.x() < min)
		min = s.x();
	return min;
}

int simulated_annealing::minCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int min = p.y();
	if(q.y() < min)	
		min = q.y();
	if(r.y() < min)
		min = r.y();
	if(s.y() < min)
		min = s.y();
	return min;
}