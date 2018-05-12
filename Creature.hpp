#ifndef CREATURE_HPP
#define CREATURE_HPP

#include <iostream>
#include "NeuralNet.hpp"
#include "shared.hpp"

#define ENERGY_INTAKE 5
#define CONSUME_PER_CREATURE 0.01
#define STARVATION 3

// The main class of Creature
// I will be adding multiple species that are inherited Creatures
class Creature {
	private:
		int speed = 1;
		int walkEnergy = 2;

	public:
		// enum for switch function
		// The first 8 represent cardinal directions
		// P is for the present location (i.e. does not move)
		enum {N, NE, E, SE, S, SW, W, NW, P};
		// position
		int c_x, c_y;
		// The level of energy.
		// Moving around reduces energy, and eating will restore energy
		int energy = 10;
		// Check if the creature is dead
		bool isAlive = true;
		// Check if the creature is starved (energy = 0)
		// Will be implementing reduced activity and lowered health, excelerating death
		int starving = 0;
		// Fitness score for future GA
		// Fitness = iterations survived + food eaten + end health
 		double fitness = 0;
		// How healthy the animal is
		// Whenever it is hurt or has been starving, it will be lowered
		// and if health <= 0, then it dies 
		int health = 1;
		// The speed at which the animal trasverses the world
		// As of now, I'm not sure how I will use this, but it most likley will depend
		// on the "species"
		// The area of visual field, n block radius of the animal (n = |dx| + |dy|)
		int vision = 2;

		vector<double> visible;

		NeuralNet NN;

		// Inits
		Creature();
		Creature(int x, int y);
		~Creature();

		// Show the relevant informations on the creature
		void showInfo();
		// Move the creture by dx and dy
		void move(int direction);
};

#endif
