#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "../headers/cgalConfig.hpp"

typedef struct change Change;

namespace local_search {
	void local_search_algorithm(Polygon_2 &greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold);
	void ApplyChanges(Polygon_2 &polygon, std::vector<Change> allchanges);
	void changePositionOfPoint(Polygon_2 &polygon, int indexOfPoint, int indexOfNewPosition);
} 

#endif