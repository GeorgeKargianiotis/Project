#ifndef UTILS_HPP
#define UTILS_HPP

#include "../headers/cgalConfig.hpp"

namespace utils{
	std::vector<std::string> splitString(std::string &str, char delimiter); 

	bool cmpPoint2(Point_2 &point1, Point_2 &point2);
}

#endif