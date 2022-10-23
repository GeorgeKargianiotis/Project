#include <vector>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void incremental::incrementalAlgorithm(std::vector<Point_2> &points){

	std::sort(points.begin(), points.end(), utils::cmpPoint2);

	for(auto point : points)
		std::cout << point.hx() << std::endl;	

}