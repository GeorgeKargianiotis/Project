#include <vector>
#include <string>

#include "../headers/utils.hpp"

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

bool utils::cmpPoint2(Point_2 &point1, Point_2 &point2){
	return point1.hx() < point2.hx();
}