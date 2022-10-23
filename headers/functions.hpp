// Add algorithms here (1, 2 or 3)
#include <iostream>
#include <string>
#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/convex_hull_2.h>
#include <fstream>
#include <CGAL/Polygon_2.h>
#include <CGAL/basic.h>
#include <CGAL/Cartesian.h>
#include <CGAL/Simple_cartesian.h>
#include <CGAL/Polygon_2.h>


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point_2;
typedef std::istream_iterator< Point_2 > point2_iterator;
typedef std::vector<Point_2> Points;
typedef std::vector<Point_2>::iterator pveciterator;


typedef CGAL::Exact_predicates_inexact_constructions_kernel K;
typedef K::Point_2 Point;
typedef CGAL::Polygon_2<K> Polygon_2;
using std::cout; using std::endl;

// Functions for each method, might need more arguments than just the points
 Polygon_2 Incremental(Points mypoints); 

 Polygon_2 Convex_Hull(Points mypoints);

 Polygon_2 Onion(Point mypoints);
