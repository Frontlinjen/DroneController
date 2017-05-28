#include <opencv/core/core.hpp>
#include <matx.hpp>

class Ring{
	public:
		int ringNumber = -1;
		Vec3f entry, exit, origo, direction;
		Ring();
		Ring(Vec3f origo, Vec3f direction, int ringNumber);
		Vec3d calculateEntry();
		Vec3d calculateExit();
};