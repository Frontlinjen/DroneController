#include "Vector.h"
#include <cmath>
#pragma once

class Ring{
	public:
		int ringNumber = -1;
		Vector entry, exit, origo, direction;
		float chance, angleD;
		Ring();
		Ring(Vector origo, Vector direction, int ringNumber, float chance);
		Vector calculateEntry();
		Vector calculateExit();
		float angleDegrees();
};