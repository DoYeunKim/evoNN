#include "shared.hpp"

displace cardinalToDisplace(int dir) {
    int d = dir;
	int x, y;

    switch(d) {
        case SE:
            x = y = 1;
            break;
        case SW:
            x = -1;
            y = 1;
            break;
        case S:
            x = 0;
            y = 1;
            break;
        case NE:
            x = 1;
            y = -1;
            break;
        case NW:
            x = y = -1;
            break;
        case N:
            x = 0;
            y = -1;
            break;
        case P:
            x = y = 0;
            break;
    }

	displace *dis = new displace; dis->dx = x; dis->dy = y;
	return *dis;
}

