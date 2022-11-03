#include <vector>
#include <string>

#include "../headers/utils.hpp"
#include "../headers/cgalConfig.hpp"

std::vector<std::string> utils::splitString(std::string &str, char delimiter = ' '){
	std::vector<std::string> split;

	int begin = 0;
	int end = str.find(delimiter);
	while(end != -1){
		split.push_back(str.substr(begin, end - begin));
		begin = end + 1;
		end = str.find(delimiter, begin);
	}

	split.push_back(str.substr(begin, str.length()));
	
	return split;
}


void utils::writeToOutputFile(std::ofstream &outFile, std::vector<Point_2> &points, Polygon_2 &polygon, Polygon_2 &convexHullPolygon, int edgeSelection, char* initialization, int polygonArea, const int64_t &executionTime){
	//wirite polygon's points
	for(Point_2 point : points)
		outFile << point.x() << " " << point.y() << "\n"; 
	
	//write polygon's edges
	for(Polygon_2::Edge_const_iterator edge = polygon.edges().begin(); edge != polygon.edges().end(); edge++)
		outFile << edge->start() << " " << edge->end() << "\n";

	outFile << "Alogrithm: incremental edge_selection " << edgeSelection << " initilization " << *initialization << "\n";  

	outFile << "area: " << polygonArea << "\n";

	outFile << "ratio: " << polygonArea / convexHullPolygon.area() << "\n";

	outFile << "construction time: " << executionTime << " ms\n";
}

// this function prints the polygon's points as a python array to plot the polygon with matplotlib.
void utils::polygonToPythonArray(Polygon_2 &polygon, const std::string &name){
	std::cout << name << " = [\n";
	for(Point_2 point : polygon)
		std::cout << "[" << point.hx() << "," << point.hy() << "],";  
	std::cout << "\b \b";
	std::cout << "\n]\n";
}

// this function prints the vector's points as a python array to plot the polygon with matplotlib.
void utils::vectorToPythonArray(std::vector<Point_2> &points){
	for(Point_2 point : points)
		std::cout << "[" << point.hx() << "," << point.hy() << "],";  
	std::cout << std::endl;
}

bool utils::cmp1aPoint2(Point_2 &point1, Point_2 &point2){
	if(point1.x() < point2.x())
		return true;
	else if(point1.x() > point2.x())
		return false;
	else{
		if(point1.y() < point2.y())
			return true;
		else
			return false;
	}
}

bool utils::cmp1bPoint2(Point_2 &point1, Point_2 &point2){
	if(point1.x() > point2.x())
		return true;
	else if(point1.x() < point2.x())
		return false;
	else{
		if(point1.y() < point2.y())
			return true;
		else
			return false;
	}
}

bool utils::cmp2aPoint2(Point_2 &point1, Point_2 &point2){
	if(point1.y() < point2.y())
		return true;
	else if(point1.y() > point2.y())
		return false;
	else{
		if(point1.x() < point2.x())
			return true;
		else
			return false;
	}
}

bool utils::cmp2bPoint2(Point_2 &point1, Point_2 &point2){
	if(point1.y() > point2.y())
		return true;
	else if(point1.y() < point2.y())
		return false;
	else{
		if(point1.x() < point2.x())
			return true;
		else
			return false;
	}
}
