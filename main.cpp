#include "World.h"
#include "Creature.h"
#include <ctime>

#define ITERATIONS  10

using namespace std;

int main() {

	clock_t start;
	double duration;

	World world(50, 50, 10);
    
	world.populateFood();
	world.populateCreature();

    world.showWorld();

	for (int i = 0; i < ITERATIONS; i++) {
		world.moveCreatures();
		cout << "Iteration " << i << endl;
		world.showWorld();
	}


}
