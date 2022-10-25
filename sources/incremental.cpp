#include <vector>
#include <string>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void incremental::incrementalAlgorithm(std::vector<Point_2> &points, char *initialization){

	//order by x ascending
	if(std::string(initialization).compare(SORT_BY_X_ASC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp1aPoint2);
	//order by x descending 
	else if(std::string(initialization).compare(SORT_BY_X_DESC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp1bPoint2);
	//order by y ascending
	else if(std::string(initialization).compare(SORT_BY_Y_ASC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp2aPoint2);
	//order by y descending
	else if(std::string(initialization).compare(SORT_BY_Y_DESC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp2bPoint2);

	Polygon_2 polygon;			
	
	// initialize polygon with the 3 first sorted points
	polygon.push_back(points[0]);
	polygon.push_back(points[1]);
	polygon.push_back(points[2]);

	int i = 0;
	while(CGAL::collinear(points[i], points[i+1], points[i+2])){
		polygon.push_back(points[i+3]);
		i++;
	}

	for(const Segment_2& edge : polygon.edges())
		std::cout << edge << std::endl;

	// utils::polygonToPythonArray(polygon);
	// utils::vectorToPythonArray(points);

	// for(int i = 3; i < points.size(); i++){

	// }

}
