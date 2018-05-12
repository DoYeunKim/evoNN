#include "shared.hpp"

using namespace std;

displace cardinalToDisplace(int dir) {
    int d = dir;
	int x, y;

    switch(d) {
        case N:
            x = 0;
            y = -1;
            break;
        case NE:
            x = 1;
            y = -1;
            break;
		case E:
			x = 1;
			y = 0;
        case SE:
            x = y = 1;
            break;
        case S:
            x = 0;
            y = 1;
            break;
        case SW:
            x = -1;
            y = 1;
            break;
		case W:
			x = -1;
			y = 0;
			break;
        case NW:
            x = y = -1;
            break;
        case P:
            x = y = 0;
            break;
    }

	displace *dis = new displace; dis->dx = x; dis->dy = y;
	// cout << dis->dx << ", " << dis->dy << endl;
	return *dis;
}

