#include "World.hpp"

using namespace std;

void World::initWorld(vector< vector<char> >& t_map, vector< vector<double> >& f_map, vector< vector<double> >& d_map) {
	mapY = f_map.size();
	if (mapY <= 0) { 
		cout << "Illegal number of rows for the map ( <= 0)" << endl;
		exit(1);
	}
	mapX = f_map[0].size();

	for (int i = 0; i < mapY; i++) {
		vector<cell> col;
		for (int j = 0; j < mapX; j++) {
			cell *c = new cell;
			c->cellPop = 0;
			c->nourishment = f_map[i][j];
			c->terrain = t_map[i][j];
			c->danger = d_map[i][j];
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
World::World(vector< vector<char> >& terrainMap, vector< vector<double> >& foodMap, vector< vector<double> >& dangerMap) {
	popSize = survived = DEFAULT_POP;	
	initWorld(terrainMap, foodMap, dangerMap);
	cout << "Creating a world that is " << mapX << " x " << mapY << " in size" << endl;
	populateCreature();
}

// Delete map
World::~World() {
}

// Populate the world with food
// Until the quota of food is met, populate the map, checking for collision
void World::populateFood() {
	for (int i = 0; i < mapY; i++) {
		for (int j = 0; j < mapX; j++) {
			if ((map[j][i].nourishment + DEF_REGEN) > 1.0) {
				map[j][i].nourishment = 1;
			} else {
				map[j][i].nourishment += DEF_REGEN;
			}
		}
	}	
}

// Populate the world with creatures
// Until the quota of creatures is met, populate the map, checking for collision
void World::populateCreature() {
	int x, y;
	int currNum = creatures.size();

	// Seed random and generate random integer for the given input
	random_device r;
	default_random_engine el(r());
	uniform_int_distribution<int> x_dist(0, mapX - 1);	
	uniform_int_distribution<int> y_dist(0, mapY - 1);
	
	// Until the quota is met
	while (currNum != popSize) {
		// Random seed
		x = x_dist(el);
		y = y_dist(el);
		cout << "Creature " << currNum << " placed at (" << x << "," << y << ")" << endl;	

		// Create new creature and place it.
		// Update the total number of creatures in the cell
		Creature c(x,y);
		creatures.push_back(c);
		map[y][x].cellPop++;
		currNum++;
	}
}

// The new generation of creatures
// Until the quota of creatures is met, populate the map, checking for collision
void World::newGenCreatures(vector<edge>& inheritedE) {
	int x, y;
	int currNum = creatures.size();
	
	for (int i = 0; i < mapY; i++) {
		for (int j = 0; j < mapX; j++) {
			map[j][i].cellPop = 0;
		}
	}	
	
	// Seed random and generate random integer for the given input
	random_device r;
	default_random_engine el(r());
	uniform_int_distribution<int> x_dist(0, mapX - 1);	
	uniform_int_distribution<int> y_dist(0, mapY - 1);

	// Until the quota is met
	while (currNum != popSize) {
		// Random seed
		x = x_dist(el);
		y = y_dist(el);
		// cout << "Creature " << currNum << " placed at (" << x << "," << y << ")" << endl;	

		// Create new creature and place it.
		// Update the total number of creatures in the cell
		Creature c(x,y, inheritedE);
		creatures.push_back(c);
		map[y][x].cellPop++;
		currNum++;
	}
}

// Show the world so that we can know what is going on
void World::showWorld(int mapType) {
	int d = mapType;

	switch(d) {
		case 0:
			cout << "# creatures, nourishment, danger, terrain " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%2d,%1.2lf,%1.2lf,%c ", map[j][i].cellPop, map[j][i].nourishment, map[j][i].danger, map[j][i].terrain);
				}
				cout << endl;
			} 
			cout << endl;
			break;
		case 1:
			cout << "nourishment, danger, terrain " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%1.2lf,%1.2lf,%c ", map[j][i].nourishment, map[j][i].danger, map[j][i].terrain);
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 2:
			cout << "# creatures, terrain " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%2d,%c ", map[j][i].cellPop, map[j][i].terrain);
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 3: 
			cout << "# creatures, danger " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%2d,%1.2lf ", map[j][i].cellPop, map[j][i].danger);
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 4: 
			cout << "# creatures, nourishment " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%2d,%1.2lf ", map[j][i].cellPop, map[j][i].nourishment);
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 5:
			cout << "# creatures " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%2d ", map[j][i].cellPop);
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 6:
			cout << "nourishment " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%1.2lf ", map[j][i].nourishment);
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 7:
			cout << "danger " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%1.2lf ", map[j][i].danger);
				}
				cout << endl;
			}
			cout << endl;
			break;
		case 8:
			cout << "terrain " << endl;
			for (int i = 0; i < mapY; i++) {
				for (int j = 0; j < mapX; j++) {
					printf("%c ", map[j][i].terrain);
				}
				cout << endl;
			}
			cout << endl;
			break;
	}
	cout << endl;
}

// Check if there is anything at (x,y)
// If (x,y) is out of bounds or if another creature is there, then we can't go there
bool World::showPos(int x, int y){
	bool canMove = true;
	
	// Check for bounds
	if (mapX <= x || x < 0) { 
		// cout << "Out of bounds! " << endl;
		return !canMove; 
	}
	else if (mapY <= y || y < 0) { 
		// cout << "Out of bounds! " << endl;
		return !canMove; 
	}

	// Let the creature know if it can move
	return canMove;
}

// Move the creature, using Creature::move()
// For each creature, check if it can move to the new (x,y), and if it can, move
bool World::moveCreatures() {
	int x, y, n_x, n_y, dir;
	bool foodEaten = false;
	if (!survived) { return false; }

	// Randomly generate doubles between 0.0 and 1.0 for danger
	random_device rd; // Obtain random seed for random number engine
	mt19937_64 gen(rd()); // Standard64-bit  mersenne_twister_engine seeded with rd()
	uniform_real_distribution<> dis(0.0, 1.0);

	// Iterate through creatures
	for (vector<Creature>::iterator it = creatures.begin(); it != creatures.end(); it++) {
		//cout << "Was at (" << it->c_x << "," << it->c_y << ")" << endl;
		if (it->isAlive) {				
				
			// Every turn, they use up 1 energy	
			x = it->c_x;
			y = it->c_y;
			it->energy--;

			// Effects of danger
			double currD = 0.0;
			// While there is no reason for there to not be a creature at this position, just account for division by 0
			if (map[y][x].cellPop > 0) {

				// Share the burden of danger with other animals in the same tile
				currD = ((double) map[y][x].danger / (double) map[y][x].cellPop);

				// Because the creature is evading danger, reduce energy level
				// Also penalize the animal's decision to move to the tile given the level of danger
				int evadeEnergy = EVADE;
				it->fitness -= map[y][x].danger;
				it->energy -= evadeEnergy;

				// Randomly generate the likelihood of the creature getting hurt
				// If the animal is exposed to danger, reduce health and kill it if health is lower than 0
				double exposeDanger = dis(gen);
				if (exposeDanger < currD) it->health--;
				if(it->health <= 0) { 
					it->isAlive = false;
					//cout << "Creature killed" << endl;
					survived--;
					map[y][x].cellPop--;		
					continue; 
				}
			}

			int eaten = 0;
			double currN = map[y][x].nourishment;
			// cout << "Found: " << currN << " food " << endl;
			if (currN >= CONSUME_PER_CREATURE) {
				map[y][x].nourishment -= CONSUME_PER_CREATURE;
				eaten = ENERGY_INTAKE;
				it->energy += eaten;
				it->fitness += currN;
				it->starving = 0;

			} else if (currN > 0) {
				map[y][x].nourishment = 0;
				eaten = ENERGY_INTAKE * (currN / CONSUME_PER_CREATURE);
				it->energy += eaten;
				it->fitness += currN;
				it->starving = 0;
			} else {
				// Penalize not moving when there is lack of food
				eaten = NO_FOOD;
				it->energy += eaten;
				// cout << "No food here!" << endl;
			}
		
			// If the creature has run out of energy, it is starving
			if (it->energy <= 0) {
				it->starving++;
				// cout << "Starving... " << it->starving << endl;
			}

			// If the creature has been starving for 5 turns, then reduce its health
			// If health reaches zero, then it is dead. update the map and break out of the loop
			if (it->starving == STARVATION) {
				it->health--;
				if(it->health <= 0) { 
					it->isAlive = false;
					// cout << "Creature died" << endl;
					survived--;
					map[y][x].cellPop--;		
					continue; 
				}
			}

			// Each NN is fed the level of food and danger in the tiles within its visual field
			vector<double> nourishmentVision = calcVision(x, y, it->vision, 0);
			vector<double> dangerVision = calcVision(x, y, it->vision, 1);
			vector<double> calculatedV = nourishmentVision;
			calculatedV.insert( calculatedV.end(), dangerVision.begin(), dangerVision.end());
			
			dir = it->NN.testInput(calculatedV);
			// cout << "Moving to the cardinal direction of: " << dir << endl;
			
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

			it->NN.trainWeights(calculatedV);

			// cout << "Now at (" << it->c_x << "," << it->c_y << ")" << endl;
			// cout << "Current energy level is " << it->energy << endl;
		}
		
	}
	// cout << survived << " creatures survived this round" << endl << endl << endl;

	// Call populate food
	populateFood();
	return true;
}

// Calculate the visual field of the creature at the given location
vector<double> World::calcVision(int x, int y, int v, int type) {
	
	// cout << "Showing the creature's visual field" << endl;
	vector<double> v_field;
	// cout << "Looking around (" << x << "," << y << ") in radius of " << v << endl;
	// Within the visual range
	for (int i = x - v; i <= x + v; i++) {
		for (int j = y - v; j <= y + v; j++) {
			// If out of bounds, put 9 down
			if ( 0 > i || i >= mapX || 0 > j || j >= mapY) {
				if (type == 0)	v_field.push_back(0.0);
				else if (type == 1) v_field.push_back(1.0);
				// cout << "-1. ";
			} else {
				if (type == 0)	v_field.push_back(map[j][i].nourishment);
				else if (type == 1) v_field.push_back(map[j][i].danger);
				// printf("%1.1lf ", map[j][i].nourishment);
			}
		}
		// cout << endl;
	}
	// cout << endl;
	return v_field;	
}	

