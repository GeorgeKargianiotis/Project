#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "headers/utils.hpp"
#include "headers/incremental.hpp"
#include "headers/convex_hull.hpp"
#include "headers/cgalConfig.hpp"

void readArguments(int &argc, char* argv[]);

char *inputFile, *outputFile, *algorithm, *initialization, *edgeSelection;
Polygon_2 polygon;

int main(int argc, char* argv[]){
	readArguments(argc, argv);
	std::ifstream inFile(inputFile);
	std::ofstream outFile(outputFile);
	std::string line;
	std::vector<Point_2> Points2;

	//ignore first two lines
	std::getline(inFile, line);
	std::getline(inFile, line);

	while(std::getline(inFile, line)){
		std::vector<std::string> split = utils::splitString(line, '\t'); 
		Points2.push_back(Point_2(std::stod(split[1]), std::stod(split[2])));
	}

	inFile.close();

	if(std::string(algorithm).compare("incremental") == 0)
		incremental::incrementalAlgorithm(Points2, initialization, std::stoi(edgeSelection), outFile, polygon);

	// Need int for convex hull edges
	if(std::string(algorithm).compare("convex_hull") == 0)
		convex_hull::convex_HullAlgorithm(Points2, std::stoi(edgeSelection), outFile);

	outFile.close();

	return 0;
}

// EDIT READ ARGUMENTS TO INCLUDE EXTRA AGRUMENTS FOR 2ND PART OF PROJECT
void readArguments(int &argc, char* argv[]){
	if(argc != 11 && argc != 9){
		std::cerr << "Λάθος αριθμός ορισμάτων. " << std::endl;
		std::cerr << "$./polygonization –i <point set input file> –ο <output file> –algorithm <incremental or convex_hull> -edge_selection <1 or 2 or 3 | όχι στο onion> -initialization <1a or 1b or 2a or 2b | μόνο στον αυξητικό αλγόριθμο>" << std::endl;
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i < argc; i += 2){

		if(std::string(argv[i]).compare("-i") == 0)
			inputFile = argv[i+1];
		else if(std::string(argv[i]).compare("-o") == 0)
			outputFile = argv[i+1];
		else if(std::string(argv[i]).compare("-algorithm") == 0)
			algorithm = argv[i+1];
		else if(std::string(argv[i]).compare("-edge_selection") == 0)
			edgeSelection = argv[i+1];
		else if(std::string(argv[i]).compare("-initialization") == 0)
			initialization = argv[i+1];
		else{
			std::cout << "Wrong argument " << argv[i] << std::endl;
			exit(EXIT_FAILURE);
		}
	}
}