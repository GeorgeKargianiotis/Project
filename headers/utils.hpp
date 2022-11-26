#ifndef UTILS_HPP
#define UTILS_HPP

#include "../headers/cgalConfig.hpp"

namespace utils{

	std::vector<std::string> splitString(std::string &str, char delimiter); 

	void writeToOutputFile(std::ofstream &outFile, std::vector<Point_2> &points, Polygon_2 &polygon, Polygon_2 &convexHullPolygon, int edgeSelection, int polygonArea, const int64_t &executionTime, char* initialization = nullptr);

	void polygonToPythonArray(Polygon_2 &polygon, const std::string &name = "polygon");
	void vectorToPythonArray(std::vector<Point_2> &points);
	void printOutput(Polygon_2 &polygon, std::vector<Point_2> &points, Polygon_2 &convexHullPolygon, std::vector<Segment_2> &redEdges, std::vector<Segment_2> &visibleEdges, Point_2 &newPoint);
	
	bool cmp1aPoint2(Point_2 &point1, Point_2 &point2);
	bool cmp1bPoint2(Point_2 &point1, Point_2 &point2);
	bool cmp2aPoint2(Point_2 &point1, Point_2 &point2);
	bool cmp2bPoint2(Point_2 &point1, Point_2 &point2);

	void local_search_algorithm(Polygon_2 greedypolygon, std::ofstream &outFile, int L, char* area, double threshhold);
	void simulated_annealing_algorithm(Polygon_2 greedypolygon, std::ofstream &outFile);	
}

#endif