#include <vector>
#include <string>
#include <functional>
#include <cstdlib>
#include <time.h>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

typedef std::vector<Point_2>::iterator pveciterator;
typedef std::vector<Segment_2> Segments; 

bool isVisibleEdgeCH(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edge, const Point_2 &newPoint);

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points, int edge, std::ofstream &outFile){	

	auto start = std::chrono::high_resolution_clock::now();

	srand(time(0));

	Polygon_2 mypolygon, polygonchain; // Initial polygon to be used in convex_hull
	Segments myseg; // Edges stored here
	Segment_2 chosen;
	// Used to store points not yet included in polygon, needs to be empty in the end, closest is the closest point to each edge (according to myseg)
	std::vector<Point_2> RemainingPoints, ClosestPoints; 
	double distance; // Needed for the point we are about to add

	// Initialising distances and areas, neede for edge selection
	double mindistance = 9999999999.9999999;
	double minarea = 99999999.999999999;
	double maxarea = 0.0;

	// Point selected to add to the chain
	Point_2 toadd, newp;

	// Segments that provide the min and max area respectively
	Segment_2 minemb, maxemb;
	int random, index;
	double area; // Area calculated each time
	
	// Add all points to new vector
	for (auto iter=Points.begin(); iter!=Points.end(); iter++)
		RemainingPoints.push_back(*iter);
		
	// Same for polygon
	for (auto iter=Points.begin(); iter!=Points.end(); iter++)
		mypolygon.push_back(*iter);

	const Polygon_2::Vertices& range = mypolygon.vertices();
 	std::vector<Point_2> result;

	// Using all given points to create initial chain
	CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(result));

	// After we get the convex hull, create the chain with the points chosen, and remove them from the point vector (they have now been used)
 	for (auto it = result.begin(); it!= result.end(); it++){
 		polygonchain.push_back(*it);
		
		RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), *it), RemainingPoints.end());
	}	

	// Make edges from polygon chain, add them to vector
	for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++)
		myseg.push_back(Segment_2 (edge->start(), edge->end()));

	
	// From each edge, find nearest visible point INSIDE THE CHAIN and add it to polygon	
	// 3 ways: random, max and min area

	// Process while we still have unused points
	while (RemainingPoints.size() != 0){
		// Random edge selection
		if (edge == 1){
			// For each edge, find nearest point
			for (auto iter=myseg.begin(); iter!=myseg.end(); iter++){
				Segment_2 temp = *iter;
				for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end(); it++){
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

			myseg.push_back(Segment_2 (chosen.source(), newp));
			myseg.push_back(Segment_2 (newp, chosen.target()));
			myseg.erase(std::remove(myseg.begin(), myseg.end(), chosen), myseg.end());
			RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), newp), RemainingPoints.end());
			

			for(Polygon_2::Vertex_iterator EdgeToBeReplaced = polygonchain.begin(); EdgeToBeReplaced != polygonchain.end(); EdgeToBeReplaced++){
				if(*EdgeToBeReplaced == chosen.end()){
					polygonchain.insert(EdgeToBeReplaced, newp); 
					break;
				}
			}
			ClosestPoints.clear();
			// ΤΟ DO, VISIBILITY BEFORE INSERTION
			// CHANGE INTERSECTION WITH DO_INTERSECT
			// CLOCKWISE VS COUNTERCLOCKWISE ROTATION OF CONVEX HULL
			// FOR OUTSIDE POINTS: DO_INERSECT POINT LEFT OUT WITH 2 NEW EDGES AND OLD ONE
			for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
				if(!isVisibleEdgeCH(polygonchain, edge, newp))
					std::cerr << "Visibility error" << std::endl;
			}
			std::cout << "Conveeeex" << std::endl;

		}
		else if (edge == 2){
			// Add the edge that offers the smallest triangle area, when connected to the point
			for (auto iter=myseg.begin(); iter!=myseg.end(); ++iter){
				Segment_2 temp = *iter;
				for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end();++it){
					distance = CGAL::squared_distance(*iter, *it);

					if (distance < mindistance){
						mindistance = distance;
						toadd = *it;
					}
				}
				
				ClosestPoints.push_back(toadd);	
			}

				// Myseg and closest points have the same size, find area for each pair

				for (int i = 0; i != myseg.size(); i++){
					area = CGAL::area(ClosestPoints.at(i), myseg.at(i).source(), myseg.at(i).target());

					if (area < minarea){
						minarea = area;
						index = 1;
					}
				}

				myseg.push_back(Segment_2 (myseg.at(index).source(), RemainingPoints.at(index)));
				myseg.push_back(Segment_2 (RemainingPoints.at(index), myseg.at(index).target()));
				myseg.erase(std::remove(myseg.begin(), myseg.end(), myseg.at(index)), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), RemainingPoints.at(index)), RemainingPoints.end());
				
				for(Polygon_2::Vertex_iterator EdgeToBeReplaced = polygonchain.begin(); EdgeToBeReplaced != polygonchain.end(); EdgeToBeReplaced++){
					if(*EdgeToBeReplaced == chosen.end()){
						polygonchain.insert(EdgeToBeReplaced, newp); 
						break;
					}
				}
				ClosestPoints.clear();
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!isVisibleEdgeCH(polygonchain, edge, newp))
						std::cerr << "Visibility error" << std::endl;
				}
		}
		
		
		else{
			// Add the edge that offers the largest triangle area, when connected to the point
			for (auto iter=myseg.begin(); iter!=myseg.end(); ++iter){
				Segment_2 temp = *iter;
				for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end();++it){
					distance = CGAL::squared_distance(*iter, *it);

					if (distance < mindistance){
						mindistance = distance;
						toadd = *it;
					}
				}
				
				ClosestPoints.push_back(toadd);	
			}

				// Myseg and closest points have the same size, find area for each pair

				for (int i = 0; i != myseg.size(); i++){
					area = CGAL::area(ClosestPoints.at(i), myseg.at(i).source(), myseg.at(i).target());

					if (area > maxarea){
						maxarea = area;
						index = 1;
					}
				}

				myseg.push_back(Segment_2 (myseg.at(index).source(), RemainingPoints.at(index)));
				myseg.push_back(Segment_2 (RemainingPoints.at(index), myseg.at(index).target()));
				myseg.erase(std::remove(myseg.begin(), myseg.end(), myseg.at(index)), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), RemainingPoints.at(index)), RemainingPoints.end());
				
				for(Polygon_2::Vertex_iterator EdgeToBeReplaced = polygonchain.begin(); EdgeToBeReplaced != polygonchain.end(); EdgeToBeReplaced++){
					if(*EdgeToBeReplaced == chosen.end()){
						polygonchain.insert(EdgeToBeReplaced, newp); 
						break;
					}
				}
				ClosestPoints.clear();
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!isVisibleEdgeCH(polygonchain, edge, newp))
						std::cerr << "Visibility error" << std::endl;
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
			if(CGAL::intersection(intersectLine, line2))
				return false;
			else
				continue;
		}
		if(secondLineIsNeighbor){
			if(CGAL::intersection(intersectLine, line1))
				return false;
			else
				continue;
		}

		if(CGAL::intersection(intersectLine, line1) || CGAL::intersection(intersectLine, line2))
			return false;	
	}

	return true;
}