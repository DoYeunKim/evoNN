#include "World.hpp"


using namespace std;

void World::initWorld(vector< vector<double> >& i_map) {
	mapY = i_map.size();
	if (mapY <= 0) { 
		cout << "Illegal number of rows for the map ( <= 0)" << endl;
		exit(1);
	}
	mapX = i_map[0].size();

	for (int i = 0; i < mapY; i++) {
		vector<cell> col;
		for (int j = 0; j < mapX; j++) {
			cell *c = new cell;
			c->cellPop = 0;
			c->nourishment = i_map[i][j];
			col.push_back(*c);
		}
		map.push_back(col);
	}

}

// Initialize the world with inate numbers and create the map
World::World() {
	cout << "The world needs to have at least the map input." << endl;
	exit(1);
}

// Initialize the world with just the map
// Use default values
World::World(vector< vector<double> >& inputMap) {
	popSize = survived = DEFAULT_POP;	
	initWorld(inputMap);
	cout << "Creating a world that is " << mapX << " x " << mapY << " in size" << endl;
	populateCreature();
}

// Delete map
World::~World() {
}

// Populate the world with food
// Until the quota of food is met, populate the map, checking for collision
void World::populateFood() {
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
		x = rand() % mapX;
		y = rand() % mapY;
		
		// Create new creature and place it.
		// Update the total number of creatures in the cell
		Creature c(x,y);
		//c.c_x = x;
		//c.c_y = y;
		creatures.push_back(c);
		map[y][x].cellPop++;
		//cout << "(" << x << "," << y << ")" << endl;
		currNum++;
	}
	/*
	for (vector<Creature>::iterator it = creatures.begin(); it != creatures.end(); it++) {
		cout << it->c_x << "," << it->c_y << endl;
	}
	*/
}

// Show the world so that we can know what is going on
void World::showWorld() {
	cout << "---------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < mapY; i++) {
		cout << "|";
		for (int j = 0; j < mapX; j++) {
			printf("%2d, %1.1lf|", map[j][i].cellPop, map[j][i].nourishment);
			// printf("%2.2lf ", map[j][i].nourishment);
		}
		cout << endl;
	}
	cout << "---------------------------------------------------------------------------------" << endl;
	cout << endl;
}

// Check if there is anything at (x,y)
// If (x,y) is out of bounds or if another creature is there, then we can't go there
bool World::showPos(int x, int y){
	bool canMove = true;
	
	// Check for bounds
	if (mapX <= x || x < 0) { 
		cout << "Out of bounds! " << endl;
		return !canMove; 
	}
	else if (mapY <= y || y < 0) { 
		cout << "Out of bounds! " << endl;
		return !canMove; 
	}

	// Let the creature know if it can move
	return canMove;
}

// Move the creature, using Creature::move()
// For each creature, check if it can move to the new (x,y), and if it can, move
// Right now the amount of movement is randomized
// When the animal moves, update the map to be NIL - this part is not working....
bool World::moveCreatures() {
	int x, y, n_x, n_y, dir;
	bool foodEaten = false;
	if (!survived) { return false; }

	// Iterate through creatures
	for (vector<Creature>::iterator it = creatures.begin(); it != creatures.end(); it++) {
		//cout << "Was at (" << it->c_x << "," << it->c_y << ")" << endl;
		if (it->isAlive) {				
	
			// Every turn, they use up 1 energy	
			x = it->c_x;
			y = it->c_y;
			it->energy--;
			double currN = map[y][x].nourishment;
			if (currN >= CONSUME_PER_CREATURE) {
				map[y][x].nourishment -= CONSUME_PER_CREATURE;
				it->energy += ENERGY_INTAKE;
				it->fitness += currN;
				it->starving = 0;
			} else if (currN > 0) {
				map[y][x].nourishment = 0;
				it->energy += ENERGY_INTAKE * (currN/CONSUME_PER_CREATURE);
				it->fitness += currN;
				it->starving = 0;
			}
		
			// If the creature has run out of energy, it is starving
			if (it->energy <= 0) {
				it->starving++;
				cout << "Starving... " << it->starving << endl;
			}

			// If the creature has been starving for 5 turns, then reduce its health
			// If health reaches zero, then it is dead. update the map and break out of the loop
			if (it->starving == STARVATION) {
				it->health--;
				if(it->health <= 0) { 
					it->isAlive = false;
					cout << "This one is dead" << endl;
					survived--;
					map[y][x].cellPop--;		
					continue; 
				}
			}

			it->fitness += map[y][x].nourishment;
			it->NN.inputLayer = calcVision(x, y, it->vision);

			/*
			int k = 0;
			for (auto l : it->NN.inputLayer) {
				if (k == 12) cout << " p  ";
				printf("%1.1lf ", l);
				k++;
			} cout << endl;
			*/

			// Calculating dx and dy
			// This will be provided by NN as I move along
			dir = rand() % 9;
			// cout << dir << endl;
			displace dis;
			dis = cardinalToDisplace(dir);

			n_x = (it->c_x) + dis.dx;
			n_y = (it->c_y) + dis.dy;

			// If the animal can move, the move
			if (showPos(n_x, n_y)) {
				it->move(dir);
				map[y][x].cellPop--;
				map[n_y][n_x].cellPop++;
			}

			//cout << "Now at (" << it->c_x << "," << it->c_y << ")" << endl;
			cout << "Current energy level is " << it->energy << endl;
		}
		
	}
	cout << survived << " creatures survived this round" << endl << endl << endl;

	// Call populate food
	// If the creatures ate something, food will be repopulated
	// Else, nothing happens
	// I will probably stagnate this as we may not want indefinite abundance of creatures
	if (foodEaten) {
		populateFood();
	}
	return true;
}

// Calculate the visual field of the creature at the given location
vector<double> World::calcVision(int x, int y, int v) {
	// cout << "Showing the creature's visual field" << endl;
	vector<double> v_field;
	// cout << "Looking around (" << x << "," << y << ") in radius of " << v << endl;
	// Within the visual range
	for (int i = x - v; i <= x + v; i++) {
		for (int j = y - v; j <= y + v; j++) {
			// Skip the creature's location
			if (i == x && j == y) { 
				cout << " P  ";
				continue; 
			}
			// If out of bounds, put 9 down
			if ( 0 > i || i >= mapX || 0 > j || j >= mapY) {
				v_field.push_back(-1.0);
				cout << "-1. ";
			} else {
				v_field.push_back(map[j][i].nourishment);
				printf("%1.1lf ", map[j][i].nourishment);
			}
		}
		cout << endl;
	}
	cout << endl;
	return v_field;	
}	

