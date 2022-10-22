#include <vector>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"

void incremental::incrementalAlgorithm(std::vector<Point_2> &Points){

	for(auto point : Points)
		std::cout << point << std::endl;	

}