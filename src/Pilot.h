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

enum StatusType{GoingToNextRing, GoingToUnknownRing, AtEntryPoint, Idle};

class Pilot{

	private:
		int nextRingNumber;
		std::vector<Ring> commandqueue;
		Ring* nextTarget;
		Commands commands;
		PointReached pointReached;
		void successfullyReachedRing();
		void successfullyPassedRing();
		void lookForRings();
		Ring* searchForNextRing();
		Ring* searchForClosestUnknownRing();
		StatusType currentStatus;

	public:
		void mainLoop();
		//Pilot();
		void setEntryPointReached();
};