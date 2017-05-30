#include "Ring.h"

Ring::Ring(Vector origo, Vector direction, int ringNumber){
	this->origo = origo;
	this->direction = direction;
	this->ringNumber = ringNumber;
}

Vector Ring::calculateEntry(Vector origo, Vector direction){
	Vector v;
	v = origo - direction;
	return v;
}

Vector Ring::calculateExit(){
	Vector v;
	v = origo + direction;
	return v;
}