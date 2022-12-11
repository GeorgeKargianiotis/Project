#include <vector>
#include <string>
#include <functional>
#include <cstdlib>
#include <time.h>
#include <chrono>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

typedef std::vector<Segment_2> Segments; 

int insertNewPointToPolygonCH(Polygon_2 &polygon, const Point_2 &begin, const Point_2 &end, Point_2 newPoint);

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points, int edge, std::ofstream &outFile){	
<<<<<<< HEAD

	auto start = std::chrono::high_resolution_clock::now();

	srand(time(0));

	Polygon_2 mypolygon, polygonchain; // Initial polygon to be used in convex_hull
	Segments myseg; // Edges stored here
	Segment_2 chosen;
=======

	auto start = std::chrono::high_resolution_clock::now();

	srand(time(NULL));

	Polygon_2 mypolygon, polygonchain; // Initial polygon to be used in convex_hull (polygon chain)
	Segment_2 edgeToBeReplaced; // Segment to be replaced (broken into two new ones)
>>>>>>> 8bbd801d13d069bc12b6da8c50c58b79f3f02e97
	// Used to store points not yet included in polygon, needs to be empty in the end, closest is the closest point to each edge (according to myseg)
	std::vector<Point_2> RemainingPoints, ClosestPoints;
	std::vector<double> areav; // Areas formed, needed for cases 2 and 3

	double distance; // Needed for the point we are about to add
	// Initialising distances and areas, needed for edge-point selection
	double mindistance = DBL_MAX;
	double minarea = DBL_MAX;
	double maxarea = DBL_MIN;
	double newmin = DBL_MIN; 
	double newmax = DBL_MAX;
	

	// Point selected to add to the chain
	Point_2 toadd, newp;
	// Segments that provide the min and max area respectively
	Segment_2 minemb, maxemb;
	int random, index = 0, i = 0, defect = 0, index2 = 0; // Indexes to find edges, defect is in case we have an "external" point 
	double area; // Area calculated each time
	
	// Add all points to new vector
	for (auto iter=Points.begin(); iter!=Points.end(); iter++)
		RemainingPoints.push_back(*iter);
		
	// Same for polygon
	for (auto iter=Points.begin(); iter!=Points.end(); iter++)
		mypolygon.push_back(*iter);

	const Polygon_2::Vertices& range = mypolygon.vertices();
 	std::vector<Point_2> result;

	polygonchain.clear();
	// Using all given points to create initial chain
	CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(result));

	// After we get the convex hull, create the chain with the points chosen, and remove them from the point vector (they have now been used)
 	for (auto it = result.begin(); it!= result.end(); it++){
 		polygonchain.push_back(*it);
		
		RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), *it), RemainingPoints.end());
	}	

	// From each edge, find nearest visible point INSIDE THE CHAIN and add it to polygon	
	// 3 ways: random, min and max area

	while (RemainingPoints.size() != 0){
		
		for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
			Segment_2 temp = *edge;
			for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end(); it++){
				distance = CGAL::squared_distance(temp, *it);

				// Keep the one closest to the edge
				if (distance < mindistance){
					mindistance = distance;
					toadd = *it;
				}
			}
			// Make the entry: Each edge now has a matching closest point in this vector
			ClosestPoints.push_back(toadd);	
			mindistance = DBL_MAX;
		}

		// Random Pair Selected
		if (edge == 1){
			while(true){
				
				random = rand() % ClosestPoints.size();
				newp = ClosestPoints.at(random);

				// Visibility check, point must be able to "see" every edge
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!CGAL::do_intersect(Segment_2(edge->start(), newp), Segment_2(newp, edge->end())))
						std::cerr << "Visibility error" << std::endl;
				}

				// Insert the new point, but first find the correct edge inside the existing polygon
				for (Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if (index == random){
						edgeToBeReplaced = *edge;
						index = 0;
						break;
					}
					index++;
				}
					
<<<<<<< HEAD
			// Connect point with a random edge, create new edges and remove the point, old edge is also removed
			random = rand() % ClosestPoints.size();
			chosen = myseg.at(random);
			newp = ClosestPoints.at(random);

			myseg.push_back(Segment_2 (chosen.source(), newp));
			myseg.push_back(Segment_2 (newp, chosen.target()));
			myseg.erase(std::remove(myseg.begin(), myseg.end(), chosen), myseg.end());
			RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
			
=======
				if(insertNewPointToPolygonCH(polygonchain, edgeToBeReplaced.start(), edgeToBeReplaced.end(), newp) == 0){
					continue;
				}
>>>>>>> 8bbd801d13d069bc12b6da8c50c58b79f3f02e97

				// We need to make sure that no other point is excluded
				for (auto it = RemainingPoints.begin(); it != RemainingPoints.end(); ++it){
					if(CGAL::bounded_side_2(polygonchain.begin(), polygonchain.end(), *it, K()) == CGAL::ON_UNBOUNDED_SIDE){
						std::cout << "Point Left Out" << *it << std::endl;
						defect = 1;
						for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
							if (*vertex == newp){
								polygonchain.erase(vertex);
								break;
							}
						}
						
						break;	
					}
				}
				if (defect == 1){
					continue;
				}
				break;
			}
			// Insertion Done, Point added
			RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
				
			ClosestPoints.clear();
<<<<<<< HEAD
			// ΤΟ DO, VISIBILITY BEFORE INSERTION
			// CHANGE INTERSECTION WITH DO_INTERSECT
			// CLOCKWISE VS COUNTERCLOCKWISE ROTATION OF CONVEX HULL
			// FOR OUTSIDE POINTS: DO_INERSECT POINT LEFT OUT WITH 2 NEW EDGES AND OLD ONE
			for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
				if(!isVisibleEdgeCH(polygonchain, edge, newp))
					std::cerr << "Visibility error" << std::endl;
			}
			std::cout << "Conveeeex" << std::endl;
=======
>>>>>>> 8bbd801d13d069bc12b6da8c50c58b79f3f02e97

			defect = 0;
		}	
		// Min area selection
		else if (edge == 2){
			// Myseg and closest points have the same size, find area for each pair, keep them stored
			for (Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
				area = CGAL::area(ClosestPoints.at(i), edge->source(), edge->target());
				areav.push_back(area);
				i++;
			}

			i = 0;

			while(true){
				// Find areas and keep them uptaded
				// If we have external points or visibility errors, look for another pair with area different than the defective one
				for (int j = 0; j < areav.size(); j++){
					if(areav.at(j) < minarea && areav.at(j) > newmin){
						minarea = areav.at(j);
						index = j;
						newp = ClosestPoints.at(j);
					}
				}

				newmin = minarea;
				
				// Visibility check, point must be able to "see" every edge
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!CGAL::do_intersect(Segment_2(edge->start(), newp), Segment_2(newp, edge->end())))
						std::cerr << "Visibility error" << std::endl;
				}

				// Insert the new point
				for (Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if (index2 == index){
						edgeToBeReplaced = *edge;
						index2 = 0;
						break;
					}
					index2++;
				}
					
				if(insertNewPointToPolygonCH(polygonchain, edgeToBeReplaced.start(), edgeToBeReplaced.end(), newp) == 0){
					areav.clear();
					continue;
				}

				for (auto it = RemainingPoints.begin(); it != RemainingPoints.end(); ++it){
					if(CGAL::bounded_side_2(polygonchain.begin(), polygonchain.end(), *it, K()) == CGAL::ON_UNBOUNDED_SIDE){
						std::cout << "Point Left Out" << *it << std::endl;
						defect = 1;
						for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
							if (*vertex == newp){
								polygonchain.erase(vertex);
								break;
							}
						}
						
						break;	
					}
				}
				if (defect == 1){
					areav.clear();
					continue;
				}
				break;
			}
			// Clear vector and update areas
			areav.clear();
			newmin = DBL_MIN;

			RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
			std::cout << "Erasing Point " << newp << std::endl;	
			ClosestPoints.clear();

			defect = 0;

		}
		// Max area selection
		else if (edge == 3){
			// Myseg and closest points have the same size, find area for each pair, keep them stored
			for (Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
				area = CGAL::area(ClosestPoints.at(i), edge->source(), edge->target());
				areav.push_back(area);
				i++;
			}

			i = 0;

			while(true){
				for (int j = 0; j < areav.size(); j++){
					if(areav.at(j) > maxarea && areav.at(j) < newmax){
						maxarea = areav.at(j);
						index = j;
						newp = ClosestPoints.at(j);
					}
				}

				newmax = maxarea;
				
				// Visibility check, point must be able to "see" every edge
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!CGAL::do_intersect(Segment_2(edge->start(), newp), Segment_2(newp, edge->end())))
						std::cerr << "Visibility error" << std::endl;
				}

				// Insert the new point
				for (Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if (index2 == index){
						edgeToBeReplaced = *edge;
						index2 = 0;
						break;
					}
					index2++;
				}
					
				if(insertNewPointToPolygonCH(polygonchain, edgeToBeReplaced.start(), edgeToBeReplaced.end(), newp) == 0){
					areav.clear();
					continue;
				}

				for (auto it = RemainingPoints.begin(); it != RemainingPoints.end(); ++it){
					if(CGAL::bounded_side_2(polygonchain.begin(), polygonchain.end(), *it, K()) == CGAL::ON_UNBOUNDED_SIDE){
						std::cout << "Point Left Out" << *it << std::endl;
						defect = 1;
						for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
							if (*vertex == newp){
								polygonchain.erase(vertex);
								break;
							}
						}
						
						break;	
					}
				}
				if (defect == 1){
					areav.clear();
					continue;
				}
				break;
			}
			areav.clear();
			newmax = DBL_MAX;

<<<<<<< HEAD
		// After each new point entry, the polygon needs to remain simple
		const bool simpl = polygonchain.is_simple();
		if (!simpl){
			std::cout << "points = [\n";
			for(auto point : Points)
				std::cout << "[" << point.x() << "," << point.y() << "], " << "[" << point.x() << "," << point.y() << "],";
			std::cout << "\n]\n";
			utils::polygonToPythonArray(mypolygon, "convexHull");
			utils::polygonToPythonArray(polygonchain);
			std::cerr << "Polygon is no simple\n";
			exit (EXIT_FAILURE); 
		}
		else{
			std::cout << "points = [\n";
			for(auto point : Points)
				std::cout << "[" << point.x() << "," << point.y() << "], " << "[" << point.x() << "," << point.y() << "],";
			std::cout << "\n]\n";
			utils::polygonToPythonArray(mypolygon, "convexHull");
			utils::polygonToPythonArray(polygonchain);
			std::cerr << "Polygon is no simple\n";

		}
	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	std::cout << "Made It" << std::endl;

	//write output
	utils::writeToOutputFile(outFile, Points, polygonchain, mypolygon, edge, "none", std::abs(mypolygon.area()), executionTime.count());
	std::cout << "Made It" << std::endl;
	utils::polygonToPythonArray(polygonchain);
}
=======
			RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
			ClosestPoints.clear();

			defect = 0;
		}	
	}
>>>>>>> 8bbd801d13d069bc12b6da8c50c58b79f3f02e97

	if(!polygonchain.is_simple()){
		std::cout << "points = [\n";
		for(auto point : Points)
			std::cout << "[" << point.x() << "," << point.y() << "], " << "[" << point.x() << "," << point.y() << "],";
		std::cout << "\n]\n";
		utils::polygonToPythonArray(mypolygon, "convexHull");
		utils::polygonToPythonArray(polygonchain);
		std::cerr << "Polygon is not simple\n";
		exit (EXIT_FAILURE); 
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	//write output
	//utils::writeToOutputFile(outFile, Points, polygonchain, mypolygon, edge, std::abs(mypolygon.area()), executionTime.count());
	std::cout << "Success" << std::endl;
}	

int insertNewPointToPolygonCH(Polygon_2 &polygon, const Point_2 &begin, const Point_2 &end, Point_2 newPoint){

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