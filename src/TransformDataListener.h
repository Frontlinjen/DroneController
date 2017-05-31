#include <tf/transform_listener.h>
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "Vector.h"

class TransformDataListener{
	private:
		bool isValidVector = false;;
	public:
		float x,y,z;
		Vector currentPosition;
		TransformDataListener();
		Vector getPosition();
};