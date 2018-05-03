#include "World.h"
#include <time.h>

using namespace std;

World::World() {
	mapSize = defaultSize;
	amountFood = defaultFood;
	popSize = defaultPop;
	cout << "Creating a world that is " << mapSize << " x " << mapSize << " in size" << endl;

	for (int i = 0; i < defaultSize; i++) {
		vector<int> row(defaultSize, NIL);
		map.push_back(row);		
	}
}

World::World(int dim, int f, int c) {
	mapSize = dim;
	amountFood = f;
	popSize = c;
	cout << "Creating a world that is " << mapSize << " x " << mapSize << " in size" << endl;

	for (int i = 0; i < dim; i++) {
		vector<int> row(dim, NIL);
		map.push_back(row);
	}
}

World::~World() {

}

void World::populateFood() {
	int x, y;
	int currAmount = foods.size();
	while (currAmount != amountFood) {
		srand(time(NULL));
		x = rand() % mapSize;
		y = rand() % mapSize;
		if (map[x][y] == NIL) {
			food *f = new food; f->f_x = x; f->f_y = y;
			foods.push_back(*f);
			map[x][y] = FOOD;
			currAmount++;
		}
	}
}

void World::populateCreature() {
	int x, y;
	int currNum = creatures.size();
	while (currNum != popSize) {
		srand(time(NULL));
		x = rand() % mapSize;
		y = rand() % mapSize;
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

bool World::showPos(int x, int y){
	bool canMove = false;
	
	if (mapSize <= x || x < 0) { 
		cout << "Out of bounds! " << endl;
		return canMove; 
	}
	else if (mapSize <= y || y < 0) { 
		cout << "Out of bounds! " << endl;
		return canMove; 
	}

	switch(map[x][y]) {
		case NIL: {
					cout << "There is nothing here" << endl; 
					canMove = true; 
					break;
					}
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
		case CREATURE: {
						cout << "There is a creature here" << endl; 
						break;
						}
	}

	return canMove;
}

void World::moveCreatures() {
	int dx, dy, x, y;
	
	for (vector<Creature>::iterator it = creatures.begin(); it != creatures.end(); it++) {
		cout << "Was at (" << it->c_x << "," << it->c_y << ")" << endl;
		dx = 1 - (rand() % 3);
		dy = 1 - (rand() % 3);
		x = (it->c_x) + dx;
		y = (it->c_y) + dy;
		
		if(showPos(x, y)) {
			it->move(dx, dy);
			map[x][y] = NIL;
			cout << "The Creature is moving" << endl;
			map[it->c_x][it->c_y] = CREATURE;
						
		}
		cout << "Now at (" << it->c_x << "," << it->c_y << ")" << endl;
		
	}
	cout << endl;
	
	populateFood();
}

