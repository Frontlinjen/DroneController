#pragma once
struct Vector{
	
	float x, y, z;

	Vector(){
	}

	Vector(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector operator-(Vector& vneg){
		Vector v;
		v.x = this->x - vneg.x;
		v.y = this->y - vneg.y;
		v.z = this->z - vneg.z;
		return v;
	}

	Vector operator+(Vector& vadd){
		Vector v;
		v.x = this->x + vadd.x;
		v.y = this->y + vadd.y;
		v.z = this->z + vadd.z;
		return v;
	}
};