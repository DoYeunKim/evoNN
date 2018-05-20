#include <chrono>
#include <string>
#include <sstream> // istringstream
#include <fstream> // ifstream
#include <thread>
#include <unistd.h> // opterr
#include "World.hpp"
#define EPOCHS 200
#define GENERATIONS 50


using namespace std;

// Function to read in the map, given the name of the csv file
template <typename T>
vector< vector<T> > readMap(string inputName, vector< vector<T> >& inputMap) {
	vector< vector<T> > saveMap;
	// Open ifstream
	ifstream inputFile(inputName.c_str());
	int i = 0;

	while (inputFile) {
		i++;
		string s;
		
		// Skip empty lines
		if (!getline(inputFile, s)) break;

		// If the line is not a comment (#)
		if (s[0] != '#') {
			// Open stringstream
			istringstream ss (s);
			vector<T> row;

			// While stringstream
			while (ss) {
				string curr;

				// Skip ","
				if (!getline(ss, curr, ',')) break;

				// Append the word to the row
				try {
					row.push_back(stof(curr));
				} catch (const invalid_argument e) {
					cout << "NaN found in file " << inputName << endl;
					e.what();
				}				
			}
			// Append the row to the map
			saveMap.push_back(row);
		}
	}


	// Check that the file is valid	
	if (!inputFile.eof()) {
		cerr << "Could not read file " << inputName << "\n";
		__throw_invalid_argument("File not found");
	}

	return saveMap;

}

// Function to output usage for the user
void usage (char* program) {
	cout << program << " usage: " << endl;
	string usage;
	
	usage = "\n\tCommon format for csv's}: For each set of csv's, there is a common format of [{x_dim}x{y_dim}_{minN}x{maxN}_]" 
		"\n\tOptional:"
			"\n\t-c {number of creatures}: The number of creatures per generation (default = 1)"
			"\n\t-e {epochs}: The number of epochs per generation (default = " + to_string(EPOCHS) + ")"
			"\n\t-g {generations}: The number of generations of creatures (default = " + to_string(GENERATIONS) + ")"
			"\n\t-l {learning rate}: Learning rate for weight adjustment (default = 0.5)"
			"\n\t-m {minimum sustainability}: The minimum sustainability score possible for each tile (default = 0.0, [0.0,1.0) )"
			"\n\t-M {maximum sustainability}: The maximum sustainability score possible for each tile (default = 1.0, (0.0,1.0] )"
			"\n\t-s {shift}: Shift in node activation function (default = 0.3)"
			"\n\t-w {weights}: Initial range of connection strength (default = 0.15)"
			"\n\n\t Example: ./evoNN  10x10_0x50.csv -c 10 -e 50 -g 50 -l 0.9 -m 0.0 -M 20.0 \n";

	cout << usage << endl;
	exit(1);
}

// Parse arguments.
// As of now, only the file name is necessary.
void getArgs(int argc, char** argv, string &input, int& numCreature, int& epochs, int& generations, double& learningRate, double& minS, double& maxS, double& shift, double& weight) {
	learningRate = epochs = -1;
	
	opterr = 1;
	char c;
	
	input = argv[1];

	while ((c = getopt(argc, argv, "c:e:l:m:M:s:w:g")) >= 0) {
		switch(c) {
			case 'c':
				numCreature = atoi(optarg);
				break;	
			case 'e':
				epochs = atoi(optarg);
				break;
			case 'g':
				generations = atoi(optarg);
				break;	
			case 'l':
				learningRate = atof(optarg);
				break;
			case 'm':
				if (atof(optarg) >= 1.0 || atof(optarg) < 0.0) {
					usage(argv[0]);
					break;
				} else {
					minS = atof(optarg);
					break;
				}
			case 'M':
				if (atof(optarg) <= 0.0 || atof(optarg) > 1.0) {
					usage(argv[0]);
					break;
				} else {
					maxS = atof(optarg);
					break;
				}
			case 's':
				shift = atof(optarg);
				break;
			case 'w':	
				weight = atof(optarg);
				break;
			case '?':
				usage(argv[0]);
				break;
			default:
				exit(1);	
		}
	}
}

// Converts terrain map, which is fed in as matrix of ints, into a matrix of chars
void convertTerrain(vector< vector<char> >& inputTer, vector< vector<int> >& tempTer) {
	int terrX = tempTer.size();
	int terrY = tempTer[0].size();
	for (int t = 0; t < terrX; t++) {
		vector<char> row;
		for (int u = 0; u < terrY; u++) {
			int terrain = tempTer[t][u];
			switch(terrain) {
				case 0:
					row.push_back('b');
					break;
				case 1:
					row.push_back('m');
					break;
				case 2:
					row.push_back('f');
					break;
			}
		}
		inputTer.push_back(row);
	}
}


int main(int argc, char** argv) {
	
	int mapType = 0;

	int epochs = EPOCHS;
	int numCreature = DEFAULT_POP;
	int generations = GENERATIONS;
	double learningRate = DEF_LRATE;
	double minS = MIN_SUS;
	double maxS = MAX_SUS;
	double shift = SHIFT_DEFAULT;
	double weight = EDGE_INIT;
	string input, inputT, inputN, inputD;
	
	if (argc == 1) usage(argv[0]);

	getArgs(argc, argv, input, numCreature, epochs, generations, learningRate, minS, maxS, shift, weight);
	// clock_t start;
	// double duration;

	inputT = input + "terrain.csv";
	inputN = input + "nourishment.csv";
	inputD = input + "danger.csv";

	vector< vector<double> > inputNour;
	cout << "Reading in the nourishment map" << endl;
	inputNour = readMap(inputN, inputNour);

	vector< vector<double> > inputDan;
	cout << "Reading in the danger map" << endl;
	inputDan = readMap(inputD, inputDan);

	vector< vector<int> > tempTer;
	cout << "Reading in the terrain map" << endl;
	tempTer = readMap(inputT, tempTer);

	
	vector< vector<char> > inputTer;
	convertTerrain(inputTer, tempTer);

	World world(inputTer, inputNour, inputDan);
	cout << "Created world" << endl;
	world.showWorld(1);

	for (int i = 0; i < GENERATIONS; i++) {
		cout << "Generation " << i << endl;
		// world.showWorld(mapType);
		// For each generation of the creatures, move them around for EPOCHS number of time
		for (int j = 0; j < EPOCHS; j++) {
		
			if (world.moveCreatures()) {
				// cout << "Iteration " << j << " of Generation " << i << endl;
				//world.showWorld(mapType);
			} else {
				cout << "World terminated " << endl;
				break;
			}
		}

		// Final evaluation of each of the creatures
		int ind = 0;
		int maxInd = 0;
		double min = 1 <<10;
		double max = -1;
		double sum = 0;
		for (auto l : world.creatures) {
			if (min > l.fitness) {
				min = l.fitness;
			}
			if (max < l.fitness) {
				max = l.fitness;
				maxInd = ind;
			}
			sum += l.fitness;
			// cout << "Final fitness score of creature #" << ind << ": " << l.fitness << endl;
			ind++;
		}
		double mean = sum/(ind + 1);
		// Find the most fit individual and replicate its edges
		cout << "The minimum fitness was " << min << endl;
		cout << "The average fitness was " << mean << endl;
		cout << "The maximum fitness was " << max << endl;
		cout << endl;
		vector<edge> bestEdges = world.creatures[maxInd].NN.edges;

		/*
		cout << "Best edges " << endl;
		for (auto as : bestEdges) {
			cout << as.weight << " ";
		}
		cout << endl << endl;
		*/
		world.showWorld(mapType);		

		world.creatures.clear();
		world.newGenCreatures(bestEdges);
	
		this_thread::sleep_for(chrono::seconds(2));		
	}
	
	return 0;

}
