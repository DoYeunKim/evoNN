typedef struct _displace {
	int dx, dy;
} displace;

enum {N, NE, E, SE, S, SW, W, NW, P};
displace cardinalToDisplace(int dir);
