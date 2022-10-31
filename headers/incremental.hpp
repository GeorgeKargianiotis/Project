#ifndef INCREMENTAL_HPP
#define INCREMENTAL_HPP

#include "../headers/cgalConfig.hpp"

#define SORT_BY_X_ASC  "1a"
#define SORT_BY_X_DESC  "1b"
#define SORT_BY_Y_ASC  "2a"
#define SORT_BY_Y_DESC  "2b"

// #define RANDOM_EDGE_SELECTION "1"
// #define MIN_AREA_EDGE_SELECTION "2"
// #define MAX_AREA_EDGE_SELECTION "3"

#define RANDOM_EDGE_SELECTION 1
#define MIN_AREA_EDGE_SELECTION 2
#define MAX_AREA_EDGE_SELECTION 3

namespace incremental {
	void incrementalAlgorithm(std::vector<Point_2> &Points, char *initialization, int edgeSelection, std::ofstream &outFile);
} 

#endif