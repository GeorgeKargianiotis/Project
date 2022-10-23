#include <vector>

#include "../headers/onion.hpp"
#include "../headers/cgalConfig.hpp"

void onion::onionAlgorithm(std::vector<Point_2> &Points){

	for(auto point : Points)
		std::cout << point << std::endl;	

}