//#include <tf/transform_listener.h>
#include <tum_ardrone/filter_state.h>
#include <thread>
#include "ros/ros.h"
#include "sensor_msgs/Imu.h"
#include "Vector.h"

class TransformDataListener{
		Vector position;
		Vector direction;
		ros::Subscriber sub;
		ros::NodeHandle n;
//		ros::Rate loop_rate;

	public:
		float yaw;
		float getYaw();
		Vector getPosition();
		Vector getDirection();
		void tfCallBack(tum_ardrone::filter_state msg);
		void setPosition(Vector v);
		void setDirection(Vector v);
		void setYaw(float yaw);
		TransformDataListener();
};