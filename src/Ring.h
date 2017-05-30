#include "Vector.h"

class Ring{
	public:
		int ringNumber = -1;
		Vector entry, exit, origo, direction;
		Ring();
		Ring(Vector origo, Vector direction, int ringNumber, float chance);
		Vector calculateEntry();
		Vector calculateExit();
};