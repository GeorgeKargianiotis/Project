#include <vector>
#include <string>
#include <functional>
#include <cstdlib>
#include <time.h>
#include <chrono>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void local_search_algorithm(Polygon_2 greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold){
	// Amount of points we can switch
	double optimal;

	while (optimal >= threshhold){
		for(Polygon_2::Edge_const_iterator edge = greedypolygon.edges().begin(); edge != greedypolygon.edges().end(); edge++){
			if (std::string(area).compare("max") == 0){
				
			}
			else if (std::string(area).compare("min") == 0){

			}
			else{

			}
		}
	}

	/*

for every path V of length ≤ k do
if V moving to e increases area and retains simplicity then
list T ← [e, V]
end if
end for
end for
Apply all changes in T to S
Keep best solution S
′
; ∆A ← Area(S
′
) − Area(S)
end while*/
}
