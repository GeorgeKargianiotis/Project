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

bool isRedEdge(Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Polygon_2 &polygon);

bool isVisibleEdge(Polygon_2 &polygon, Polygon_2::Edge_const_iterator edgeUnderCheck, const Point_2 &newPoint);

void insertNewPointToPolygon(Polygon_2 &polygon, Segment_2 &edgeToBeReplaced, Point_2 newPoint);

bool pointIsCollinearAndBetweenPreviousPoints(char* initialization, std::vector<Point_2> &points, int n);

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

	int x = 0;
	int inserted = 0;

	while(lastPointExpandPolygonIndex != points.size() - 1){
		lastPointExpandPolygonIndex++;

		Point_2 newPoint = points[lastPointExpandPolygonIndex];
		//find the convex hull polygon
		convexHullPolygon.clear();
		getConvexHullPolygonFromPoints(polygon.vertices(), convexHullPolygon);

		if(convexHullPolygon.is_clockwise_oriented() != polygon.is_clockwise_oriented())
			convexHullPolygon.reverse_orientation();

		visibleEdges.clear();
		std::vector<Segment_2> redEdges;

		/*
			if point n have the same x coordinate (if points are order by x) with point n-1 and n+1 
			or point n have the same y coordinate (if points are order by y) with point n-1 and n+1
			and it is in between n-1 and n+1 
			just add it in the polygon between them
		*/
		if(pointIsCollinearAndBetweenPreviousPoints(initialization, points, lastPointExpandPolygonIndex)){

			std::cout << "here" << std::endl;
			//insert the new point to the right position in polygon
			for(Polygon_2::Vertex_iterator endVertexOfEdgeToBeReplaced = polygon.begin(); endVertexOfEdgeToBeReplaced != polygon.end(); endVertexOfEdgeToBeReplaced++){
				if(*endVertexOfEdgeToBeReplaced == points[lastPointExpandPolygonIndex+1]){
					polygon.insert(endVertexOfEdgeToBeReplaced, newPoint); 
					break;
				}
			}

			 if(!polygon.is_simple()){
				std::cout << "NOT SIMPLE!" << std::endl;
				exit (EXIT_FAILURE);
			 }
			continue;
		}

		bool firstRedEdgeFound = false;
		bool redEdgeIsVisibleEdge = false;
		//find the red edges of convex hull polygon
		for(Polygon_2::Edge_const_iterator convexPolygonEdge = convexHullPolygon.edges().begin(); convexPolygonEdge != convexHullPolygon.edges().end(); convexPolygonEdge++){

			if(isRedEdge(convexPolygonEdge, newPoint, polygon)){

				redEdges.push_back(*convexPolygonEdge);

				firstRedEdgeFound = true;

				//find visible edges
				for(Polygon_2::Edge_const_iterator edge = polygon.edges().begin(); edge != polygon.edges().end(); edge++){

					if(convexPolygonEdge->start() == edge->start()){

						if(convexPolygonEdge->end() == edge->end()){
							visibleEdges.push_back(Segment_2(edge->start(), edge->end()));
							redEdgeIsVisibleEdge = true;
							break;
						}

						//check if all polygon edges "behind" the red edge are visible to the newPoint
						do{
							if(isVisibleEdge(polygon, edge, newPoint))
								visibleEdges.push_back(Segment_2(edge->start(), edge->end()));
							edge++;
						} while(convexPolygonEdge->end() != edge->start());//&& edge != polygon.edges().end());

						break;
					}
				}

				continue;
			}

			//if one red edge has been found and next is blue, it stops
			if(firstRedEdgeFound)
				break;
		}

		if(redEdgeIsVisibleEdge){
			Segment_2 edgeToBeReplaced = visibleEdges[0];
			if(CGAL::collinear(edgeToBeReplaced.start(), edgeToBeReplaced.end(), newPoint)){
				int a = 0;
				for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){
					if(*vertex == edgeToBeReplaced.start()){
						Segment_2 s = Segment_2(edgeToBeReplaced.end(), newPoint);
						//if(s.collinear_has_on(edgeToBeReplaced.start())){
						if(s.has_on(edgeToBeReplaced.start())){
							polygon.insert(vertex, newPoint);
							a = 1;
							break;
						}
						else{
							vertex++;
							if(vertex == polygon.end()){
								polygon.insert(polygon.begin(), newPoint);
								break;
							}
							vertex++;
							polygon.insert(vertex, newPoint);
							a = 2;
							break;
						}
					}
					else if(*vertex == edgeToBeReplaced.end()){
						Segment_2 s = Segment_2(edgeToBeReplaced.start(), newPoint);
						//if(s.collinear_has_on(edgeToBeReplaced.end())){
						if(s.has_on(edgeToBeReplaced.end())){
							polygon.insert(vertex, newPoint);
							a = 3;
							break;
						}
						else{
							vertex++;
							if(vertex == polygon.begin()){
								polygon.insert(polygon.end(), newPoint);
								break;
							}
							vertex++;
							polygon.insert(vertex, newPoint);
							a = 4;
							break;
						}
					}
				}

				if(polygon.is_simple()){
					std::cout << "succesull insertion from red" << std::endl;
					std::cout << "a " << a << std::endl;
					continue;
				}
				else{
					std::cout << "wrong insertion of new point in red edge" << std::endl;
					std::cout << "a " << a << std::endl;
					std::cout << "points = [\n";
					for(auto point : points)
						std::cout << "[" << point.x() << "," << point.y() << "], " << "[" << point.x() << "," << point.y() << "],";
					std::cout << "]\n";
					utils::polygonToPythonArray(convexHullPolygon, "convexHull");
					std::cout << "redEdges = [\n";
					for(auto edge : redEdges)
						std::cout << "[" << edge.start().x() << "," << edge.start().y() << "], " << "[" << edge.end().x() << "," << edge.end().y() << "],";
					std::cout << "\b \b";
					std::cout << "]\n";
					utils::polygonToPythonArray(polygon);
					std::cout << "visibleEdges = [\n";
					for(auto edge : visibleEdges)
						std::cout << "[" << edge.start().x() << "," << edge.start().y() << "], " << "[" << edge.end().x() << "," << edge.end().y() << "],";
					std::cout << "\b \b";
					std::cout << "\n]\n";
					exit (EXIT_FAILURE);
				}
			}
		}

		if(visibleEdges.empty()){
			std::cout << "points = [\n";
			for(auto point : points)
				std::cout << "[" << point.x() << "," << point.y() << "], " << "[" << point.x() << "," << point.y() << "],";
			std::cout << "]\n";
			utils::polygonToPythonArray(convexHullPolygon, "convexHull");
			std::cout << "redEdges = [\n";
			for(auto edge : redEdges)
				std::cout << "[" << edge.start().x() << "," << edge.start().y() << "], " << "[" << edge.end().x() << "," << edge.end().y() << "],";
			std::cout << "\b \b";
			std::cout << "]\n";
			utils::polygonToPythonArray(polygon);
			std::cout << polygon.size() << std::endl;
			std::cout << "dual points " << x << std::endl;
			std::cout << lastPointExpandPolygonIndex << std::endl;
			std::cout << "inserted: " << inserted << std::endl;
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
		insertNewPointToPolygon(polygon, edgeToBeReplaced, newPoint);
				
		 if(!polygon.is_simple()){
			std::cout << "points = [\n";
			for(auto point : points)
				std::cout << "[" << point.x() << "," << point.y() << "], " << "[" << point.x() << "," << point.y() << "],";
			std::cout << "\b \b";
			std::cout << "\n]\n";
			utils::polygonToPythonArray(convexHullPolygon, "convexHull");
			std::cout << "redEdges = [\n";
			for(auto edge : redEdges)
				std::cout << "[" << edge.start().x() << "," << edge.start().y() << "], " << "[" << edge.end().x() << "," << edge.end().y() << "],";
			std::cout << "\b \b";
			std::cout << "]\n";
			utils::polygonToPythonArray(polygon);
			std::cout << "edgeToBeReplaced = [\n" << "[" << edgeToBeReplaced.start().x() << "," << edgeToBeReplaced.start().y() << "], " << "[" << edgeToBeReplaced.end().x() << "," << edgeToBeReplaced.end().y() << "]\n]\n";
			std::cout << polygon.size() << std::endl;
			std::cout << "dual points " << x << std::endl;
			std::cout << lastPointExpandPolygonIndex << std::endl;
			std::cout << "inserted: " << inserted << std::endl;
			std::cout << "Last visible edge was a red edge " << redEdgeIsVisibleEdge << std::endl;
			std::cerr << "Polygon is no simple\n";
			exit (EXIT_FAILURE);
		}

		if(lastPointExpandPolygonIndex + 1 == points.size()){
			// std::cout << "points = [\n";
			// for(auto point : points)
			// 	std::cout << "[" << point.x() << "," << point.y() << "], " << "[" << point.x() << "," << point.y() << "],";
			// std::cout << "\n]\n";
			// utils::polygonToPythonArray(convexHullPolygon, "convexHull");
			// std::cout << "redEdges = [\n";
			// for(auto edge : redEdges)
			// 	std::cout << "[" << edge.start().x() << "," << edge.start().y() << "], " << "[" << edge.end().x() << "," << edge.end().y() << "],";
			// std::cout << "]\n";
			// utils::polygonToPythonArray(polygon);
			//std::cout << "edgeToBeReplaced = [\n" << "[" << edgeToBeReplaced.start().x() << "," << edgeToBeReplaced.start().y() << "], " << "[" << edgeToBeReplaced.end().x() << "," << edgeToBeReplaced.end().y() << "]\n]\n";
		}
	}

	auto stop = std::chrono::high_resolution_clock::now();
	auto executionTime = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);

	std::cout << "Success" << std::endl;
	//write output
	utils::writeToOutputFile(outFile, points, polygon, convexHullPolygon, edgeSelection, initialization, polygonArea, executionTime.count());
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

void insertNewPointToPolygon(Polygon_2 &polygon, Segment_2 &edgeToBeReplaced, Point_2 newPoint){
	for(Polygon_2::Vertex_iterator vertex = polygon.begin(); vertex != polygon.end(); vertex++){
		if(*vertex == edgeToBeReplaced.start()){
			vertex++; 
			if(*vertex == edgeToBeReplaced.end()){
				polygon.insert(vertex, newPoint);
				break;
			}

			vertex--;
			if(vertex != polygon.begin())
				vertex--;
			if(*vertex == edgeToBeReplaced.end()){
				polygon.insert(vertex, newPoint);
				break;
			}

			if(*polygon.begin() == edgeToBeReplaced.end()){
				polygon.insert(polygon.begin(), newPoint);
				break;
			}
			
			std::cout << "Problem inserting point " << std::endl;
			exit (EXIT_FAILURE);
		}
	}
}

bool pointIsCollinearAndBetweenPreviousPoints(char* initialization, std::vector<Point_2> &points, int n){
	std::string init = std::string(initialization);

	if(init.compare(SORT_BY_X_ASC) == 0 || init.compare(SORT_BY_X_DESC))
		if(points[n-1].x() == points[n].x() && points[n].x() == points[n+1].x())
			if( !(points[n].y() > points[n-1].y() && points[n].y() > points[n+1].y()) && !(points[n].y() < points[n-1].y() && points[n].y() < points[n+1].y()) )
				return true;

	if(init.compare(SORT_BY_Y_ASC) == 0 || init.compare(SORT_BY_Y_DESC))
		if(points[n-1].y() == points[n].y() && points[n].y() == points[n+1].y())
			if( !(points[n].x() > points[n-1].x() && points[n].x() > points[n+1].x()) && !(points[n].x() < points[n-1].x() && points[n].x() < points[n+1].x()) )
				return true;

	return false;
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