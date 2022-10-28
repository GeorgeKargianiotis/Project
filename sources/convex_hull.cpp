#include <vector>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"

typedef std::vector<Point_2>::iterator pveciterator;
typedef std::vector<Segment_2> Segments; 

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points, int edge){	

	Polygon_2 mypolygon, polygonchain; // Initial polygon to be used in convex_hull
	Segments myseg; // Edges stored here
	std::vector<Point_2> RemainingPoints; // Used to store points not yet included in polygon, needs to be empty in the end
	double distance; // Needed for the point we are about to add
	double mindistance = 9999999999.9999999;
	Point_2 toadd;
	Segment_2 random, minemb, maxemb;
	double area;
	double minarea = 99999999.999999999;
	double maxarea = 0.0;

	// Add all points to new vector
	for (auto iter=Points.begin(); iter!=Points.end(); ++iter)
		RemainingPoints.push_back(*iter);

	// Same for polygon
	for (auto iter=Points.begin(); iter!=Points.end(); ++iter)
		mypolygon.push_back(*iter);


	const Polygon_2::Vertices& range = mypolygon.vertices();
 	std::vector<Point_2> result;

	// Using all given points to create initial chain
	CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(result));

	// After we get the convex hull, create the chain with the point chosen, and remove them from the point vector (they have now been used)
 	for (auto it = result.begin(); it!= result.end();++it){
 		polygonchain.push_back(*it);
		RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), *it), RemainingPoints.end());
	}	

	// Make edges from polygon chain, add them to vector
	for (auto vi = polygonchain.vertices_begin(); vi != polygonchain.vertices_end(); vi+=2)
		myseg.push_back(Segment_2 (*vi, *(vi+1)));

	// From each edge, find nearest visible point INSIDE THE CHAIN and add it to polygon	
	// 3 ways: random, max and min area

	// TODO: REMOVE POINTS WHEN WE ADD TO POLYGON
	while (RemainingPoints.size() != 0){
		// Random first, simply pick the first one that is visible
		if (edge == 1){
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
				for (auto iter2=myseg.begin(); iter2!=myseg.end(); ++iter2){
					if(!CGAL::do_intersect(*iter2, toadd)){
						std::cerr << "Visibility error" << std::endl;
					}
				}
				// 1st case, random edge
				random = myseg.at(rand() % myseg.size() + 1);
				myseg.push_back(Segment_2 (random.source(), toadd));
				myseg.push_back(Segment_2 (toadd, random.target()));
				myseg.erase(std::remove(myseg.begin(), myseg.end(), random), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), toadd), RemainingPoints.end());
				polygonchain.push_back(toadd);

			}	
		}
		else if (edge == 2){
			// 2ND WAY, MIN TRIANGLE AREA
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
				for (auto iter2=myseg.begin(); iter2!=myseg.end(); ++iter2){
					if(!CGAL::do_intersect(*iter2, toadd)){
						std::cerr << "Visibility error" << std::endl;
					}
					//
					Segment_2 sgmt = *iter2;
					area = CGAL::area(toadd, sgmt.source(), sgmt.target());

					if (area < minarea){
						minarea = area;
						minemb = sgmt;
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
			// 3RD WAY, MAX TRIANGLE AREA
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
				for (auto iter2=myseg.begin(); iter2!=myseg.end(); ++iter2){
					if(!CGAL::do_intersect(*iter2, toadd)){
						std::cerr << "Visibility error" << std::endl;
					}
					//
					Segment_2 sgmt = *iter2;
					area = CGAL::area(toadd, sgmt.source(), sgmt.target());

					if (area > maxarea){
						maxarea = area;
						maxemb = sgmt;
					}
				}
				myseg.push_back(Segment_2 (maxemb.source(), toadd));
				myseg.push_back(Segment_2 (toadd, maxemb.target()));
				myseg.erase(std::remove(myseg.begin(), myseg.end(), minemb), myseg.end());
				RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), toadd), RemainingPoints.end());
				polygonchain.push_back(toadd);

			}
		}

	

	// Check final polygon, simplicity and polygon points = starting points
 	const bool simpl = polygonchain.is_simple();
 	if (!simpl)
		std::cerr << "Not Simple Polygon" << std::endl; 
 		
}