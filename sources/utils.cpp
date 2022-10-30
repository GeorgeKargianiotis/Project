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

// this function prints the polygon's points as a python array to plot the polygon with matplotlib.
void utils::polygonToPythonArray(Polygon_2 &polygon){
	for(Point_2 point : polygon)
		std::cout << "[" << point.hx() << "," << point.hy() << "],";  
	std::cout << std::endl;
}

// this function prints the vector's points as a python array to plot the polygon with matplotlib.
void utils::vectorToPythonArray(std::vector<Point_2> &points){
	for(Point_2 point : points)
		std::cout << "[" << point.hx() << "," << point.hy() << "],";  
	std::cout << std::endl;
}

bool utils::cmp1aPoint2(Point_2 &point1, Point_2 &point2){
	return point1.hx() < point2.hx();
}

bool utils::cmp1bPoint2(Point_2 &point1, Point_2 &point2){
	return point1.hx() > point2.hx();
}

bool utils::cmp2aPoint2(Point_2 &point1, Point_2 &point2){
	return point1.hy() < point2.hy();
}

bool utils::cmp2bPoint2(Point_2 &point1, Point_2 &point2){
	return point1.hy() > point2.hy();
}