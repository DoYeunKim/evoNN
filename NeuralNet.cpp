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

NeuralNet::NeuralNet(vector<edge> inheritedE, double learningRate) {
	lRate = learningRate;
	initOutput();
	edges = inheritedE;
}

NeuralNet::~NeuralNet() {

};

void NeuralNet::trainWeights() {

}

double NeuralNet::testInput() {

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
