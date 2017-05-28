#include "ros/ros.h"

class PointReached{

	private:
		void tellPointReached();

	public:
		PointReached();
		void listenForPointReached();
};