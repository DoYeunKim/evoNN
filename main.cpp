#include "World.h"
#include "Creature.h"

int main() {

    World world1;
    //World world2(50, 100);

    world1.populateFood();
    //world2.populateFood();

    world1.showWorld();
	//world2.showWorld();

	Creature c1;
	Creature c2(2, 15);

	c1.showInfo();
	c2.showInfo();
}
