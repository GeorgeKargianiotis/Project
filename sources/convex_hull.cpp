#include <vector>

#include "../headers/convex_hull.hpp"
#include "../headers/cgalConfig.hpp"

void convex_hull::convex_HullAlgorithm(std::vector<Point_2> &Points){	

	Polygon_2 mypolygon, chp;

	// Take the first three points and use them as starting ΚΠ
	// Edge cases?
	for(auto point : Points)
		std::cout << point << std::endl;
	mypolygon.push_back(Points[0]);
	mypolygon.push_back(Points[1]);
	mypolygon.push_back(Points[2]);

	// Needed for points to add
	int counter = 2;
	

	// Πολυγωνική Αλυσίδα:vector<Segment_2> 
	// ΚΠ: CONVEX_HULL_2
	const Polygon_2::Vertices& range = mypolygon.vertices();
 	std::vector<Point_2> result;

 	for(auto it = range.begin(); it!= range.end(); ++it){
 	std::cout << *it << std::endl;
 	}

	for(const Segment_2& e : mypolygon.edges()){
 	std::cout << e << std::endl;
 	}
 	std::cout << mypolygon.area() << std::endl;


	CGAL::convex_hull_2(range.begin(), range.end(), std::back_inserter(result));

 	for(auto it = result.begin(); it!= result.end();++it)
 		chp.push_back(*it);

 	std::cout << chp.area() << std::endl;

 	const bool simpl = mypolygon.is_simple();
 	if (simpl) 
 		std::cout << "Simple polygon" << std::endl;
 	else
 		std::cout << "Not simple" << std::endl;
 
	// CGAL::squared_distance() + arguments

	// Need to use sqrt somewhere

}