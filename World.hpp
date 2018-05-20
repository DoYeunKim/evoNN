#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include "Creature.hpp"

#define MIN_SUS 0.0
#define MAX_SUS 1.0
#define DEFAULT_POP 10
#define DEF_REGEN 0.001


using namespace std;

// Each food is a struct
// with x and y coordinate
typedef struct _cell {
    char terrain;
	int cellPop;
	double nourishment;
	double danger;

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


    public:
		int survived;
		// These vectors are constantly updated and it is easier to have them here
		vector<Creature> creatures;
		// The map
		// The current map comprises of cells that contain nourishment score, danger score,
		// type of terrain, and the number of creatures currently there. 
        vector< vector<cell> > map;
		//inits
        World();
        World(vector< vector<char> >& terrainMap, vector< vector<double> >& foodMap, vector< vector<double> >& dangerMap);
        ~World();

		// Populate the world
		void initWorld(vector< vector<char> >& t_map, vector< vector<double> >& f_map, vector< vector<double> >& d_map);
        void populateFood();
		void populateCreature();
		void newGenCreatures(vector<edge>& inheritedE);
	
		// Display the world
        void showWorld(int mapType);

		// Functions dealing with moving the creatures
		// showPos checks if it is possible for the creature to move into that space
		// moveCreatures calls Creature.move() to actually do the moving if showPos returns true
        bool showPos(int x, int y);
		bool moveCreatures();
		vector<double> calcVision(int x, int y, int v, int type);

};

#endif
