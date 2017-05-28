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

class Pilot{

	private:
		int nextRingNumber = 0;
		std::vector<Ring> commandqueue;
		Ring* nextTarget;
		Commands commands;
		void successfullyReachedRing();
		void successfullyPassedRing();
		void lookForRings();
		Ring* searchForNextRing();
		Ring* searchForClosestUnknownRing();
		enum statusType{GoingToNextRing, GoingToUnknownRing, AtEntryPoint, Idle};
		statusType status = Idle;

	public:
		void mainLoop();
		Pilot();
		void setEntryPointReached();
};