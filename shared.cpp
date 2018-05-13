#include "shared.hpp"

using namespace std;

displace cardinalToDisplace(int dir) {
    int d = dir;
	int dr, dc;

    switch(d) {
        case N:
            dr = -1;
            dc = 0;
            break;
        case NE:
            dr = -1;
            dc = 1;
            break;
		case E:
			dr = 0;
			dc = 1;
        case SE:
            dr = dc = 1;
            break;
        case S:
            dr = 1;
            dc = 0;
            break;
        case SW:
            dr = 1;
            dc = -1;
            break;
		case W:
			dr = 0;
			dc = -1;
			break;
        case NW:
            dr = dc = -1;
            break;
        case P:
            dr = dc = 0;
            break;
    }

	displace *dis = new displace; dis->dx = dr; dis->dy = dc;
	// cout << dis->dx << ", " << dis->dy << endl;
	return *dis;
}

