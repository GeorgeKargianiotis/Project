#include <iostream>
#include <vector>
#include <string>
#include <fstream>

#include "headers/utils.hpp"
#include "headers/incremental.hpp"
#include "headers/convex_hull.hpp"
#include "headers/local_search.hpp"
#include "headers/simulated_annealing.hpp"
#include "headers/cgalConfig.hpp"

void readArguments(int argc, char* argv[], bool &max, bool &min);

char *inputFile, *outputFile, *algorithm, *L, *threshold, *annealing;

int main(int argc, char* argv[]){

	bool max, min;
	readArguments(argc, argv, max, min);
	std::ifstream inFile(inputFile);
	std::ofstream outFile(outputFile);
	std::string line;
	std::vector<Point_2> points;

	//ignore first two lines
	std::getline(inFile, line);
	std::getline(inFile, line);

	while(std::getline(inFile, line)){
		std::vector<std::string> split = utils::splitString(line, '\t'); 
		points.push_back(Point_2(std::stod(split[1]), std::stod(split[2])));
	}

	inFile.close();

	//get the starting simple polygon
	char initialization[2] = {'2', 'a'};
	Polygon_2 polygon;
	//incremental::incrementalAlgorithm(points, initialization, 2, polygon);

	if(std::string(algorithm).compare("simulated_annealing") == 0){
		if(std::string(annealing).compare("subdivision") != 0)
			simulated_annealing::simulatedAnnealing(points, annealing, max, std::stoi(L));
		else
			simulated_annealing::simulatedAnnealingWithSubdivision(points, max);
	}

	outFile.close();

	return 0;
}

void readArguments(int argc, char* argv[], bool &max, bool &min){
	if(argc != 12){
		std::cerr << "Λάθος αριθμός ορισμάτων." << std::endl;
		std::cerr << "$./optima_polygon –i <point set input file> –ο <output file> –algorithm <local_search or simulated_annealing> -L [L parameter according to algorithm] –max [maximal area polygonization] –min [minimal area polygonization] –threshold <double> [in local search] –annealing <'local' or 'global' or 'subdivision' in simulated annealing>" << std::endl;
		exit(EXIT_FAILURE);
	}

	for(int i = 1; i < argc; i += 2){

		if(std::string(argv[i]).compare("-i") == 0)
			inputFile = argv[i+1];
		else if(std::string(argv[i]).compare("-o") == 0)
			outputFile = argv[i+1];
		else if(std::string(argv[i]).compare("-algorithm") == 0){
			if(std::string(argv[i+1]).compare("local_search") != 0 && std::string(argv[i+1]).compare("simulated_annealing") != 0){
				std::cerr << "Argument algorithm is wrong. Please insert either local_search or simulated_annealing\n";
				exit(1);
			}
			algorithm = argv[i+1];
		}
		else if(std::string(argv[i]).compare("-L") == 0)
			L = argv[i+1];
		else if(std::string(argv[i]).compare("-max") == 0){
			max = true;
			i--;
		}
		else if(std::string(argv[i]).compare("-min") == 0){
			min = true;
			i--;
		}
		else if(std::string(argv[i]).compare("-threshold") == 0)
			threshold = argv[i+1];
		else if(std::string(argv[i]).compare("-annealing") == 0){
			if(std::string(argv[i+1]).compare("local") != 0 && std::string(argv[i+1]).compare("global") != 0 && std::string(argv[i+1]).compare("subdivision") != 0){
				std::cerr << "Argument annealing is wrong. Please insert local/global/subdivision\n";
				exit(1);
			}
			annealing = argv[i+1];
		}
		else{
			std::cout << "Wrong argument " << argv[i] << std::endl;
			exit(EXIT_FAILURE);
		}
	}

	if(std::string(algorithm).compare("local_search") == 0 && threshold == nullptr){
		std::cerr << "You must enter argument 'threshold' for local_search algorithm\n";
		exit(1);
	}
	if(std::string(algorithm).compare("simulated_annealing") == 0 && annealing == nullptr){
		std::cerr << "You must enter argument 'annealing' for simulated_annealing algorithm\n";
		exit(1);
	}

	if(!max && !min){
		std::cerr << "You set max or min argument\n";
		exit(1);
	}
}