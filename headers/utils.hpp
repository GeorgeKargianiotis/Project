#ifndef UTILS_HPP
#define UTILS_HPP

#include "../headers/cgalConfig.hpp"

namespace utils{

	std::vector<std::string> splitString(std::string &str, char delimiter); 

	void writeToOutputFile(std::ofstream &outFile, std::vector<Point_2> &points, Polygon_2 &polygon, Polygon_2 &convexHullPolygon, int edgeSelection, char* initialization, int polygonArea, const int64_t &executionTime);

	void polygonToPythonArray(Polygon_2 &polygon, const std::string &name = "polygon");
	void vectorToPythonArray(std::vector<Point_2> &points);
	
	bool cmp1aPoint2(Point_2 &point1, Point_2 &point2);
	bool cmp1bPoint2(Point_2 &point1, Point_2 &point2);
	bool cmp2aPoint2(Point_2 &point1, Point_2 &point2);
	bool cmp2bPoint2(Point_2 &point1, Point_2 &point2);
}

#endif