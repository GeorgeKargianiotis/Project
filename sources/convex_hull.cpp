#include <vector>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"

typedef std::vector<Point_2>::iterator pveciterator;
typedef std::vector<Segment_2> Segments; 

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points, int edge){	

	Polygon_2 mypolygon, polygonchain;
	Segments myseg;
	std::vector<Point_2> RemainingPoints; // Used to store points not yet included in polygon, needs to be empty in the end

	// Add all points to new vector
	for (auto iter=Points.begin(); iter!=Points.end(); ++iter)
		RemainingPoints.push_back(*iter);

	// Needed for points to add
	int counter = 0;

	// Πολυγωνική Αλυσίδα:vector<Segment_2> 
	// ΚΠ: CONVEX_HULL_2
	const Polygon_2::Vertices& range = mypolygon.vertices();
 	std::vector<Point_2> result;


	// Using all given points to create initial chain
	CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(result));

 	for (auto it = result.begin(); it!= result.end();++it){
 		polygonchain.push_back(*it);
		RemainingPoints.erase(std::remove(RemainingPoints.begin(), RemainingPoints.end(), *it), RemainingPoints.end());
	}	
	std::cout << result.size() << " points on the convex hull" << std::endl;

	// Use this for debug
	//for (pveciterator iter=result.begin(); iter!=result.end(); ++iter)
 		//std::cout << *iter << std::endl;
 	

 	std::cout << polygonchain.area() << std::endl;

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
				// Visible, Add it to the polygon
				// FIX NEEDED, FIND THE CLOSEST POINT WITH SQUARED DISTANCE
				if(CGAL::do_intersect(temp, Points[0])){
					myseg.push_back(Segment_2 (temp.source(), Points[0]));
					myseg.push_back(Segment_2 (Points[0], temp.target()));
					//ADD TO RIGHT POLYGON
				}
			}	
		}
		else if (edge == 2){
			// 2ND WAY, MAX TRIANGLE AREA
		}
		
		else{
			// 3RD WAY, MIN TRIANGLE AREA
		}

	
	
	// FOR BOTH WE NEED MAX/MIN AND SPECIFIC POINT
	

	// Check final polygon, simplicity and polygon points = starting points
 	/*const bool simpl = mypolygon.is_simple();
 	if (simpl) 
 		std::cout << "Simple polygon" << std::endl;
 	else
 		std::cout << "Not simple" << std::endl;*/
 
	// CGAL::squared_distance() + arguments

	// Need to use sqrt somewhere
	}
}