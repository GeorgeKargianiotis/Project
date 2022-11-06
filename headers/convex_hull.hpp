#ifndef CONVEX_HULL_HPP
#define CONVEX_HULL_HPP

#include "../headers/cgalConfig.hpp"

namespace convex_hull {
	void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points, int edge, std::ofstream &outFile);
} 

#endif