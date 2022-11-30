#ifndef INCREMENTAL_HPP
#define INCREMENTAL_HPP

#include "../headers/cgalConfig.hpp"

#define SORT_BY_X_ASC  "1a"
#define SORT_BY_X_DESC  "1b"
#define SORT_BY_Y_ASC  "2a"
#define SORT_BY_Y_DESC  "2b"

#define RANDOM_EDGE_SELECTION 1
#define MIN_AREA_EDGE_SELECTION 2
#define MAX_AREA_EDGE_SELECTION 3

namespace incremental {
	void incrementalAlgorithm(std::vector<Point_2> &points, char *initialization, int edgeSelection, Polygon_2 &polygon);
	void getConvexHullPolygonFromPoints(const Polygon_2::Vertices &vertices, Polygon_2 &convexHullPolygon);
	//void incrementalAlgorithm(std::vector<Point_2> &Points, char *initialization, int edgeSelection, std::ofstream &outFile);
}

bool isRedEdge(const Polygon_2::Edge_const_iterator edge, Point_2 &newPoint, Polygon_2 &polygon);

bool isVisibleEdge(Polygon_2 &polygon, Point_2 &begin, Point_2 &end, const Point_2 &newPoint);

void insertNewPointToPolygon(Polygon_2 &polygon, const Point_2 &begin, const Point_2 &end, Point_2 newPoint);

int randomSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

int minAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

int maxAreaSelectEdge(std::vector<Segment_2> &visibleEdges, Point_2 newPoint);

#endif