#include "Vector.h"
#pragma once

class Ring{
	public:
		int ringNumber = -1;
		Vector entry, exit, origo, direction;
		float chance;
		Ring();
		Ring(Vector origo, Vector direction, int ringNumber, float chance);
		Vector calculateEntry();
		Vector calculateExit();
};