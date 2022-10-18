#include <iostream>
#include <string>

void readArguments(int &argc, char* argv[]);

char *inputFiles, *outputFile, *algorithm, *edgeSelection, *initialization;

int main(int argc, char* argv[]){
	readArguments(argc, argv);
	return 0;
}


void readArguments(int &argc, char* argv[]){
	if(argc != 11){
		std::cerr << "Λάθος αριθμός ορισμάτων. " << std::endl;
		std::cerr << "$./polygonization –i <point set input file> –ο <output file> –algorithm <incremental or convex_hull or onion> -edge_selection <1 or 2 or 3 | όχι στο onion> -initialization <1a or 1b or 2a or 2b | μόνο στον αυξητικό αλγόριθμο> -onion_initialization <1 to 5>" << std::endl;
	}

	for(int i = 1; i < argc; i += 2){

		if(std::string(argv[i]).compare("-i") == 0){
			inputFiles = argv[i+1];
			continue;
		}

		if(std::string(argv[i]).compare("-o") == 0){
			outputFile = argv[i+1];
			continue;
		}

		if(std::string(argv[i]).compare("-algorithm") == 0){
			algorithm = argv[i+1];
			continue;
		}
			
		if(std::string(argv[i]).compare("-edge_selection") == 0){
			edgeSelection = argv[i+1];
			continue;
		}

		if(std::string(argv[i]).compare("-initialization") == 0){
			inputFiles = argv[i+1];
			continue;
		}
	}
}