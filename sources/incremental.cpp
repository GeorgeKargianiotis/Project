#include <vector>
#include <string>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void incremental::incrementalAlgorithm(std::vector<Point_2> &points, char *initialization){

	if(std::string(initialization).compare("1a") == 0)
		std::sort(points.begin(), points.end(), utils::cmp1aPoint2);
	else if(std::string(initialization).compare("1b") == 0)
		std::sort(points.begin(), points.end(), utils::cmp1bPoint2);
	else if(std::string(initialization).compare("2a") == 0)
		std::sort(points.begin(), points.end(), utils::cmp2aPoint2);
	else if(std::string(initialization).compare("2b") == 0)
		std::sort(points.begin(), points.end(), utils::cmp2bPoint2);

	std::cout << initialization << std::endl; 
	for(auto point : points)
		std::cout << point << std::endl;	

}