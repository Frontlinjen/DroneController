#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include "Commands.h"
#include <sstream>
#include <string>
#include <math.h>
#include "Ring.h"
#include <cstddef>
#include <vector>
#include "PointReached.h"
#include "RingList.h"

enum StatusType{GoingToNextRing, GoingToUnknownRing, AtEntryPoint, Idle};

class Pilot{

	private:
		int nextRingNumber;
		Ring* nextTarget;
		Commands commands;
		PointReached pointReached;
		RingList ringList;
		bool busy = false;
		StatusType currentStatus = Idle;

		void stateIdle();
		void stateAtEntry();
		void stateGoingToNextRing();
		void stateGoingToUnknownRing();

	public:
		void mainLoop();
};