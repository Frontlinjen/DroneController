struct Vector{
	
	float x, y, z;

	Vector(float x, float y, float z){
		this->x = x;
		this->y = y;
		this->z = z;
	}

	Vector operator-(Vector& vmin){
		Vector v;
		v.x = this->x - vmin.x;
		v.y = this->y - vmin.y;
		v.z = this->z - vmin.z;
		return v;
	}

	Vector operator+(Vector& vadd){
		Vector v;
		v.x = this->x + vmin.x;
		v.y = this->y + vmin.y;
		v.z = this->z + vmin.z;
		return v;
	}
}