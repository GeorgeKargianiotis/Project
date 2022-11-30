#ifndef SIMULATED_ANNEALING_HPP
#define SIMULATED_ANNEALING_HPP 

#include "../headers/cgalConfig.hpp"

namespace simulated_annealing{
	Polygon_2* simulatedAnnealing(std::vector<Point_2> &points, char* annealing, bool max, int L);
	Polygon_2* simulatedAnnealingWithSubdivision(std::vector<Point_2> &points, bool max);
} 

void localTransitionStep(Polygon_2 &polygon, Tree &kdTree);
void globalTransitionStep(Polygon_2 &polygon);

#endif