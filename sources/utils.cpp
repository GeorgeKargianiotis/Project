#include <vector>
#include <string>

#include "../headers/utils.h"

std::vector<std::string> splitString(std::string str, char delimiter = ' '){
	std::vector<std::string> split;

	int begin = 0;
	int end = str.find(delimiter);
	while(end != -1){
		split.push_back(str.substr(begin, end));
		begin += end;
		end = str.find(delimiter);
	}
	
	return split;
}