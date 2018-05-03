#include "World.h"
#include "Creature.h"
#include <ctime>

#define ITERATIONS  10

using namespace std;

int main() {

	clock_t start;
	double duration;

	int m,f,c;
	m = 10;
	f = 20;
	c = 10;

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

    world.showWorld();

	for (int i = 0; i < ITERATIONS; i++) {
		world.moveCreatures();
		cout << "Iteration " << i << endl;
		world.showWorld();
	}

	return 0;

}
