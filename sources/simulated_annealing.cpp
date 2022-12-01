#include <chrono>
#include <string>
#include <vector>
#include <time.h>

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

	double energy = 0;

	if(max)
		energy = points.size() * (1 - polygon.area() / convexHullPolygon.area());
	else
		energy = points.size() * polygon.area() / convexHullPolygon.area();

	for(int i = 0; i < L; i++){

		if(strcmp(annealing, "local") == 0){
			Tree kdTree;
			for(Point_2 point : points)
				kdTree.insert(point);
			kdTree.build();

			localTransitionStep(polygon, kdTree);
		}
		else 
			globalTransitionStep(polygon);


	}

	return nullptr;
}

Polygon_2* simulated_annealing::simulatedAnnealingWithSubdivision(std::vector<Point_2> &points, bool max){
	
	return nullptr;
}

void localTransitionStep(Polygon_2 &polygon, Tree &kdTree){
	bool validPointSwap;
	
	while(1){

		validPointSwap = true;

		//take a random point in polygon to swap
		int randomPoint = 1 + (rand() % (polygon.size() - 2));

		std::cout << "random point : " << randomPoint << std::endl;

		int i = randomPoint;

		Point_2 p, q, r, s; // q and r are the points to be exchanged. p is previous to q and s is next to r
		p = polygon[i-1];
		q = polygon[i];
		r = polygon[i+1];
		s = polygon[i+2];

		int maxX = maxCoordinateX(p, q, r, s);
		int minX = minCoordinateX(p, q, r, s);
		int maxY = maxCoordinateY(p, q, r, s);
		int minY = minCoordinateY(p, q, r, s);
		
		std::vector<Point_2> pointsInBox;
		Fuzzy_iso_box searchBox(Point_2(minX, minY), Point_2(maxX, maxY));
		kdTree.search(std::back_inserter(pointsInBox), searchBox);

		// new lines
		Segment_2 line1 = Segment_2(p, r);
		Segment_2 line2 = Segment_2(q, s);

		if(CGAL::do_intersect(line1, line2))
			continue;
		
		for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){

			for(std::vector<Point_2>::iterator point = pointsInBox.begin(); point != pointsInBox.end(); point++)
				if(*point == *vertex){
					Point_2 a = *vertex;	// point in box
					--vertex;
					Point_2 b = *vertex;	// previous point
					++vertex; 
					++vertex;
					Point_2 c = *vertex;	// next point

					// the two lines from point in box
					Segment_2 lineA = Segment_2(b, a);
					Segment_2 lineB = Segment_2(a, c);

					pointsInBox.erase(point);

					if(CGAL::do_intersect(line1, lineA) || CGAL::do_intersect(line1, lineB) || CGAL::do_intersect(line2, lineA) || CGAL::do_intersect(line2, lineB))
						validPointSwap = false;

					--vertex;
					break;
				}
			
			if(!validPointSwap)
				break;

			//swap points in polygon and return;
		}

		if(!validPointSwap)
			continue;
	}
	
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