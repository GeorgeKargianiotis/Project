#ifndef SIMULATED_ANNEALING_HPP
#define SIMULATED_ANNEALING_HPP 

#include "../headers/cgalConfig.hpp"

namespace simulated_annealing{
	Polygon_2* simulatedAnnealing(std::vector<Point_2> &points, char* annealing, bool max, int L);
	Polygon_2* simulatedAnnealingWithSubdivision(std::vector<Point_2> &points, bool max);
} 

void localTransitionStep(Polygon_2 &polygon, Tree &kdTree);
void globalTransitionStep(Polygon_2 &polygon);

int maxCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);
int maxCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);
int minCoordinateX(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);
int minCoordinateY(Point_2 &p, Point_2 &q, Point_2 &r, Point_2 &s);

#endif