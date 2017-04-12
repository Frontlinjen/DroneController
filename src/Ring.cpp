#include "Ring.h"

Ring::Ring(){

}

Ring::Ring(float oX, float oY, float oZ, float dX, float dY, float dZ, int ringNumber){
	this.oX = oX;
	this.oY = oY;
	this.oZ = oZ;
	this.dX = dX;
	this.dY = dY;
	this.dZ = dZ;
	this.ringNumber = ringNumber;

	//TODO Calculate entry and exit points
}
