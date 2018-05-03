#ifndef WORLD_H
#define WORLD_H

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include "Creature.h"
#define defaultSize 20
#define defaultFood 10
#define defaultPop 10

using namespace std;

typedef struct _food {
    int f_x, f_y;

} food;


class  World {

    private:
		enum {NIL, FOOD, CREATURE};
        int mapSize;
        int amountFood;
		int popSize;
        vector< vector<int> > map;

    public:
        vector<food> foods;
		vector<Creature> creatures;
        World();
        World(int dim, int f, int c);
        ~World();

        void populateFood();
        void showWorld();

		void populateCreature();
        bool showPos(int x, int y);
		void moveCreatures();
		void updateMap();

};

#endif
