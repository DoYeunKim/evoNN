#include <cstdlib>
#include <math.h>
#include "NeuralNet.hpp"

using namespace std;

// A simple sigmoidal activation function
double activationFunction(double x) {
	return 1.0 / (1 + exp(-x + SHIFT_DEFAULT));
}

// Derivative of activation function
double derivAF(double x) {
	double gOfIn = activationFunction(x);
	return gOfIn * (1 - gOfIn);
}

// Return a double value of edge weights
double doubleInRange(double lower, double upper) {
	random_device rd; // Obtain random seed for random number engine
	mt19937_64 gen(rd()); // Standard64-bit  mersenne_twister_engine seeded with rd()
	uniform_real_distribution<> dis(lower, upper);
	return dis(gen);
}

// Default Constructor
NeuralNet::NeuralNet() {
	lRate = DEF_LRATE;
	initOutput();
	setEdges(DEF_IN);
}

// Constructor that creates an input layer of given size
NeuralNet::NeuralNet(int input) {
	lRate = DEF_LRATE;
	initOutput();
	setEdges(input);
}

// Constructor that creates an input layer of given size using input learning rate
NeuralNet::NeuralNet(double learningRate, int input) {
	lRate = learningRate;
	initOutput();
	setEdges(input);
}

// Constructor that takes in a vector of edges and "inherits" it.
NeuralNet::NeuralNet(vector<edge>& inheritedE) {
	lRate = DEF_LRATE;
	initOutput();
	edges.clear();
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

// Evaluate the fitness of the movement the creature is making
vector<double> NeuralNet::evalMovement(vector<double> input) {
	int iSize = input.size();
	if (iSize == 0) exit(1);
	vector<double> eval(OUT_SIZE, 0.0);
	// Because input is now nourishment + danger, it is always going to have even number of entries.
	// No need to check for ramainders
	int NDdivide = iSize/2;

	// Obtain the mean value of the visible field
	double maxN = -1.0;
	double sumN = 0.0;
	double maxD = -1.0;
	double sumD = 0.0;

	// Get maximum nourishment and the sum to get average
	for (int i = 0; i < NDdivide; i++) {
		if (input[i] > maxN) maxN = input[i];
		sumN += input[i];
	}
	// Get maximum danger and the sum to get average
	for (int j = NDdivide; j < iSize; j++) {
		if (input[j] > maxD) maxD = input[j];
		sumD += input[j];
	}

	// Reward nourishment
	double meanN = ((double) sumN) / ((double) NDdivide);
	double standardN = maxN - meanN;
	for (int i = 0; i < NDdivide; i++) {
		eval[i] += input[i] - standardN;
	}

	// Penalize danger
	double meanD = ((double) sumD) / ((double) NDdivide);
	double standardD = maxD - meanD;
	
	for (int j = NDdivide; j < iSize; j++) {
		eval[j - NDdivide] -= (input[j] - standardD);
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

// Initialize output to 0.0
void NeuralNet::initOutput() {
	vector <double> vect (OUT_SIZE, 0.0);
	outputLayer = vect;
}
