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

<<<<<<< HEAD
void local_search::local_search_algorithm(Polygon_2 &greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold){
	
	int firstpoint = 0, secondpoint = 0, found = 0; // Positions of points for each change we make
	double optimal = DBL_MAX; // New area - Old area to calculate diffirence 
	bool error = false, apply = false; // Indicates whenever a move is invalid, and when a valid move must be applied
	std::vector<Point_2> Points; // Store the chain here, with the corresponding edge
	std::vector<Change> allchanges; // All changes for specific edge stored here
	Change temp; // Resets each individual change
	Polygon_2 newpol = greedypolygon; // Polygon used to test each point change at a time
	double before, after; // Areas stored here
=======
void local_search::local_search_algorithm(Polygon_2 greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold){
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
>>>>>>> 8a5ddaf3be06ee384c9d15cafb5df0f4d30a9f88

	// Setting Time For Algorithm
	auto start = std::chrono::high_resolution_clock::now();

	srand(time(NULL));

	while (optimal >= threshhold){

<<<<<<< HEAD
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
=======
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
>>>>>>> 8a5ddaf3be06ee384c9d15cafb5df0f4d30a9f88
							temp.edge = edge;
							temp.Points.push_back(*vertex);
							apply = true;
						}
						else if (temp.Points.size() > 0){
							Points.pop_back();
<<<<<<< HEAD
							local_search::changePositionOfPoint(newpol, secondpoint, firstpoint);
							if (temp.Points.size() > 0){
								apply = true;
							}
						}
					}
					else if (std::string(area).compare("min") == 0){
						if (before - after > 0){
=======
							apply = true;
						}
					}
					else if (std::string(area).compare("min") == 0){
						if (old.area() - newpol.area() > 0){
>>>>>>> 8a5ddaf3be06ee384c9d15cafb5df0f4d30a9f88
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
<<<<<<< HEAD
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
=======
					old = newpol;
>>>>>>> 8a5ddaf3be06ee384c9d15cafb5df0f4d30a9f88
				}	
			}
			if(apply){
				allchanges.push_back(temp);
				Change temp2;
				temp = temp2;
<<<<<<< HEAD
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
=======
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
>>>>>>> 8a5ddaf3be06ee384c9d15cafb5df0f4d30a9f88
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	//write output
<<<<<<< HEAD
	utils::writeToOutputFile(outFile, Points, newpol, greedypolygon, 0, std::abs(greedypolygon.area()), executionTime.count(), "none");
	std::cout << "Success" << std::endl;
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


=======
	//utils::writeToOutputFile(outFile, Points, old, greedypolygon, 0, std::abs(old.area()), executionTime.count(), "none");
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
>>>>>>> 8a5ddaf3be06ee384c9d15cafb5df0f4d30a9f88
