#include <vector>
#include <string>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon);

bool isRedEdge(Polygon_2::Edge_const_iterator &edge, Point_2 &newPoint, Point_2 &polygonPoint);

bool isEdgeVisible(Polygon_2 &polygon, Polygon_2::Edge_const_iterator &edge, Point_2 &newPoint);

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
	Point_2 lastPointExpandPolygon; 	//to teleytaio shmeio poy mphke sthn polygwnikh grammh kai thn epektine
	int lastPointExpandPolygonIndex;
	double polygonArea;
	
	// initialize polygon with the 3 first sorted points
	polygon.push_back(points[0]);
	polygon.push_back(points[1]);
	polygon.push_back(points[2]);

	// add points until a triangle get shaped
	int i = 0;
	while(CGAL::collinear(points[i], points[i+1], points[i+2])){
		polygon.push_back(points[i+3]);
		i++;

		if(i == points.size()){
			std::cerr << "Given points are all collinear. Can't create polygon" << std::endl;
			exit (EXIT_FAILURE);
		}
	}

	lastPointExpandPolygonIndex = i + 3;
	lastPointExpandPolygon = points[lastPointExpandPolygonIndex];
	polygonArea = CGAL::area(points[0], points[1], points[i+3]);

	while(lastPointExpandPolygonIndex != points.size()){
		lastPointExpandPolygonIndex++;
		//find the convex hull polygon
		getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);

		//find the red edges of convex hull polygon
		for(Polygon_2::Edge_const_iterator convexPolygonEdge = convexHullPolygon.edges().begin(); convexPolygonEdge != convexHullPolygon.edges().end(); convexPolygonEdge++){

			if(isRedEdge(convexPolygonEdge , points[lastPointExpandPolygonIndex], points[0])){
				
				for(Polygon_2::Vertex_iterator polygonVertex = polygon.vertices_begin(); polygonVertex  != polygon.vertices_end(); polygonVertex++){

					if(convexPolygonEdge->start() == *polygonVertex){

						//check if all polygon edges "behind" the red edge are visible to the newPoint
						do{
							
							polygonVertex++;
							
						}while(convexPolygonEdge->end() != *polygonVertex);

						std::cout << "Checked all edges" << std::endl;
						break;
					}
				}
			}
		}
	}
}

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon){
	std::vector<Point_2> points;
	CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(points));
	for(auto it = vertices.begin(); it != vertices.end(); it++)
		convexHullPolygon.push_back(*it);
}

//given an edge of the convex hull polygon it returns true if it is red 
bool isRedEdge(Polygon_2::Edge_const_iterator &edge, Point_2 &newPoint, Point_2 &polygonPoint){
	double detA = CGAL::determinant(Vector_3(edge->start().hx(), edge->end().hw(), newPoint.hx()), Vector_3(edge->start().hy(), edge->end().hy(), newPoint.hy()), Vector_3(1, 1, 1));
	double detB = CGAL::determinant(Vector_3(edge->start().hx(), edge->end().hw(), polygonPoint.hx()), Vector_3(edge->start().hy(), edge->end().hy(), polygonPoint.hy()), Vector_3(1, 1, 1));
	return detA * detB < 0;
}

//checks if the given edge is visible from the newPoint
bool isEdgeVisible(Polygon_2 &polygon, Polygon_2::Edge_const_iterator &edge, Point_2 &newPoint){
	return true;
}