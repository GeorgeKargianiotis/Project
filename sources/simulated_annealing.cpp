#include <chrono>
#include <string>
#include <vector>
#include <time.h>
#include <CGAL/intersections.h>

#include "../headers/simulated_annealing.hpp"
#include "../headers/incremental.hpp"
#include "../headers/utils.hpp"

Polygon_2* simulated_annealing::simulatedAnnealing(std::vector<Point_2> &points, char* annealing, bool max, int L){

	srand(time(0));

	//get the starting simple polygon
	char initialization[2] = {'1', 'a'};
	Polygon_2 polygon, convexHullPolygon;
	incremental::incrementalAlgorithm(points, initialization, 1, polygon);
	incremental::getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);

	std::cout << "Area before: " << polygon.area() << std::endl;

	double energy = 0, temperature = 1, DE, R = rand() / (RAND_MAX);
	double convexHullArea = convexHullPolygon.area();
	double polygonArea = polygon.area();
	double polygonAreaAfterStep, energyAfterStep;

	if(max)
		energy = points.size() * (1 - polygonArea / convexHullArea);
	else
		energy = points.size() * polygonArea / convexHullArea;

	for(int i = 0; i < L; i++){

		int indexOfFirstPoint;
		double areaRemoved = 0.0, areaAdded = 0.0;

		if(strcmp(annealing, "local") == 0)
			localTransitionStep(polygon, areaRemoved, areaAdded, indexOfFirstPoint);
		else
			globalTransitionStep(polygon);

		polygonAreaAfterStep = polygonArea - areaRemoved + areaAdded;

		//check if step is acceptable
		if(max){
			energyAfterStep = points.size() * (1 - polygonAreaAfterStep / convexHullArea);
			DE = energyAfterStep - energy;
			if(DE > 0 || exp(-DE / temperature) > R)
				energy = energyAfterStep;
			else
				swapTwoPoints(polygon, indexOfFirstPoint); // if step is not acceptable, undo the step 
		}
		else{
			energyAfterStep = points.size() * polygonAreaAfterStep / convexHullArea;
			DE = energyAfterStep - energy;
			if(DE < 0 || exp(-DE / temperature) > R)
				energy = energyAfterStep;
			else
				swapTwoPoints(polygon, indexOfFirstPoint); // if step is not acceptable, undo the step
		}

		//reduce temperature	
		temperature = temperature - 1 / L;

	}

	std::cout << "Area after: " << polygon.area() << std::endl;

	std::cout << "success\n";

	return nullptr;
}

Polygon_2* simulated_annealing::simulatedAnnealingWithSubdivision(std::vector<Point_2> &points, bool max){
	
	return nullptr;
}

void localTransitionStep(Polygon_2 &polygon, double &areaRemoved, double &areaAdded, int &indexOfFirstPoint){

	//create kd-Tree
	Tree kdTree;
	for(Point_2 vertex : polygon.vertices())
		kdTree.insert(vertex);
	kdTree.build();

	bool validPointSwap;
	
	while(1){
		
		//take a random point in polygon to swap
		int randomPointIndex = 1 + (rand() % (polygon.size() - 2));

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

		// std::cout << '[' << p.x() << ',' << p.y() << "]," << '[' << q.x() << ',' << q.y() << "]," << '[' << r.x() << ',' << r.y() << "]," << '[' << s.x() << ',' << s.y() << "]," << '[' << minX << ',' << minY << ']' << std::endl;
		// std::cout << '[' << minX << ',' << minY << "]," << '[' << maxX << ',' << minY << "]," << '[' << maxX << ',' << maxY << "]," << '[' << minX << ',' << maxY << "]," << '[' << minX << ',' << minY << ']' << std::endl;

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

					if(a == q || b == q || c == q || a == r || b == r || c == r)
						continue;

					// the two lines from point in box
					Segment_2 lineA = Segment_2(b, a);
					Segment_2 lineB = Segment_2(a, c);

					pointsInBox.erase(point);

					if(CGAL::do_intersect(line1, lineA) || CGAL::do_intersect(line1, lineB) || CGAL::do_intersect(line2, lineA) || CGAL::do_intersect(line2, lineB))
						validPointSwap = false;

					--vertex;
					break;
				}
			}
			
			if(!validPointSwap)
				break;
		}

		// if a line intersect with one of the new lines, try again
		if(!validPointSwap)
			continue;

		//utils::polygonToPythonArray(polygon);	

		//swap points
		swapTwoPoints(polygon, randomPointIndex);	

		//	calculate the area removed and area add because of swap
		//	if triangle p, q, r has the same orientation as the polygon
		// 	then the area of the triangle is inside the polygon
		//	else it is outside.
		if(polygon.orientation() == triangleOrientation(p, q, r)){
			areaRemoved = CGAL::area(p, q, r);
			areaAdded = CGAL::area(q, r, s);
		}
		else{
			areaRemoved = CGAL::area(q, r, s);
			areaAdded = CGAL::area(p, q, r);
		}

		indexOfFirstPoint = randomPointIndex;

		// utils::polygonToPythonArray(polygon);	
		// if(!polygon.is_simple()){
		// 	std::cout << "Not ok\n";
		// 	exit(1);
		// }
		// else

		break;
	}
}

void swapTwoPoints(Polygon_2 &polygon, int indexOfFirstPoint){

	// Let p, q, r, s be four consecutive points in polygon. We remove point q and place it before s
	// indexOfFirstPoint points to q

	Polygon_2::Vertex_iterator vertex = polygon.begin() + indexOfFirstPoint; 
	Point_2 q = *vertex;

	//remove q point
	polygon.erase(vertex);

	vertex = polygon.begin() + indexOfFirstPoint + 1;

	// add point q after r (or before s)
	polygon.insert(vertex, q);
}

int triangleOrientation(Point_2 &a, Point_2 &b, Point_2 &c){
	int orientation = (b.y() - a.y()) * (c.x() - b.x()) - (b.x() - a.x()) * (c.y() - b.y());
	if(orientation == 0) return 0;
	return orientation < 0 ? 1 : -1;	// 1 for counter-clockwise, -1 for clockwise
}

void globalTransitionStep(Polygon_2 &polygon){
	int x = 0;
}

int maxCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int max = p.x();
	if(q.x() > max)	
		max = q.x();
	if(r.x() > max)
		max = r.x();
	if(s.x() > max)
		max = s.x();
	return max;
}

int maxCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int max = p.y();
	if(q.y() > max)	
		max = q.y();
	if(r.y() > max)
		max = r.y();
	if(s.y() > max)
		max = s.y();
	return max;
}

int minCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int min = p.x();
	if(q.x() < min)	
		min = q.x();
	if(r.x() < min)
		min = r.x();
	if(s.x() < min)
		min = s.x();
	return min;
}

int minCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s){
	int min = p.y();
	if(q.y() < min)	
		min = q.y();
	if(r.y() < min)
		min = r.y();
	if(s.y() < min)
		min = s.y();
	return min;
}