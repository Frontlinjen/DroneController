#include "Ring.h"
#include "Vector.h"
Ring::Ring(){
}

Ring::Ring(Vector origo, Vector direction, int ringNumber, float chance){
	this->origo = origo;
	this->direction = direction;
	this->ringNumber = ringNumber;
	this->chance = chance;
}

Vector Ring::calculateEntry(){
	Vector v;
	v = origo - direction;
	return v;
}

Vector Ring::calculateExit(){
	Vector v;
	v = origo + direction;
	return v;
}

float Ring::angleDegrees(){
	angleD = atan2(direction.x, direction.y) * 180 / 3.14159265;
	return angleD;
}