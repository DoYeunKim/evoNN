#ifndef SHARED_HPP
#define SHARED_HPP

#include <iostream>

typedef struct _displace {
	int dx, dy;
} displace;

enum {N, NE, E, SE, S, SW, W, NW, P};
displace cardinalToDisplace(int dir);

#endif
