#include <string>
#include <sstream> // istringstream
#include <fstream> // ifstream
#include "World.hpp"
//#include <ctime>

#define ITERATIONS 50

using namespace std;

vector< vector<double> > readMap(string inputName) {

	vector< vector<double> > inputMap;
	ifstream inputFile(inputName.c_str());
	int i = 0;

	while (inputFile) {
		i++;
		string s;

		if (!getline(inputFile, s)) break;

		if (s[0] != '#') {
			istringstream ss (s);
			vector<double> row;

			while (ss) {
				string curr;

				if (!getline(ss, curr, ',')) break;

				try {
					row.push_back(stof(curr));
				} catch (const invalid_argument e) {
					cout << "NaN found in file " << inputName << endl;
					e.what();
				}				
			}
			inputMap.push_back(row);
		}
	}
	
	if (!inputFile.eof()) {
		cerr << "Could not read file " << inputName << "\n";
		__throw_invalid_argument("File not found");
	}

	return inputMap;
}

int main() {

	// clock_t start;
	// double duration;
	
	vector< vector<double> > inputMap = readMap("5x5_map.csv");

	for (auto l: inputMap) {
		for (auto x : l) {
			cout << x << " ";
		}
		cout << endl;
	}


	/*
	int m,f,c;
	m = 10;
	f = 30;
	c = 1;

	// Check for illegal world
	if (f < 1 || c < 1) {
		cout << "We need at least one food and one creature to work with." << endl;
		return -1;
	}
	else if ((m * m) < (f + c)) {
		cout << "The sum of food and creatures cannot exceed the amount of space provided in this world." << endl;
		return -1;
	} 

	World world(m, f, c);
    
	world.populateFood();
	world.populateCreature();

	cout << "Displaying a world that is " << m << " x " << m << " in size" << endl;
    world.showWorld();

	for (int i = 0; i < ITERATIONS; i++) {
		if (world.moveCreatures()) {
			cout << "Iteration " << i << endl;
			world.showWorld();
		} else {
			cout << "World terminated " << endl;
			break;
		}
	}
	*/

	return 0;

}
