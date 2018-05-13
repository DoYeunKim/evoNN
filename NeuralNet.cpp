#include <cstdlib>
#include <math.h>
#include "NeuralNet.hpp"

using namespace std;

double activationFunction(double x) {
	return 1.0 / (1 + exp(-x + SHIFT_DEFAULT));
}

double derivAF(double x) {
	double gOfIn = activationFunction(x);
	return gOfIn * (1 - gOfIn);
}

double doubleInRange(double lower, double upper) {
	double randNum = rand() / ((double) RAND_MAX);
	return lower + randNum * (upper - lower);
}

NeuralNet::NeuralNet() {
	lRate = DEF_LRATE;
	initOutput();
	setEdges(DEF_IN);
}

NeuralNet::NeuralNet(int input) {
	lRate = DEF_LRATE;
	initOutput();
	setEdges(input);
}

NeuralNet::NeuralNet(double learningRate, int input) {
	lRate = learningRate;
	initOutput();
	setEdges(input);
}

NeuralNet::NeuralNet(vector<edge>& inheritedE) {
	lRate = DEF_LRATE;
	initOutput();
	edges = inheritedE;
}

NeuralNet::~NeuralNet() {

};

// Train the weight of each edge using the evaluation
void NeuralNet::trainWeights(vector<double> input) {
	vector<double> eval = evalMovement(input);

	int numEdge = edges.size();
	edge curr;
	for (int i = 0; i < numEdge; i++) {
		curr = edges[i];
		edges[i].weight = curr.weight + (lRate * inputLayer[curr.input] * eval[curr.output] * derivAF(weightSums[curr.output]));
	}
	
}

vector<double> NeuralNet::evalMovement(vector<double> input) {
	vector<double> eval(OUT_SIZE, 0);

	// Obtain the mean value of the visible field
	double max = -1;
	double sum = 0;
	for (auto mov : input) {
		if (mov > max) {
			max = mov;
		};
		sum += mov;
	}

	double mean = sum / OUT_SIZE;
	double standard = max - mean;
	for (int i = 0; i < OUT_SIZE; i++) {
		eval[i] = input[i] - standard;
		// cout << "Evaluation for tile " << i << ": " << eval[i] << endl;
	}

	return eval;
}

double NeuralNet::testInput(vector<double> input) {
	// Read in the input layer
	inputLayer.clear();
	inputLayer = input;

	// Add Bias node
	inputLayer.push_back(BIAS);
	
	// Need to calculate weights for each edge
	int numEdges = edges.size();

	// Clear and resize weightSums
	weightSums.clear();
	weightSums.resize(OUT_SIZE, 0);

	// Get sum of all inputs and wieghts for each output node
	for (int i = 0; i < numEdges; i++) {
		edge e = edges[i];
		double input = inputLayer[e.input];
		weightSums[e.output] += input * e.weight;
	}

	// Calculate output node value based on inputs and edge weights through activation function
	for (int i = 0; i < OUT_SIZE; i++) {
		outputLayer[i] = activationFunction(weightSums[i]);
		// cout << "Output value for node " << i << ": " << outputLayer[i] << endl;
	}

	// Return the most activated output node
	double max = 0;
	int maxIndex = -1;

	for (int i = 0; i < OUT_SIZE; i++) {
		if (outputLayer[i] > max) {
			max = outputLayer[i];
			maxIndex = i;
		}
	}
	// cout << "Moving by the cardinal direction of: " << maxIndex << endl;
	return maxIndex;
}

// Set the edges
void NeuralNet::setEdges(int input) {
	// Clear the edges 
	edges.clear();

	int inputs = input;

	edge working;
	// For each output
	for (int i = 0; i < OUT_SIZE; i++) {
		working.output = i;
	
		// Acount for bias node
		for (int j = 0; j < inputs + BIAS; j++) {
			working.input = j;
			// Assign random value b/w -EDGE_INIT and EDGE_INIT to weight
			working.weight = doubleInRange(-EDGE_INIT, EDGE_INIT);
			edges.push_back(working);
		}
	}
}

void NeuralNet::initOutput() {
	vector <double> vect (OUT_SIZE, 0.0);
	outputLayer = vect;
}
