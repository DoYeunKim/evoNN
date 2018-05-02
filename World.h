#ifndef WORLD_H
#define WORLD_H

#include<iostream>
#include<cstdlib>
#include<math.h>
#include<vector>
#define defaultSize 20
#define defaultFood 10

using namespace std;

typedef struct _food {
    int f_x, f_y;

} food;


class  World {

    private:
		enum {NIL, FOOD, CREATURE};
        vector< vector<int> > map;
        int size;
        int amountFood;
        vector<food> foods;

    public:
        World();
        World(int dim, int f);
        ~World();

        void populateFood();
        void showWorld();
        void showPos(int x, int y);

};

#endif
