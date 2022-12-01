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
	Polygon_2::Vertex_iterator pointA, pointB;
	for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){
		

		if(i == randomPoint){
			pointA = vertex;
			if(++vertex == polygon.end())
				pointB = polygon.begin();
			else
				pointB = vertex;
				
			std::vector<Point_2> pointsInBox;
			//Fuzzy_iso_box searchBox(Point_d((double)pointA->x(), (double)pointA->y()), Point_d(pointB->x(), pointB->y()));
			Fuzzy_iso_box searchBox(Point_2(pointA->x(), pointA->y()), Point_2(pointB->x(), pointB->y()));
			kdTree.search(std::back_inserter(pointsInBox), searchBox);

			for(Point_2 p : pointsInBox)
				std::cout << p << std::endl;

			break;
		}


		i++;
	}
}

void globalTransitionStep(Polygon_2 &polygon){

}