#ifndef CREATURE_H
#define CREATURE_H

#include<iostream>

class Creature {
	private:
		int c_x, c_y;
 		int fitness = 0;
		int damage = 1;
		int health = 1;
		int speed = 1;

	public:
		Creature();
		Creature(int x, int y);
		~Creature();

		void showInfo();
};

#endif
