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
	NeuralNet NN();
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
	int dx, dy;

	displace dis;
	dis = cardinalToDisplace(d);

	c_x += (dis.dx) * speed;
	c_y += (dis.dy) * speed;
	cout << "Moving by (" << dx << "," << dy << ")" << endl;
	energy -= walkEnergy;
}

