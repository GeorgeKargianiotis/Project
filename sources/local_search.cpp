#include <vector>
#include <string>
#include <functional>
#include <cstdlib>
#include <time.h>
#include <chrono>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"
#include "../headers/local_search.hpp"

struct change{
	std::vector<Point_2> Points;
	Polygon_2::Edge_const_iterator edge;
};

void local_search_algorithm(Polygon_2 greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold){
	// Amount of points we can switch
	double optimal;
	std::vector<Point_2> Points;
	std::vector<Point_2> Examined;
	std::vector<Change> allchanges;
	Polygon_2 old;
	Polygon_2 newpol;
	
	old = greedypolygon;
	newpol = old;

	while (optimal >= threshhold){
		for(Polygon_2::Edge_const_iterator edge = old.edges().begin(); edge != old.edges().end(); edge++){
			//FIRST THOUGHT, RUN THROUGH EDGES AND ADD POINTS THAT WAY
			//Use Examined Vector for searches
			for(Polygon_2::Vertex_iterator vertex = old.begin(); vertex != old.end(); vertex++){
				//Add single point to chain, if we still have space
				if (Points.size() < L){
					Points.push_back(*vertex);
				}

				if (local_search::InsertPointForLS(newpol, edge->start(), edge->end(), *vertex) == 0){
					std::cout << "Testing Point" << std::endl;
				}

				// Visibility check, point must be able to "see" every edge
				for(Polygon_2::Edge_const_iterator edge = newpol.edges().begin(); edge != newpol.edges().end(); edge++){
					if(!CGAL::do_intersect(Segment_2(edge->start(), *vertex), Segment_2(*vertex, edge->end())))
						std::cerr << "Visibility error" << std::endl;
				}

				//We have a chain, switch edges and check simplicity
				//utils::switch(...)
				//We need start and end points of edge
				//Move points in reverse order (end point of chain then start point) 
				if (std::string(area).compare("max") == 0){
					Points.push_back(edge->start());
				}
				//SECOND THOUGHT, RUN THROUGH VERTICES AND ONLY KEEP EDGES FOR INITIAL SEARCH 
				else if (std::string(area).compare("min") == 0){
					
				}
				else{
					std::cerr << "Wrong arguments given! " << std::endl;
					exit(EXIT_FAILURE);
				}
			}
		}
	}
}	

int local_search::InsertPointForLS(Polygon_2 &polygon, const Point_2 &begin, const Point_2 &end, Point_2 newPoint){

	for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){
		if(*vertex == begin){
			vertex++;
			if(vertex == polygon.end()){
				polygon.insert(polygon.begin(), newPoint);
				return 1;
			}
			if(*vertex == end){
				polygon.insert(vertex, newPoint);
				return 1;
			}
			vertex--;
		}
		 else if(*vertex == end){
			vertex++;
			if(vertex == polygon.end()){
				polygon.insert(polygon.begin(), newPoint);
				return 1;
			}
			if(*vertex == begin){
				polygon.insert(--vertex, newPoint);
				return 1;
			}
			vertex--;
		 }
	}

	std::cout << "Problem inserting point " << newPoint << std::endl;
	return 0;
}

/*
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

