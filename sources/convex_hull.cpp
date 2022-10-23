#include <vector>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points){

	for(auto point : Points)
		std::cout << point << std::endl;	

}