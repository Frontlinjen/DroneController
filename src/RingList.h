#include <math.h>
#include <mutex>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include "ros/ros.h"
#include "std_msgs/String.h"
#include "TransformDataListener.h"
#include "Ring.h"
#include "Vector.h"

class RingList{
	
	private:
		std::mutex ringList_mutex;
		std::vector<Ring> ringList;
		ros::NodeHandle n;
		ros::Rate loop_rate;
		ros::Subscriber sub;
		
		void updateRing(Ring r1, Ring r2);
		void updateRingnumber(Ring r1, Ring r2);
		Ring getRing(int i);
		void updateList(Ring r);
		void opencvCallback(const std_msgs::String::ConstPtr& msg);
		void msgHandle(std_msgs::String::ConstPtr& msg);
		bool listening = false;

	public:
		RingList();
}