#include <string>
#include <vector>

#include "../headers/simulated_annealing.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void simulated_annealing::function(Polygon_2 &polygon){
	utils::polygonToPythonArray(polygon);
	std::cout << "Hello from simulated_annealing.cpp" << std::endl;
}