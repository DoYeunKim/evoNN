#include "World.h"
#include <time.h>

using namespace std;

// Initialize the world with inate numbers and create the map
World::World() {
	mapSize = defaultSize;
	amountFood = defaultFood;
	popSize = defaultPop;
	cout << "Creating a world that is " << mapSize << " x " << mapSize << " in size" << endl;

	for(int i = 0; i < mapSize; i++) {
		vector<int> row(mapSize, NIL);
		map.push_back(row);
	}
}

// Initialize the world with provided numbers and create the map
World::World(int dim, int f, int c) {
	mapSize = dim;
	amountFood = f;
	popSize = c;
	cout << "Creating a world that is " << mapSize << " x " << mapSize << " in size" << endl;
	
	for(int i = 0; i < mapSize; i++) {
		vector<int> row(mapSize, NIL);
		map.push_back(row);
	}
}

// Delete map
World::~World() {
}

// Populate the world with food
// Until the quota of food is met, populate the map, checking for collision
void World::populateFood() {
	int x, y;
	int currAmount = foods.size();
	// Until the quota is met
	while (currAmount != amountFood) {
		// Random seed
		srand(time(NULL));
		x = rand() % mapSize;
		y = rand() % mapSize;
		// If there is nothing at the map coordinate
		// Create new food and put it there
		if (map[x][y] == NIL) {
			food *f = new food; f->f_x = x; f->f_y = y;
			foods.push_back(*f);
			map[x][y] = FOOD;
			currAmount++;
		}
	}
}

// Populate the world with creatures
// Until the quota of creatures is met, populate the map, checking for collision
void World::populateCreature() {
	int x, y;
	int currNum = creatures.size();
	// Until the quota is met
	while (currNum != popSize) {
		// Random seed
		srand(time(NULL));
		x = rand() % mapSize;
		y = rand() % mapSize;
		// If there is nothing at the map coordinate
		// Create new creature and put it there
		if (map[x][y] == NIL) {
			Creature c;
			c.c_x = x;
			c.c_y = y;
			creatures.push_back(c);
			map[x][y] = CREATURE;
			//cout << "(" << x << "," << y << ")" << endl;
			currNum++;
		}
	}
	/*
	for (vector<Creature>::iterator it = creatures.begin(); it != creatures.end(); it++) {
		cout << it->c_x << "," << it->c_y << endl;
	}
	*/
}

// Show the world so that we can know what is going on
void World::showWorld() {
	cout << endl << "Displaying a world that is " << mapSize << " x " << mapSize << " in size" << endl;
	for (int i = 0; i < mapSize; i++) {
		for (int j = 0; j < mapSize; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

// Check if there is anything at (x,y)
// If (x,y) is out of bounds or if another creature is there, then we can't go there
bool World::showPos(int x, int y){
	bool canMove = false;
	
	// Check for bounds
	if (mapSize <= x || x < 0) { 
		cout << "Out of bounds! " << endl;
		return canMove; 
	}
	else if (mapSize <= y || y < 0) { 
		cout << "Out of bounds! " << endl;
		return canMove; 
	}

	// Based on what is already at (x,y)
	switch(map[x][y]) {
		// If there is nothing, we can move there
		case NIL: {
					cout << "There is nothing here" << endl; 
					canMove = true; 
					break;
					}
		// If there is food, we can move there
		// We want to remove this food because it is now eaten
		// Right now iterating through food, but maybe I should make foods a map instead of vector
		case FOOD: {
					cout << "There is food here" << endl; 
					canMove = true;

					for (vector<food>::iterator it = foods.begin(); it != foods.end(); it++) {
						if (x == it->f_x && y == it->f_y) {
							foods.erase(it);
						} 						
					}

					break;
					}
		// If there is creature, we can't move there as of now
		// The current creatures only eat food, but as I add more species that will hopefully learn to hunt
		// I will add more cases
		case CREATURE: {
						cout << "There is a creature here" << endl; 
						break;
						}
	}
	// Let the creature know if it can move
	return canMove;
}

// Move the creature, using Creature::move()
// For each creature, check if it can move to the new (x,y), and if it can, move
// Right now the amount of movement is randomized
// When the animal moves, update the map to be NIL - this part is not working....
void World::moveCreatures() {
	int dx, dy, x, y, n_x, n_y;
	
	// Iterate through creatures
	for (vector<Creature>::iterator it = creatures.begin(); it != creatures.end(); it++) {
		cout << "Was at (" << it->c_x << "," << it->c_y << ")" << endl;

		// Calculating dx and dy
		// This will be provided by NN as I move along
		dx = 1 - (rand() % 3);
		dy = 1 - (rand() % 3);
		x = it->c_x;
		y = it->c_y;
		n_x = (it->c_x) + dx;
		n_y = (it->c_y) + dy;

		// If we can move into the new position
		// Move and update the map	
		if(showPos(n_x, n_y)) {
			it->move(dx, dy);
			cout << "The Creature is moving" << endl;
			map[n_x][n_y] = CREATURE;
			cout << "Moved Creature" << endl;
			map[x][y] = NIL;
			cout << "Updated Map" << endl;
		}
		cout << "Now at (" << it->c_x << "," << it->c_y << ")" << endl;
		
	}
	cout << endl;
	
	// Call populate food
	// If the creatures ate something, food will be repopulated
	// Else, nothing happens
	// I will probably stagnate this as we may not want indefinite abundance of creatures
	populateFood();
}

