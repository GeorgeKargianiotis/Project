#include <string>
#include <vector>

#include "../headers/simulated_annealing.hpp"
#include "../headers/incremental.hpp"
#include "../headers/utils.hpp"

Polygon_2* simulated_annealing::simulatedAnnealing(std::vector<Point_2> &points, char* annealing, bool max, int L){

	//get the starting simple polygon
	char initialization[2] = {'2', 'a'};
	Polygon_2 polygon, convexHullPolygon;
	incremental::incrementalAlgorithm(points, initialization, 2, polygon);
	//incremental::getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);

	double energy = 0;

	if(max)
		energy = points.size() * (1 - polygon.area() / convexHullPolygon.area());
	else
		energy = points.size() * polygon.area() / convexHullPolygon.area();

	return nullptr;
}

Polygon_2* simulated_annealing::simulatedAnnealingWithSubdivision(std::vector<Point_2> &points, bool max){
	
	return nullptr;
}

void localTransitionStep(){

}

void globalTransitionStep(){

}