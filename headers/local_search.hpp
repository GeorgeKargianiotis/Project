#ifndef LOCAL_SEARCH_HPP
#define LOCAL_SEARCH_HPP

#include "../headers/cgalConfig.hpp"

typedef struct change Change;

namespace local_search {
	void local_search_algorithm(Polygon_2 greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold);
	int InsertPointForLS(Polygon_2 &polygon, const Point_2 &begin, const Point_2 &end, Point_2 newPoint);
	void ApplyChanges(Polygon_2 &polygon, std::vector<Change> allchanges);
	void swapTwoPoints(Polygon_2 &polygon, int indexOfFirstPoint, int indexOfSecondPoint);
	void changePositionOfPoint(Polygon_2 &polygon, int &indexOfPoint, int &indexOfNewPosition);
} 

#endif