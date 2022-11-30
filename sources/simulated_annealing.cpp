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
	//take a random point in polygon to swap
	int randomPoint = rand() % polygon.size();

	int i = 0;
	for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){

		if(i == randomPoint)

	}
}

void globalTransitionStep(Polygon_2 &polygon){

}