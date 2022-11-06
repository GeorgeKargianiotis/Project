#include <vector>
#include <string>
#include <functional>
#include <cstdlib>
#include <time.h>
#include <chrono>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

typedef std::vector<Point_2>::iterator pveciterator;
typedef std::vector<Segment_2> Segments; 

bool isVisibleEdgeCH(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edge, const Point_2 &newPoint);

// int check_inside(Point_2 pt, Point_2 start, Point_2 end, K traits);
void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points, int edge, std::ofstream &outFile){	

	auto start = std::chrono::high_resolution_clock::now();

	srand(time(0));

	Polygon_2 mypolygon, polygonchain; // Initial polygon to be used in convex_hull (polygon chain)
	Segments myseg; // Edges stored here
	Segment_2 chosen, current; // Segments to be inserted or ketp in case we have visibility errors or an "external" point
	// Used to store points not yet included in polygon, needs to be empty in the end, closest is the closest point to each edge (according to myseg)
	std::vector<Point_2> RemainingPoints, ClosestPoints, DefectivePoints; // Defective is to store points that cause an error

	double distance; // Needed for the point we are about to add
	// Initialising distances and areas, neede for edge selection
	double mindistance = 9999999999.9999999;
	double minarea = 99999999.999999999;
	double maxarea = 0.0;

	// Point selected to add to the chain
	Point_2 toadd, newp;

	// Segments that provide the min and max area respectively
	Segment_2 minemb, maxemb;
	int random, index, outside, defect = 0;
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

	//std::cout << polygonchain.orientation() << std::endl;

	// Make edges from polygon chain, add them to vector
	for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++)
		myseg.push_back(Segment_2 (edge->start(), edge->end()));

	
	// From each edge, find nearest visible point INSIDE THE CHAIN and add it to polygon	
	// 3 ways: random, max and min area

	// Process while we still have unused points
	while (RemainingPoints.size() != 0){
		// Random edge selection
		if (edge == 1){
			while(true){
				// For each edge, find nearest point
				for (auto iter=myseg.begin(); iter!=myseg.end(); iter++){
					Segment_2 temp = *iter;
					for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end(); it++){
						if (DefectivePoints.size() != 0){
							for (auto it2 = DefectivePoints.begin(); it2!= DefectivePoints.end(); it2++){
								if (*it == *it2){
									break;
								}	
							}
						continue;	
						}
						distance = CGAL::squared_distance(*iter, *it);

						// Keep the one closest to the edge
						if (distance < mindistance){
							mindistance = distance;
							toadd = *it;
						}
					}
					// Make the entry: Each edge in myseg now has a matching closest point in this vector
					ClosestPoints.push_back(toadd);	
				}

						
				// Connect point with a random edge, create new edges and remove the point, old edge is also removed
				random = rand() % ClosestPoints.size();
				chosen = myseg.at(random);
				newp = ClosestPoints.at(random);

				// Visibility check, point must be able to "see" every edge
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!isVisibleEdgeCH(polygonchain, edge, newp))
						std::cerr << "Visibility error" << std::endl;
				}

				// Insert the new point
				for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
					if(*vertex == chosen.start()){
						vertex++; 
						if(*vertex == chosen.end()){
							polygonchain.insert(vertex, newp);
							break;
						}

						vertex--;
						if(vertex != polygonchain.begin())
							vertex--;
						if(*vertex == chosen.end()){
							polygonchain.insert(vertex, newp);
							break;
						}

						if(*polygonchain.begin() == chosen.end()){
							polygonchain.insert(polygonchain.begin(), newp);
							break;
						}
						
						std::cout << "Problem inserting point " << std::endl;
						exit (EXIT_FAILURE);

					}
				}


				// Keep the new and old edges, in case we have an xternal point and need to backtrack
				current = chosen;
				Segment_2 new1 (chosen.source(), newp);
				Segment_2 new2 (newp, chosen.target());

				// Insert new edges, remove old one and "use" the point
				myseg.push_back(new1);
				myseg.push_back(new2);
				myseg.erase(std::remove(myseg.begin(), myseg.end(), chosen), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
				
				ClosestPoints.clear();

				// Check if any of the remaining points is now external due to the new polygon
				for (auto it = RemainingPoints.begin(); it != RemainingPoints.end(); ++it){
					if(CGAL::bounded_side_2(polygonchain.begin(), polygonchain.end(), *it, K()) == CGAL::ON_UNBOUNDED_SIDE){
						defect = 1;
						std::cout << "Point Left Out" << std::endl;
						DefectivePoints.push_back(newp);
						myseg.erase(std::remove(myseg.begin(), myseg.end(), new1), myseg.end());
						myseg.erase(std::remove(myseg.begin(), myseg.end(), new2), myseg.end());
						for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
							if (*vertex == newp){
								polygonchain.erase(vertex);
							}
						}
						RemainingPoints.push_back(newp);
						break;	
					}
				}
				if (defect == 0){
					break;
				}
			}
		}
		else if (edge == 2){
			while(true){
				// Add the edge that offers the smallest triangle area, when connected to the point
				for (auto iter=myseg.begin(); iter!=myseg.end(); ++iter){
					Segment_2 temp = *iter;
					for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end();++it){

						if (DefectivePoints.size() != 0){
							for (auto it2 = DefectivePoints.begin(); it2!= DefectivePoints.end(); it2++){
								if (*it == *it2){
									break;
								}	
							}
							continue;	
						}
						distance = CGAL::squared_distance(*iter, *it);

						if (distance < mindistance){
							mindistance = distance;
							toadd = *it;
						}
					}
					
					ClosestPoints.push_back(toadd);	
					std::cout << toadd << std::endl;
				}
					// Myseg and closest points have the same size, find area for each pair

					for (int i = 0; i != myseg.size(); i++){
						area = CGAL::area(ClosestPoints.at(i), myseg.at(i).source(), myseg.at(i).target());
						std::cout << area << std::endl;
						if (area > maxarea){
							maxarea = area;
							index = i;
						}
					}

					// Same as above, visibility and insertion
					for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
						if(!isVisibleEdgeCH(polygonchain, edge, ClosestPoints.at(index)))
							std::cerr << "Visibility error" << std::endl;
					}

					for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
						std::cout << "Insertion" << std::endl;
						if(*vertex == chosen.start()){
							vertex++; 
							if(*vertex == chosen.end()){
								polygonchain.insert(vertex, newp);
								break;
							}

							vertex--;
							if(vertex != polygonchain.begin())
								vertex--;
							if(*vertex == chosen.end()){
								polygonchain.insert(vertex, newp);
								break;
							}

							if(*polygonchain.begin() == chosen.end()){
								polygonchain.insert(polygonchain.begin(), newp);
								break;
							}
							
							std::cout << "Problem inserting point " << std::endl;
							exit (EXIT_FAILURE);

						}
					}

				// Same process as 1st case, same for 3rd as well
				current = chosen;
				Segment_2 new1 (chosen.source(), newp);
				Segment_2 new2 (newp, chosen.target());

				// Insert new edges, remove old one and "use" the point
				myseg.push_back(new1);
				myseg.push_back(new2);
				myseg.erase(std::remove(myseg.begin(), myseg.end(), chosen), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
				
				ClosestPoints.clear();

				for (auto it = RemainingPoints.begin(); it != RemainingPoints.end(); ++it){
					if(CGAL::bounded_side_2(polygonchain.begin(), polygonchain.end(), *it, K()) == CGAL::ON_UNBOUNDED_SIDE){
						defect = 1;
						std::cout << "Point Left Out" << std::endl;
						DefectivePoints.push_back(newp);
						myseg.erase(std::remove(myseg.begin(), myseg.end(), new1), myseg.end());
						myseg.erase(std::remove(myseg.begin(), myseg.end(), new2), myseg.end());
						for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
							if (*vertex == newp){
								polygonchain.erase(vertex);
							}
						}
						RemainingPoints.push_back(newp);
						break;	
					}
				}
				if (defect == 0){
					break;
				}
			}		
		}
		
		
		else{
			while(true){
				// Add the edge that offers the smallest triangle area, when connected to the point
				for (auto iter=myseg.begin(); iter!=myseg.end(); ++iter){
					Segment_2 temp = *iter;
					for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end();++it){

						if (DefectivePoints.size() != 0){
							for (auto it2 = DefectivePoints.begin(); it2!= DefectivePoints.end(); it2++){
								if (*it == *it2){
									break;
								}	
							}
							continue;	
						}
						distance = CGAL::squared_distance(*iter, *it);

						if (distance < mindistance){
							mindistance = distance;
							toadd = *it;
						}
					}
					
					ClosestPoints.push_back(toadd);	
					DefectivePoints.clear();
				}
					// Myseg and closest points have the same size, find area for each pair

					for (int i = 0; i != myseg.size(); i++){
						area = CGAL::area(ClosestPoints.at(i), myseg.at(i).source(), myseg.at(i).target());
						if (area < minarea){
							minarea = area;
							index = i;
						}
					}

					// Same as above, visibility and insertion
					for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
						if(!isVisibleEdgeCH(polygonchain, edge, ClosestPoints.at(index)))
							std::cerr << "Visibility error" << std::endl;
					}

					for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
						if(*vertex == chosen.start()){
							vertex++; 
							if(*vertex == chosen.end()){
								polygonchain.insert(vertex, newp);
								break;
							}

							vertex--;
							if(vertex != polygonchain.begin())
								vertex--;
							if(*vertex == chosen.end()){
								polygonchain.insert(vertex, newp);
								break;
							}

							if(*polygonchain.begin() == chosen.end()){
								polygonchain.insert(polygonchain.begin(), newp);
								break;
							}
							
							std::cout << "Problem inserting point " << std::endl;
							exit (EXIT_FAILURE);

						}
					}

				// Same process as 1st case, same for 3rd as well
				current = chosen;
				Segment_2 new1 (chosen.source(), newp);
				Segment_2 new2 (newp, chosen.target());

				// Insert new edges, remove old one and "use" the point
				myseg.push_back(new1);
				myseg.push_back(new2);
				myseg.erase(std::remove(myseg.begin(), myseg.end(), chosen), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
				std::cout << "Made Addition" << std::endl; 
				
				ClosestPoints.clear();

				for (auto it = RemainingPoints.begin(); it != RemainingPoints.end(); ++it){
					if(CGAL::bounded_side_2(polygonchain.begin(), polygonchain.end(), *it, K()) == CGAL::ON_UNBOUNDED_SIDE){
						defect = 1;
						std::cout << "Point Left Out" << std::endl;
						DefectivePoints.push_back(newp);
						myseg.erase(std::remove(myseg.begin(), myseg.end(), new1), myseg.end());
						myseg.erase(std::remove(myseg.begin(), myseg.end(), new2), myseg.end());
						for(Polygon_2::Vertex_iterator vertex = polygonchain.begin(); vertex != polygonchain.end(); vertex++){
							if (*vertex == newp){
								polygonchain.erase(vertex);
							}
						}
						RemainingPoints.push_back(newp);
						break;	
					}
				}
				if (defect == 0){
					break;
				}
			}	
		}

	

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
		mindistance = 9999999999.9999999;
		minarea = 99999999.999999999;
		maxarea = 0.0;

	}
	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);

	//write output
	utils::writeToOutputFile(outFile, Points, polygonchain, mypolygon, edge, "none", std::abs(mypolygon.area()), executionTime.count());
	utils::polygonToPythonArray(polygonchain);
}

//checks if the given edge is visible from the newPoint
bool isVisibleEdgeCH(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edgeUnderCheck, const Point_2 &newPoint){

	Segment_2 line1 = Segment_2(edgeUnderCheck->start(), newPoint);
	Segment_2 line2 = Segment_2(edgeUnderCheck->end(), newPoint);

	for(int i = 0; i < polygon.edges().size(); i++){
		Segment_2 intersectLine = Segment_2(polygon.edge(i).start(), polygon.edge(i).end());

		bool firstLineIsNeighbor = intersectLine.start() == line1.start() || intersectLine.end() == line1.start() || intersectLine.start() == line1.end() || intersectLine.end() == line1.end();
		bool secondLineIsNeighbor =  intersectLine.start() == line2.start() || intersectLine.end() == line2.start() || intersectLine.start() == line2.end() || intersectLine.end() == line2.end();

		//if the two lines are neighbors or are the same line
		if(firstLineIsNeighbor && secondLineIsNeighbor)
			continue;
		if(firstLineIsNeighbor){
			if(CGAL::do_intersect(intersectLine, line2))
				return false;
			else
				continue;
		}
		if(secondLineIsNeighbor){
			if(CGAL::do_intersect(intersectLine, line1))
				return false;
			else
				continue;
		}

		if(CGAL::do_intersect(intersectLine, line1) || CGAL::do_intersect(intersectLine, line2))
			return false;	
	}

	return true;
}