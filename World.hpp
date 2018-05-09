#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <cstdlib>
#include <math.h>
#include <vector>
#include "Creature.hpp"
#define DEFAULT_SIZE 20
#define DEFAULT_FOOD 10
#define DEFAULT_POP 10
#define FOOD_ENERGY 10
#define STARVATION 3

using namespace std;

// Each food is a struct
// with x and y coordinate
typedef struct _food {
    int f_x, f_y;

} food;

// The world!
// This is the main class of the program
// The world maintains the world and controls interactions among its features
class  World {

    private:
		// enum for switch function
		enum {NIL, FOOD, CREATURE};
		enum {N, NE, E, SE, S, SW, W, NW, P};
		// The width or height of the map
        int mapSize;
		// The maximum amount of food that we want on the world
        int amountFood;
		// The maximum amount of creatures that we want on the world
		int popSize;
		// The map
		// It is a vector of vector of int so that it is easier to use enum for the time being
		// I may want to change this to char type to make the world more light
		// Also wondering if I should make map a public variable so that it can be updated more easily
        vector< vector<int> > map;

    public:
		int survived;
		// These vectors are constantly updated and it is easier to have them here
        vector<food> foods;
		vector<Creature> creatures;
		//inits
        World();
        World(int dim, int f, int c);
        ~World();

		// Populate the world
        void populateFood();
		void populateCreature();
	
		// Display the world
        void showWorld();

		// Functions dealing with moving the creatures
		// showPos checks if it is possible for the creature to move into that space
		// moveCreatures calls Creature.move() to actually do the moving if showPos returns true
        int showPos(int x, int y);
		bool moveCreatures();
		vector<double> calcVision(int x, int y, int v);

};

#endif
