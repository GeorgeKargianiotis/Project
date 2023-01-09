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

void local_search::local_search_algorithm(Polygon_2 &greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold){
	
	int firstpoint = 0, secondpoint = 0, found = 0; // Positions of points for each change we make
	double optimal = DBL_MAX; // New area - Old area to calculate diffirence 
	bool error = false, apply = false; // Indicates whenever a move is invalid, and when a valid move must be applied
	std::vector<Point_2> Points; // Store the chain here, with the corresponding edge
	std::vector<Change> allchanges; // All changes for specific edge stored here
	Change temp; // Resets each individual change
	Polygon_2 newpol = greedypolygon; // Polygon used to test each point change at a time
	double before, after; // Areas stored here

	// Setting Time For Algorithm
	auto start = std::chrono::high_resolution_clock::now();

	srand(time(NULL));

	while (optimal >= threshhold){

		// For every edge, find paths of maximum L points and see if changing them is beneficial	
		for(Polygon_2::Edge_const_iterator edge = greedypolygon.edges().begin(); edge != greedypolygon.edges().end(); edge++){
			
			// Check every consecutive point for potential chains
			for(Polygon_2::Vertex_iterator vertex = greedypolygon.begin(); vertex != greedypolygon.end(); vertex++){
				
				// Add single point to chain, if we still have space
				firstpoint++;
				if (Points.size() < L){
					Points.push_back(*vertex);
				
					// Find the position of the edge end to make the change
					if(found == 0){
						for(Polygon_2::Vertex_iterator vertex = greedypolygon.begin(); vertex != greedypolygon.end(); vertex++){
							secondpoint++;
							if (*vertex == edge->end()){
								found = 1;
								break;
							}
						}
					}
					// Store area before any change and attempt to remove point
					before = greedypolygon.area();
					std::cout << firstpoint << " " << secondpoint << std::endl;

					local_search::changePositionOfPoint(newpol, firstpoint, secondpoint);
					

					// Visibility check, point must be able to "see" every edge
					for(Polygon_2::Edge_const_iterator edge = newpol.edges().begin(); edge != newpol.edges().end(); edge++){
						
						if(!CGAL::do_intersect(Segment_2(edge->start(), *vertex), Segment_2(*vertex, edge->end()))){
							std::cerr << "Visibility error" << std::endl;
							error = true;
							local_search::changePositionOfPoint(newpol, secondpoint, firstpoint);
						}	
					}

					// Invalid move, check next point
					if(error == true){
						secondpoint = 0;
						error = false;
						found = 0;
						continue;
					}

					
					// New polygon must still be simple 
					if(newpol.is_simple()){
						std::cerr << "Simplicity error" << std::endl;
						error = true;
						local_search::changePositionOfPoint(newpol, secondpoint, firstpoint);
					}

					// Invalid move, check next point
					if(error == true){
						secondpoint = 0;
						error = false;
						found = 0;
						continue;
					}
					after = newpol.area();

					
					// Depending on user, determine if the new polygon is bigger or smaller
					// If so, the point and edge are stored for the actual polygon change later
					if (std::string(area).compare("max") == 0){
						if (after - before > 0){
							temp.edge = edge;
							temp.Points.push_back(*vertex);
							apply = true;
						}
						else if (temp.Points.size() > 0){
							Points.pop_back();
							local_search::changePositionOfPoint(newpol, secondpoint, firstpoint);
							if (temp.Points.size() > 0){
								apply = true;
							}
						}
					}
					else if (std::string(area).compare("min") == 0){
						if (before - after > 0){
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
				}
				// Max point reached, add them
				// Changes do not need to be consecutive
				else{
					apply = true;
					if(apply){
						allchanges.push_back(temp);
						Change temp2;
						temp = temp2;
						if (Points.size() != 0){
							Points.clear();
						}
						apply = false;
					}	
				}	
			}
			if(apply){
				allchanges.push_back(temp);
				Change temp2;
				temp = temp2;
				if (Points.size() != 0){
					Points.clear();
				}
				apply = false;
			}	
			firstpoint = 0;
		}
		// After going through every point for a specific edge, apply the changes and update the optimal change	
		newpol = greedypolygon;
		local_search::ApplyChanges(greedypolygon, allchanges);
		
		if (std::string(area).compare("max") == 0){
			optimal = greedypolygon.area() - newpol.area();
		}
		else if (std::string(area).compare("min") == 0){
			optimal = newpol.area() - greedypolygon.area();
		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	//write output
	utils::writeToOutputFile(outFile, Points, newpol, "local_search", area, 0, std::abs(greedypolygon.area()), executionTime.count());
}	

void local_search::ApplyChanges(Polygon_2 &polygon, std::vector<Change> allchanges){
	int first = 0, second = 0;
	// For Every Change, delete/add point in reverse order
	for(auto iter = allchanges.end() - 1; iter != allchanges.begin(); iter--){
		Change mychange = *iter;

		// Position of point to insert
		for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){
			first++;
			if (*vertex == mychange.Points.back()){
				break;
			}
		}

		// Position of Point where the insertion will be made
		for (Polygon_2::Edge_const_iterator edge = polygon.edges().begin(); edge != polygon.edges().end(); edge++){
			second++;
			if(edge->end() == mychange.edge->end()){
				break;
			}		
		}

		local_search::changePositionOfPoint(polygon, first, second);

		first = 0;
		second = 0;
		mychange.Points.pop_back();
	
	}	
}

void local_search::changePositionOfPoint(Polygon_2 &polygon, int indexOfPoint, int indexOfNewPosition){
	
	// indexOfPoint points to the point we currently have and indexOfNewPosition points to the point at the new postiion of insertion

	Point_2 newpoint = Point_2(*(polygon.begin() + indexOfPoint-1));

	//remove point from polygon
	polygon.erase(polygon.begin() + indexOfPoint-1);

	//insert in new position
	polygon.insert(polygon.begin() + indexOfNewPosition-1, newpoint);
	
}