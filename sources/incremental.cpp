#include <vector>
#include <string>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon);

bool isRedEdge(Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Point_2 &polygonPoint);

bool isVisibleEdge(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edge, const Point_2 &newPoint);

bool segment1BeforeSegment2AxisX(Segment_2 &seg1, Segment_2 &seg2);

bool segment1BeforeSegment2AxisY(Segment_2 &seg1, Segment_2 &seg2);

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
		i++;
		polygon.push_back(points[i+2]);

		if(i == points.size()){
			std::cerr << "Given points are all collinear. Can't create polygon" << std::endl;
			exit (EXIT_FAILURE);
		}
	}


	lastPointExpandPolygonIndex = i + 2;
	lastPointExpandPolygon = points[lastPointExpandPolygonIndex];
	polygonArea = CGAL::area(points[0], points[1], points[i+3]);
	Point_2 polygonFirstEdgeMiddlePoint = Point_2((polygon.edge(0).point(0).hx() + polygon.edge(0).point(1).hx()) / 2.0, (polygon.edge(0).point(0).hy() + polygon.edge(0).point(1).hy()) / 2.0);

	while(lastPointExpandPolygonIndex != points.size() - 1){
		lastPointExpandPolygonIndex++;
		//find the convex hull polygon
		convexHullPolygon.clear();
		getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);
		std::vector<Segment_2> visibleEdges;

		//find the red edges of convex hull polygon
		for(Polygon_2::Edge_const_iterator convexPolygonEdge = convexHullPolygon.edges().begin(); convexPolygonEdge != convexHullPolygon.edges().end(); convexPolygonEdge++){

			//if(isRedEdge(convexPolygonEdge, points[lastPointExpandPolygonIndex], points[0])){
			if(isRedEdge(convexPolygonEdge, points[lastPointExpandPolygonIndex], polygonFirstEdgeMiddlePoint)){

				//find visible edges
				for(Polygon_2::Edge_const_iterator edge = polygon.edges().begin(); edge != polygon.edges().end(); edge++){

					if(convexPolygonEdge->start() == edge->start()){

						//check if all polygon edges "behind" the red edge are visible to the newPoint
						do{
							 if(isVisibleEdge(polygon, edge, points[lastPointExpandPolygonIndex]))
							 	visibleEdges.push_back(Segment_2(edge->start(), edge->end()));
							edge++;
						} while(convexPolygonEdge->end() != edge->start() && edge != polygon.edges().end());

						break;
					}
				}
			}
		}

		//choose visible edge to replace
	}
}

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon){
	std::vector<Point_2> points;
	CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(points));
	for(auto it = vertices.begin(); it != vertices.end(); it++)
		convexHullPolygon.push_back(*it);
}

//given an edge of the convex hull polygon it returns true if it is red 
bool isRedEdge(Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Point_2 &polygonPoint){
	//double detA = CGAL::determinant(Vector_3(edge->start().hx(), edge->end().hw(), newPoint.hx()), Vector_3(edge->start().hy(), edge->end().hy(), newPoint.hy()), Vector_3(1, 1, 1));
	// double detB = CGAL::determinant(Vector_3(edge->start().hx(), edge->end().hw(), polygonPoint.hx()), Vector_3(edge->start().hy(), edge->end().hy(), polygonPoint.hy()), Vector_3(1, 1, 1));
	double detA = CGAL::determinant(Vector_3(edge->start().hx(), edge->start().hy(), 1), Vector_3(edge->end().hx(), edge->end().hy(), 1), Vector_3(newPoint.hx(), newPoint.hy(), 1));
	double detB = CGAL::determinant(Vector_3(edge->start().hx(), edge->start().hy(), 1), Vector_3(edge->end().hx(), edge->end().hy(), 1), Vector_3(polygonPoint.hx(), polygonPoint.hy(), 1));
	return detA * detB < 0;
}

//checks if the given edge is visible from the newPoint
bool isVisibleEdge(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edgeUnderCheck, const Point_2 &newPoint){

	Segment_2 line1 = Segment_2(edgeUnderCheck->start(), newPoint);
	Segment_2 line2 = Segment_2(edgeUnderCheck->end(), newPoint);

	for(int i = 0; i < polygon.edges().size(); i++){
		Segment_2 intersectLine = Segment_2(polygon.edge(i).start(), polygon.edge(i).end());

		//if the two lines are neighbors or are the same line
		if(intersectLine.start() == line1.start() || intersectLine.end() == line1.start() || intersectLine.start() == line1.end() || intersectLine.end() == line1.end())
			continue;
		if(intersectLine.start() == line2.start() || intersectLine.end() == line2.start() || intersectLine.start() == line2.end() || intersectLine.end() == line2.end())
			continue;

		if(CGAL::intersection(intersectLine, line1) || CGAL::intersection(intersectLine, line2))
			return false;	
	}

	return true;
}

// Because points are in order, we check if a line is behind another one before we call intersect
bool segment1BeforeSegment2AxisX(Segment_2 &seg1, Segment_2 &seg2){
	return seg1.start().hx() < seg2.start().hx() && seg1.start().hx() < seg2.end().hx() && seg1.end().hx() < seg2.start().hx() && seg1.end().hx() < seg2.end().hx();
}

// Because points are in order, we check if a line is behind another one before we call intersect
bool segment1BeforeSegment2AxisY(Segment_2 &seg1, Segment_2 &seg2){
	return seg1.start().hy() < seg2.start().hy() && seg1.start().hy() < seg2.end().hy() && seg1.end().hy() < seg2.start().hy() && seg1.end().hy() < seg2.end().hy();
}
