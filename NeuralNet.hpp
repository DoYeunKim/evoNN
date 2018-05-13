#ifndef NEURAL_NET_HPP
#define NEURAL_NET_HPP

#include <iostream>
#include <vector>
#define OUT_SIZE 9
#define DEF_IN 8
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
		enum {N, NE, E, SE, S, SW, W, NW, P};
		double lRate;

		vector<double> outputLayer;
		vector<double> weightSums;


	public:
		NeuralNet();
		NeuralNet(int input);
		NeuralNet(double learningRate, int input);
		NeuralNet(vector<edge>& inheritedE);
		~NeuralNet();

		vector<double> evalMovement(vector<double> input);
		double testInput(vector<double> input);
		void trainWeights(vector<double> input);
		void initOutput();
		void setEdges(int input);
		vector<double> inputLayer;
		vector<edge> edges;
};


#endif
