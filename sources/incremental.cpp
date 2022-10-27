#include <vector>
#include <string>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon);

void incremental::incrementalAlgorithm(std::vector<Point_2> &points, char *initialization){

	//order by x ascending
	if(std::string(initialization).compare(SORT_BY_X_ASC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp1aPoint2);
	//order by x descending 
	else if(std::string(initialization).compare(SORT_BY_X_DESC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp1bPoint2);
	//order by y ascending
	else if(std::string(initialization).compare(SORT_BY_Y_ASC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp2aPoint2);
	//order by y descending
	else if(std::string(initialization).compare(SORT_BY_Y_DESC) == 0)
		std::sort(points.begin(), points.end(), utils::cmp2bPoint2);

	Polygon_2 polygon, convexHullPolygon;
	
	// initialize polygon with the 3 first sorted points
	polygon.push_back(points[0]);
	polygon.push_back(points[1]);
	polygon.push_back(points[2]);

	Point_2 lastPointExpandPolygon = points[2];	//to teleytaio shmeio poy mphke sthn polygwnikh grammh kai thn epektine

	// add points until a triangle get shaped
	int i = 0;
	while(CGAL::collinear(points[i], points[i+1], points[i+2])){
		polygon.push_back(points[i+3]);
		lastPointExpandPolygon = points[i+3];
		i++;
	}

	//find the convex hull polygon
	getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);

	//find the red edges of convex hull polygon
	for(int i = 0; i < convexHullPolygon.edges().size(); i++){
		
	}
}

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon){
	std::vector<Point_2> points;
	CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(points));
	for(auto it = vertices.begin(); it != vertices.end(); it++)
		convexHullPolygon.push_back(*it);
}