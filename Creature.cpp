#include "Creature.h"

using namespace std;

// By default, place the creature at (0,0)
Creature::Creature() {
    c_x = c_y = 0;
}

// Place the creature at (x,y)
Creature::Creature(int x, int y) {
    c_x = x;
    c_y = y;
}

// remove creature
// Don't have dynamically allocated objects yet, but will become handy
Creature::~Creature() {
}

// Show the relevant information
void Creature::showInfo() {
	cout << "Position: (" << c_x << "," << c_y << ")" << endl;
	cout << "Fitness: " << fitness << endl;
	cout << "Damage: " << damage << endl;
	cout << "Health: " << health << endl;
	cout << "Speed: " << speed << endl;
	cout << "Vision: " << vision << endl;
	cout << "Energy Level: " << energy << endl;
	cout << "Starving?: " << (starving ? "Yes" : "No") << endl;

}

// Move the animal by dx and dy
// Reduce energy level
void Creature::move(int dx, int dy) {
	c_x += dx * speed;
	c_y += dy * speed;
	cout << "Moving by (" << dx << "," << dy << ")" << endl;
	energy -= 1;
}

