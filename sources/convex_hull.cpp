#include <vector>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"

typedef std::vector<Point_2>::iterator pveciterator;
typedef std::vector<Segment_2> Segments; 

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points){	

	Polygon_2 mypolygon, polygonchain;
	Segments myseg;

	// Needed for points to add
	int counter = 0;

	// Πολυγωνική Αλυσίδα:vector<Segment_2> 
	// ΚΠ: CONVEX_HULL_2
	const Polygon_2::Vertices& range = mypolygon.vertices();
 	std::vector<Point_2> result;


	// Using all given points to create initial chain
	CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(result));

 	for (auto it = result.begin(); it!= result.end();++it)
 		polygonchain.push_back(*it);
	std::cout << result.size() << " points on the convex hull" << std::endl;

	for (pveciterator iter=result.begin(); iter!=result.end(); ++iter)
 		std::cout << *iter << std::endl;
 	

 	std::cout << polygonchain.area() << std::endl;

	// Make edges from polygon chain, add them to vector
	for (auto vi = polygonchain.vertices_begin(); vi != polygonchain.vertices_end(); vi+=2)
		myseg.push_back(Segment_2 (*vi, *(vi+1)));

	// From each edge, find nearest visible point and add it to polygon	

 	const bool simpl = mypolygon.is_simple();
 	if (simpl) 
 		std::cout << "Simple polygon" << std::endl;
 	else
 		std::cout << "Not simple" << std::endl;
 
	// CGAL::squared_distance() + arguments

	// Need to use sqrt somewhere

}