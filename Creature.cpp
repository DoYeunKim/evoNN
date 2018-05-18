#include "Creature.hpp"

using namespace std;

// By default, place the creature at (0,0)
Creature::Creature() {
    c_x = c_y = 0;
	NeuralNet NN();
}

// Place the creature at (x,y)
Creature::Creature(int x, int y) {
    c_x = x;
    c_y = y;
	int visAx = 2 * vision + 1; // Each side of the square visual field is 2 * vision + 1 (e.g. 5 for vision = 1)
	int visInput = 2 * visAx * visAx; // Multiply by 2 because we have nourishment and danger to account for
	// cout << "The size of input layer is: " << visInput << endl;
	NeuralNet NN(visInput);
}

Creature::Creature(int x, int y, vector<edge>& inheritedE) {
	c_x = x;
	c_y = y;
	vector<edge> e = inheritedE;
	NeuralNet NN(e);
}

Creature::~Creature() {

}

// Show the relevant information
void Creature::showInfo() {
	cout << "Position: (" << c_x << "," << c_y << ")" << endl;
	cout << "Fitness: " << fitness << endl;
	cout << "Health: " << health << endl;
	cout << "Speed: " << speed << endl;
	cout << "Vision: " << vision << endl;
	cout << "Energy Level: " << energy << endl;
	cout << "Starving?: " << (starving ? "Yes" : "No") << endl;

}

// Move the animal by dx and dy
// Reduce energy level
void Creature::move(int dir) {
	int d = dir;

	displace dis;
	dis = cardinalToDisplace(d);

	c_x += (dis.dx) * speed;
	c_y += (dis.dy) * speed;
	// cout << "Moving by (" << dis.dy << "," << dis.dx << ")" << endl;
	if (dis.dx + dis.dy > 0) {
		energy -= walkEnergy;
	}
}

