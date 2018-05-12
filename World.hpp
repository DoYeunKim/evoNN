#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include "Creature.hpp"

#define MIN_SUS 0.0
#define MAX_SUS 50.0
#define DEFAULT_POP 1


using namespace std;

// Each food is a struct
// with x and y coordinate
typedef struct _cell {
    int cellPop;
	double nourishment;

} cell;

// The world!
// This is the main class of the program
// The world maintains the world and controls interactions among its features
class  World {

    private:
		// enum for switch function
		// The first 8 represent cardinal directions
		// P is for the present location (i.e. does not move)
		enum {N, NE, E, SE, S, SW, W, NW, P};
		// The width and height of the map
        int mapX, mapY;
		// The maximum amount of creatures that we want on the world
		int popSize;
		// The map
		// The current map comprises of cells that contain nourishment score and the number of
		// creatures currently there. 
        vector< vector<cell> > map;

    public:
		int survived;
		// These vectors are constantly updated and it is easier to have them here
		vector<Creature> creatures;
		//inits
        World();
        World(vector< vector<double> >& inputMap);
        ~World();

		// Populate the world
		void initWorld(vector< vector<double> >& i_map);
        void populateFood();
		void populateCreature();
	
		// Display the world
        void showWorld();

		// Functions dealing with moving the creatures
		// showPos checks if it is possible for the creature to move into that space
		// moveCreatures calls Creature.move() to actually do the moving if showPos returns true
        bool showPos(int x, int y);
		bool moveCreatures();
		vector<double> calcVision(int x, int y, int v);

};

#endif
