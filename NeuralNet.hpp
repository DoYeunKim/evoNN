#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <iostream>
#include <random>
#include <vector>
#define OUT_SIZE 9 // 8 cardinal directions + curr position
#define DEF_IN 16 //When Vision = 1
#define BIAS 1
#define EDGE_INIT 0.15
#define SHIFT_DEFAULT 0.5
#define DEF_LRATE 0.4

using namespace std;

typedef struct _edge {

	int input, output;
	double weight;

} edge;

class NeuralNet {
	private:
		// Cardinal directions and learning rate
		enum {N, NE, E, SE, S, SW, W, NW, P};
		double lRate;

		// Output layer and weight sums are untouched by superclasses
		vector<double> outputLayer;
		vector<double> weightSums;


	public:
		// Various constructors because I wanted the users to be able to input parameters
		NeuralNet();
		NeuralNet(int input);
		NeuralNet(double learningRate, int input);
		// Used for brain transplants
		NeuralNet(vector<edge>& inheritedE);
		~NeuralNet();

		// Evaluate movement by taking in fitness
		vector<double> evalMovement(vector<double> input);
		// Receive the visual field and compute movement
		double testInput(vector<double> input);
		// Train edge weights
		void trainWeights(vector<double> input);
		// Initialize output - currently the 8 cardinal directions and current position
		void initOutput();
		// Initialize edges
		void setEdges(int input);

		// These two are modified by super classes
		vector<double> inputLayer;
		vector<edge> edges;
};


#endif
