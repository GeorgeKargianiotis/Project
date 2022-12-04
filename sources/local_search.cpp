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
	double optimal = DBL_MAX;
	bool error = false, apply = false;
	std::vector<Point_2> Points;
	std::vector<Change> allchanges;
	Polygon_2 old;
	Change temp;
	Polygon_2 newpol;
	old = greedypolygon;
	newpol = old;

	// Setting Time For Algorithm
	auto start = std::chrono::high_resolution_clock::now();

	srand(time(NULL));

	while (optimal >= threshhold){

		//For every edge, find paths of maximum L points and see if changing them is beneficial	
		for(Polygon_2::Edge_const_iterator edge = old.edges().begin(); edge != old.edges().end(); edge++){
			
			for(Polygon_2::Vertex_iterator vertex = old.begin(); vertex != old.end(); vertex++){
				//Add single point to chain, if we still have space
				if (Points.size() < L){
					Points.push_back(*vertex);
				
					// Make the change and test the new polygon
					newpol.erase(vertex);
					if (local_search::InsertPointForLS(newpol, edge->start(), edge->end(), *vertex) == 0){
						std::cout << "Testing Point" << std::endl;
					}

					// Visibility check, point must be able to "see" every edge
					for(Polygon_2::Edge_const_iterator edge = newpol.edges().begin(); edge != newpol.edges().end(); edge++){
						if(!CGAL::do_intersect(Segment_2(edge->start(), *vertex), Segment_2(*vertex, edge->end())))
							std::cerr << "Visibility error" << std::endl;
							error = true;
					}

					if(!newpol.is_simple()){
						std::cerr << "Simplicity error" << std::endl;
						error = true;
					}

					if(error){
						error = false;
						// No Point  in chain, so no change that needs to be done
						if (Points.size() == 0){
							newpol = old;
							continue;
						}	
					}

					// Depending on user, determine if the new polygon is bigger or smaller
					if (std::string(area).compare("max") == 0){
						if (newpol.area() - old.area() > 0){
							temp.edge = edge;
							temp.Points.push_back(*vertex);
							apply = true;
						}
						else if (temp.Points.size() > 0){
							Points.pop_back();
							apply = true;
						}
					}
					else if (std::string(area).compare("min") == 0){
						if (old.area() - newpol.area() > 0){
							temp.edge = edge;
							temp.Points.push_back(*vertex);
							apply = true;
						}
						else if (temp.Points.size() > 0){
							Points.pop_back();
							apply = true;
						}
					}
					else{
						std::cerr << "Wrong arguments given! " << std::endl;
						exit(EXIT_FAILURE);
					}
					// We appllied the change, so we need to keep working on new 
					old = newpol;
				}	
			}
			if(apply){
				allchanges.push_back(temp);
				Change temp2;
				temp = temp2;
				Points.clear();
				apply = false;
			}	
		}
	// After going through every point for a specific edge, apply the changes and update the optimal change	
	newpol = old;	
	local_search::ApplyChanges(old, allchanges);
	if (std::string(area).compare("max") == 0){
		optimal = old.area() - newpol.area();
	}
	else if (std::string(area).compare("min") == 0){
		optimal = newpol.area() - old.area();
	}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	//write output
	utils::writeToOutputFile(outFile, Points, old, greedypolygon, 0, std::abs(old.area()), executionTime.count(), "none");
	std::cout << "Success" << std::endl;
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

void local_search::ApplyChanges(Polygon_2 &polygon, std::vector<Change> allchanges){
	//Insert First One with the given edge, then insert the other in reverse
	for(auto iter = allchanges.begin(); iter != allchanges.end(); iter++){
		Change mychange = *iter;
		if (local_search::InsertPointForLS(polygon, mychange.edge->start(), mychange.edge->end(), mychange.Points.back()) == 0){
			std::cout << "Testing Point" << std::endl;
		}

		mychange.Points.pop_back();

		for (auto iter=mychange.Points.end(); iter!=mychange.Points.begin(); iter--){
			for (Polygon_2::Edge_const_iterator edge = polygon.edges().begin(); edge != polygon.edges().end(); edge++){
				if(edge->start() == *iter){
					if (local_search::InsertPointForLS(polygon, edge->start(), edge->end(), *iter) == 0){
						std::cout << "Testing Point" << std::endl;
					}
				}		
			}
		}	
	}	
}



