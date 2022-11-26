#include <chrono>
#include <cstdlib>
#include <functional>
#include <string>
#include <vector>
#include <time.h>

#include "../headers/incremental.hpp"
#include "../headers/cgalConfig.hpp"
#include "../headers/utils.hpp"

void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon);

bool isRedEdge(const Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Polygon_2 &polygon);

bool isVisibleEdge(Polygon_2 &polygon, Point_2 &begin, Point_2 &end, const Point_2 &newPoint);

void insertNewPointToPolygon(Polygon_2 &polygon, const Point_2 &begin, const Point_2 &end, Point_2 newPoint);

int randomSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

int minAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

int maxAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

void incremental::incrementalAlgorithm(std::vector<Point_2> &points, char *initialization, int edgeSelection, std::ofstream &outFile){

	srand(time(0));

	auto start = std::chrono::high_resolution_clock::now();

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
	polygonArea = std::abs(CGAL::area(points[0], points[1], points[i+2]));
	std::vector<Segment_2> visibleEdges;

	while(lastPointExpandPolygonIndex != points.size() - 1){
		lastPointExpandPolygonIndex++;

		Point_2 newPoint = points[lastPointExpandPolygonIndex];
		
		//ignore duplicate points
		if(newPoint == points[lastPointExpandPolygonIndex - 1])
			continue;

		//find the convex hull polygon
		convexHullPolygon.clear();
		getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);

		if(polygon.is_clockwise_oriented())
			polygon.reverse_orientation();

		if(convexHullPolygon.is_clockwise_oriented() != polygon.is_clockwise_oriented())
			convexHullPolygon.reverse_orientation();

		visibleEdges.clear();

		//find the red edges of convex hull polygon
		for(Polygon_2::Edge_const_iterator convexPolygonEdge = convexHullPolygon.edges_begin(); convexPolygonEdge != convexHullPolygon.edges_end(); convexPolygonEdge++){

			if(isRedEdge(convexPolygonEdge, newPoint, convexHullPolygon)){

				Polygon_2::Edge_const_iterator &redEdge = convexPolygonEdge;

				//find visible edges
				for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){

					if(vertex == polygon.end())
						break;

					if(redEdge->start() == *vertex){

						Point_2 startPoint = *vertex;
						vertex++;
						Point_2 endPoint = *vertex;

						//if red edge belongs to polygon
						if(redEdge->end() == *vertex){
							if( !CGAL::collinear(startPoint, endPoint, newPoint) )
								visibleEdges.push_back(Segment_2(startPoint, endPoint));
							break;
						}
						vertex--;

						//check if all polygon edges "behind" the red edge are visible to the newPoint
						do{
							Point_2 startPoint = *vertex;
							vertex++;
							Point_2 endPoint;
							if(vertex == polygon.end())
								endPoint = *polygon.begin();
							else
								endPoint = *vertex;

							if(isVisibleEdge(polygon, startPoint, endPoint, newPoint))
								visibleEdges.push_back(Segment_2(startPoint, endPoint));

							if(vertex == polygon.end())
								vertex = polygon.begin();
						} while( *vertex != redEdge->end());

						break;
					}
				}
				continue;
			}
		}

		if(visibleEdges.empty()){
			std::cerr << "No visible edges\n";
			exit(EXIT_FAILURE);
		}

		//choose visible edge to replace
		int index = 0;
		if(edgeSelection == RANDOM_EDGE_SELECTION)
			index = randomSelectEdge(visibleEdges, points[lastPointExpandPolygonIndex]);
		else if(edgeSelection == MIN_AREA_EDGE_SELECTION)
			index = minAreaSelectEdge(visibleEdges, points[lastPointExpandPolygonIndex]);
		else if(edgeSelection == MAX_AREA_EDGE_SELECTION)
			index = maxAreaSelectEdge(visibleEdges, points[lastPointExpandPolygonIndex]);

		Segment_2 edgeToBeReplaced = visibleEdges[index];

		polygonArea += std::abs(CGAL::area(edgeToBeReplaced.start(), edgeToBeReplaced.end(), newPoint));

		//insert the new point to the right position in polygon
		insertNewPointToPolygon(polygon, edgeToBeReplaced.start(), edgeToBeReplaced.end(), newPoint);
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	//write output
	utils::writeToOutputFile(outFile, points, polygon, convexHullPolygon, edgeSelection, polygonArea, executionTime.count(), initialization);
	std::cout << "Success" << std::endl;
}

// int lastPointExpandPolygonIndex,
void getConvexHullPolygonFromPoints(const std::vector<Point_2> &vertices, Polygon_2 &convexHullPolygon){
	std::vector<Point_2> points;
	CGAL::convex_hull_2(vertices.begin(), vertices.end(), std::back_inserter(points));
	for(auto it = points.begin(); it != points.end(); it++)
		convexHullPolygon.push_back(*it);
}

//given an edge of the convex hull polygon it returns true if it is red 
bool isRedEdge(const Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Polygon_2 &polygon){
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
bool isVisibleEdge(Polygon_2 &polygon, Point_2 &begin, Point_2 &end, const Point_2 &newPoint){

	Segment_2 line1 = Segment_2(begin, newPoint);
	Segment_2 line2 = Segment_2(end, newPoint);

	for(int i = 0; i < polygon.edges().size(); i++){

		Segment_2 intersectLine = Segment_2(polygon.edge(i).start(), polygon.edge(i).end());

		bool firstLineIsNeighbor = intersectLine.start() == line1.start() || intersectLine.end() == line1.start();
		bool secondLineIsNeighbor =  intersectLine.start() == line2.start() || intersectLine.end() == line2.start();

		//if the two lines are neighbors or are the same line
		if(firstLineIsNeighbor && secondLineIsNeighbor)
			continue;
		if(firstLineIsNeighbor){
			if(CGAL::do_intersect(intersectLine, line2))
				return false;
			else
				continue;
		}
		if(secondLineIsNeighbor){
			if(CGAL::do_intersect(intersectLine, line1))
				return false;
			else
				continue;
		}

		if(CGAL::do_intersect(intersectLine, line1) || CGAL::do_intersect(intersectLine, line2))
			return false;	
	}

	return true;
}

void insertNewPointToPolygon(Polygon_2 &polygon, const Point_2 &begin, const Point_2 &end, Point_2 newPoint){

	for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){
		if(*vertex == begin){
			vertex++;
			if(vertex == polygon.end()){
				polygon.insert(polygon.begin(), newPoint);
				return;
			}
			if(*vertex == end){
				polygon.insert(vertex, newPoint);
				return;
			}
			vertex--;
		}
		 else if(*vertex == end){
			vertex++;
			if(vertex == polygon.end()){
				polygon.insert(polygon.begin(), newPoint);
				return;
			}
			if(*vertex == begin){
				polygon.insert(--vertex, newPoint);
				return;
			}
			vertex--;
		 }
	}

	std::cout << "Problem inserting point " << std::endl;
}

int randomSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint){
	return rand() % visibleEdges.size();
}

int minAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint){
	double minArea = std::numeric_limits<double>::max();
	double tempArea;
	int index = 0;

	for(int i = 0; i < visibleEdges.size(); i++){
		tempArea = std::abs(CGAL::area(visibleEdges[i].start(), visibleEdges[i].end(), newPoint));
		if( tempArea < minArea){
			minArea = tempArea;
			index = i;
		}
	}

	return index;
}

int maxAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint){
	double maxArea = 0;
	double tempArea;
	int index = 0;

	for(int i = 0; i < visibleEdges.size(); i++){
		tempArea = std::abs(CGAL::area(visibleEdges[i].start(), visibleEdges[i].end(), newPoint));
		if( tempArea > maxArea){
			maxArea = tempArea;
			index = i;
		}
	}

	return index;
}