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

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points, int edge){	

	
	Polygon_2 mypolygon, polygonchain; // Initial polygon to be used in convex_hull
	Segments myseg; // Edges stored here
	std::vector<Point_2> RemainingPoints; // Used to store points not yet included in polygon, needs to be empty in the end
	double distance; // Needed for the point we are about to add

	// Initialising distances and areas, neede for edge selection
	double mindistance = 9999999999.9999999;
	double minarea = 99999999.999999999;
	double maxarea = 0.0;

	// Point selected to add to the chain
	Point_2 toadd;

	// Segments that provide the min and max area respectively
	Segment_2 random, minemb, maxemb;
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

	
	/*for (auto vi = polygonchain.begin() -1 ; vi != polygonchain.end(); vi++){
		myseg.push_back(Segment_2 (*vi, *(vi+1)));
		std::cout << "Segments Completed" << std::endl;
	}
		myseg.push_back(Segment_2 (*vi, *(vi+1)));*/
	
	// From each edge, find nearest visible point INSIDE THE CHAIN and add it to polygon	
	// 3 ways: random, max and min area

	std::cout << "Segments Completed" << std::endl;

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
				// After we find the closest point, make sure it's visible from every edge
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!isVisibleEdgeCH(polygonchain, edge, toadd))
						std::cerr << "Visibility error" << std::endl;
				}
				/*for (auto iter2=myseg.begin(); iter2!=myseg.end(); iter2++){
					if(!CGAL::do_intersect(*iter2, toadd)){
						std::cerr << "Visibility error" << std::endl;
					}
				}*/
				
				// Connect point with a random edge, create new edges and remove the point, old edge is also removed
				random = myseg.at(rand() % myseg.size());
				std::cout << random << std::endl;
				std::cout << myseg.size() << std::endl;
				myseg.push_back(Segment_2 (random.source(), toadd));
				myseg.push_back(Segment_2 (toadd, random.target()));
				myseg.erase(std::remove(myseg.begin(), myseg.end(), random), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), toadd), RemainingPoints.end());
				polygonchain.push_back(toadd);
				std::cout << "Problem Here" << std::endl;
			}	
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
				// Same as above, visibility check
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!isVisibleEdgeCH(polygonchain, edge, toadd)){
						std::cerr << "Visibility error" << std::endl;
					}
					
					area = CGAL::area(toadd, edge->source(), edge->target());

					if (area < minarea){
						minarea = area;
						minemb = *edge;
					}
				}
				myseg.push_back(Segment_2 (minemb.source(), toadd));
				myseg.push_back(Segment_2 (toadd, minemb.target()));
				myseg.erase(std::remove(myseg.begin(), myseg.end(), minemb), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), toadd), RemainingPoints.end());
				polygonchain.push_back(toadd);

			}
		}
		
		else{
			// Biggest triangle area
			for (auto iter=myseg.begin(); iter!=myseg.end(); ++iter){
				Segment_2 temp = *iter;
				for (auto it = RemainingPoints.begin(); it!= RemainingPoints.end();++it){
					distance = CGAL::squared_distance(*iter, *it);

					if (distance < mindistance){
						mindistance = distance;
						toadd = *it;
					}
				}
				// FOUND POINT, CHECK VISIBILITY WITH EVERY EDGE(SEGMENT)
				for(Polygon_2::Edge_const_iterator edge = polygonchain.edges().begin(); edge != polygonchain.edges().end(); edge++){
					if(!isVisibleEdgeCH(polygonchain, edge, toadd)){
						std::cerr << "Visibility error" << std::endl;
					}
					area = CGAL::area(toadd, edge->source(), edge->target());

					if (area > maxarea){
						maxarea = area;
						maxemb = *edge;
					}
				}
				myseg.push_back(Segment_2 (maxemb.source(), toadd));
				myseg.push_back(Segment_2 (toadd, maxemb.target()));
				myseg.erase(std::remove(myseg.begin(), myseg.end(), minemb), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), toadd), RemainingPoints.end());
				polygonchain.push_back(toadd);

			}
		}

	

	// After each new point entry, the polygon needs to remain simple
 	const bool simpl = polygonchain.is_simple();
 	if (!simpl)
		std::cerr << "Not Simple Polygon" << std::endl; 
 		
	}
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