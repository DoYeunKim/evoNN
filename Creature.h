#ifndef CREATURE_H
#define CREATURE_H

#include<iostream>

class Creature {
	private:
		bool isStarved = false;
 		int fitness = 0;
		int damage = 0;
		int health = 100;
		int speed = 1;
		int energy = 100;

	public:
		int c_x, c_y;

		Creature();
		Creature(int x, int y);
		~Creature();

		void showInfo();
		void move(int dx, int dy);
};

#endif
