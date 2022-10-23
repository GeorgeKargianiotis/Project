#ifndef INCREMENTAL_HPP
#define INCREMENTAL_HPP

#include "../headers/cgalConfig.hpp"

#define SORT_BY_X_ASC  "1a"
#define SORT_BY_X_DESC  "1b"
#define SORT_BY_Y_ASC  "2a"
#define SORT_BY_Y_DESC  "2b"

namespace incremental {
	void incrementalAlgorithm(std::vector<Point_2> &Points, char *initialization);
} 

#endif