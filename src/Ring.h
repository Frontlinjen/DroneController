#include "Vector.h"
#include <matx.hpp>

class Ring{
	public:
		int ringNumber = -1;
		Vector entry, exit, origo, direction;
		Ring();
		Ring(Vector origo, Vector direction, int ringNumber);
		Vector calculateEntry();
		Vector calculateExit();
};