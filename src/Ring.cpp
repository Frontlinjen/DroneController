#include "Ring.h"

Ring::Ring(){

}

Ring::Ring(Vec3f origo, Vec3f direction, int ringNumber){
	this.origo = origo;
	this.direction = direction;
	this.ringNumber = ringNumber;
}

Vec3f Ring::calculateEntry(Vec3f origo, Vec3f direction){
	Vec3f v;
	v = origo - direction;
	return v;
}

Vec3f Ring::calculateExit(){
	Vec3f v;
	v = origo + direction;
	return v;
}