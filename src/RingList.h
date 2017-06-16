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
#include "ring_detector/RingData.h"

class RingList{
	
	private:
		std::mutex ringList_mutex;
		std::vector<Ring> ringList;
		ros::NodeHandle n;
		ros::Rate loop_rate;
		ros::Subscriber sub;
		TransformDataListener transformDataListener;
		const float minAcceptDistance;

		void updateRing(Ring r1, Ring r2);
		void updateRingnumber(Ring r1, Ring r2);
		void updateList(Ring r);
		void opencvCallback(const ring_detector::RingData msg);
		void msgHandle(const ring_detector::RingData msg);
		static void spinner();

	public:
		RingList();
		Ring* getRing(int i);
		Ring* getClosestRing();
		int ringCount();
};
