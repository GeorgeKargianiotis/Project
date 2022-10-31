#include <vector>
#include <string>
#include <functional>
#include <cstdlib>
#include <time.h>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon);

bool isRedEdge(Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Polygon_2 &polygon);

bool isVisibleEdge(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edge, const Point_2 &newPoint);

int randomSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

int minAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

int maxAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

bool segment1BeforeSegment2AxisX(Segment_2 &seg1, Segment_2 &seg2);

bool segment1BeforeSegment2AxisY(Segment_2 &seg1, Segment_2 &seg2);

void test(int i ,int j, int k );

void incremental::incrementalAlgorithm(std::vector<Point_2> &points, char *initialization, int edgeSelection){

	srand(time(0));

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
	Point_2 polygonFirstEdgeMiddlePoint = Point_2((polygon.edge(0).point(0).x() + polygon.edge(0).point(1).x()) / 2.0, (polygon.edge(0).point(0).y() + polygon.edge(0).point(1).y()) / 2.0);
	std::vector<Segment_2> visibleEdges;

	while(lastPointExpandPolygonIndex != points.size() - 1){
		lastPointExpandPolygonIndex++;
		Point_2 newPoint = points[lastPointExpandPolygonIndex];
		//find the convex hull polygon
		convexHullPolygon.clear();
		getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);
		visibleEdges.clear();
		std::vector<Segment_2> redEdges;

		//find the red edges of convex hull polygon
		for(Polygon_2::Edge_const_iterator convexPolygonEdge = convexHullPolygon.edges().begin(); convexPolygonEdge != convexHullPolygon.edges().end(); convexPolygonEdge++){

			if(isRedEdge(convexPolygonEdge, newPoint, polygon)){

				redEdges.push_back(*convexPolygonEdge);

				//find visible edges
				for(Polygon_2::Edge_const_iterator edge = polygon.edges().begin(); edge != polygon.edges().end(); edge++){

					if(convexPolygonEdge->start() == edge->start()){

						if(convexPolygonEdge->end() == edge->end()){
							visibleEdges.push_back(Segment_2(edge->start(), edge->end()));
							break;
						}

						//check if all polygon edges "behind" the red edge are visible to the newPoint
						do{
							 if(isVisibleEdge(polygon, edge, newPoint))
							 	visibleEdges.push_back(Segment_2(edge->start(), edge->end()));
							edge++;
						} while(convexPolygonEdge->end() != edge->start() && edge != polygon.edges().end());

						break;
					}
				}
			}
		}


		std::cout << "New point " << newPoint << std::endl;
		std::cout << "Convex Hull: ";
		utils::polygonToPythonArray(convexHullPolygon);
		std::cout << "Red edges: ";
		for(auto edge : redEdges)
			std::cout << "[" << edge.start().x() << "," << edge.start().y() << "], " << "[" << edge.end().x() << "," << edge.end().y() << "],";
		std::cout << std::endl;

		if(visibleEdges.empty()){
			std::cout << "Empty visible Edges" << std::endl;
			exit(EXIT_FAILURE);
		}

		//choose visible edge to replace
		int index = 0;
		//if(std::string(edgeSelection).compare(RANDOM_EDGE_SELECTION) == 0)
		if(edgeSelection == RANDOM_EDGE_SELECTION)
			index = randomSelectEdge(visibleEdges, points[lastPointExpandPolygonIndex]);
		//if(std::string(edgeSelection).compare(MIN_AREA_EDGE_SELECTION) == 0)
		else if(edgeSelection == MIN_AREA_EDGE_SELECTION)
			index = minAreaSelectEdge(visibleEdges, points[lastPointExpandPolygonIndex]);
		//if(std::string(edgeSelection).compare(MAX_AREA_EDGE_SELECTION) == 0)
		else if(edgeSelection == MAX_AREA_EDGE_SELECTION)
			index = maxAreaSelectEdge(visibleEdges, points[lastPointExpandPolygonIndex]);

		Segment_2 edgeToBeReplaced = visibleEdges[index];

		//insert the new point to the right position in polygon
		for(Polygon_2::Vertex_iterator endVertexOfEdgeToBeReplaced = polygon.begin(); endVertexOfEdgeToBeReplaced != polygon.end(); endVertexOfEdgeToBeReplaced++){
			if(*endVertexOfEdgeToBeReplaced == edgeToBeReplaced.end()){
				polygon.insert(endVertexOfEdgeToBeReplaced, newPoint); 
				break;
			}
		}

		std::cout << "Edge replaced: " << "[" << edgeToBeReplaced.start().x() << "," << edgeToBeReplaced.start().y() << "], " << "[" << edgeToBeReplaced.end().x() << "," << edgeToBeReplaced.end().y() << "]\n";
		std::cout << "Polygon: ";
		utils::polygonToPythonArray(polygon);


		 if(!polygon.is_simple()){
			std::cerr << "Polygon is no simple\n";
			exit (EXIT_FAILURE);
		}

		std::cout << "\n\n";
	}
}

//, int lastPointExpandPolygonIndex,
void getConvexHullPolygonFromPoints(const std::vector<Point_2> &vertices, Polygon_2 &convexHullPolygon){
	std::vector<Point_2> points;
	CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(points));
	for(auto it = points.begin(); it != points.end(); it++)
		convexHullPolygon.push_back(*it);
}

//given an edge of the convex hull polygon it returns true if it is red 
bool isRedEdge(Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Polygon_2 &polygon){
	double detA;
	double detB;
	for(Polygon_2::Vertex_iterator point = polygon.vertices_begin(); point != polygon.vertices_end(); point++){
		detA = CGAL::determinant(Vector_3(edge->start().x(), edge->start().y(), 1), Vector_3(edge->end().x(), edge->end().y(), 1), Vector_3(newPoint.x(), newPoint.y(), 1));
		detB = CGAL::determinant(Vector_3(edge->start().x(), edge->start().y(), 1), Vector_3(edge->end().x(), edge->end().y(), 1), Vector_3(point->x(), point->y(), 1));
		if(detA * detB > 0)
			return false;
	}
	return true;
}

//checks if the given edge is visible from the newPoint
bool isVisibleEdge(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edgeUnderCheck, const Point_2 &newPoint){

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

int randomSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint){
	return rand() % visibleEdges.size();
}

int minAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint){
	double minArea = std::numeric_limits<double>::max();
	int index = 0;

	for(int i = 0; i < visibleEdges.size(); i++)
		if(CGAL::area(visibleEdges[i].start(), visibleEdges[i].end(), newPoint) < minArea)	
			index = 0;

	return index;
}

int maxAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint){
	double maxArea = std::numeric_limits<double>::min();
	int index = 0;

	for(int i = 0; i < visibleEdges.size(); i++)
		if(CGAL::area(visibleEdges[i].start(), visibleEdges[i].end(), newPoint) > maxArea)	
			index = 0;

	return index;
}

// Because points are in order, we check if a line is behind another one before we call intersect
bool segment1BeforeSegment2AxisX(Segment_2 &seg1, Segment_2 &seg2){
	return seg1.start().x() < seg2.start().x() && seg1.start().x() < seg2.end().x() && seg1.end().x() < seg2.start().x() && seg1.end().x() < seg2.end().x();
}

// Because points are in order, we check if a line is behind another one before we call intersect
bool segment1BeforeSegment2AxisY(Segment_2 &seg1, Segment_2 &seg2){
	return seg1.start().y() < seg2.start().y() && seg1.start().y() < seg2.end().y() && seg1.end().y() < seg2.start().y() && seg1.end().y() < seg2.end().y();
}