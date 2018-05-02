#include "World.h"

using namespace std;

World::World() {
	size = defaultSize;
	amountFood = defaultFood;
	cout << "Creating a world that is " << size << " x " << size << " in size" << endl;

	for (int i = 0; i < defaultSize; i++) {
		vector<int> row(defaultSize, NIL);
		map.push_back(row);		
	}

	
}

World::World(int dim, int f) {
	size = dim;
	amountFood = f;
	cout << "Creating a world that is " << size << " x " << size << " in size" << endl;

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
		x = rand() % size;
		y = rand() % size;
		if (map[x][y] != FOOD) {
			food *f = new food; f->f_x = x; f->f_y = y;
			foods.push_back(*f);
			map[x][y] = FOOD;
			currAmount++;
		}
	}
}

void World::showWorld() {
	cout << endl << "Displaying a world that is " << size << " x " << size << " in size" << endl;
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			cout << map[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

void World::showPos(int x, int y){
	if (map[x][y] == 0) {
		cout << "There is nothing here" << endl;
	} else if (map[x][y] == 1) {
		cout << "There is food here!" << endl;
	}
}
