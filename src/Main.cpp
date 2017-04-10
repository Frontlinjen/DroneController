#include "ros/ros.h"
#include "std_msgs/String.h"
#include "std_msgs/Empty.h"
#include "std_srvs/Empty.h"
#include "Pilot.h"
#include <sstream>
#include <string>
#include <list>
#include <math.h>
#include "Ring.h"
#include <cstddef>

int nextRingNumber = 0;
std::list<Ring> commandqueue;
bool goingToRing = false; //If drone is doing something that is not advancing to the next ring
bool entryPointReached = false;
Ring nextTarget;
Pilot p;

void successfullyReachedRing(){
	entryPointReached = true;
}

void successfullyPassedRing(){
	nextRingNumber++;
	goingToRing = false;
	entryPointReached = false;
}

void lookForRings(){
	p.goTo(0,0,0,360);
}

Ring searchForNextRing(){
	for(int i = 0; i < commandqueue.size(); i++){
		if(commandqueue[i].ringNumber != 666){
			if(commandqueue[i].ringNumber == nextRingNumber){ //If commandqueue contains next ring. go there.
				return commandqueue[i];
			}
		}
	}
	return NULL;
}

Ring searchForClosestUnknownRing(){
	Ring bestCandidate;
	float shortestDistance;
	for(int i = 0; i < commandqueue.size(); i++){
		if(commandqueue[i].ringNumber != 666){
			//TODO Mypos does not exist. Find out position of drone
			float distanceToRing = sqrt(pow(mypos.x - commandqueue[i].oX)+pow(mypos.y - commandqueue[i].oY)+pow(mypos.z - commandqueue[i].oZ)); //distance to point
			if(bestCandidate == NULL || distanceToRing < shortestDistance){
				bestCandidate = commandqueue[i];
				shortestDistance = distanceToRing;
			}
		}
	}
	return bestCandidate;
}

int main(int argc, char **argv){

	ros::init(argc,argv,"pilot");

	if(ros::ok()){
		p.prepare();
		p.flattrim();
		p.autoInit();
		/*p.goTo(0,1,0,0);
		p.land();*/
	}

	while(ros::ok){ //Main loop
		if(goingToRing){
			if(entryPointReached){
				p.moveBy(nextTarget.exitX, nextTarget.exitY, nextTarget.exitZ,0);
			}
		}
		else{
			nextTarget = searchForNextRing();
			if(nextTarget == NULL){
				nextTarget = searchForClosestUnknownRing();
				if(nextTarget == NULL{
					lookForRings();
				}
				else{
					p.moveBy(nextTarget.entryX, nextTarget.entryY, nextTarget.entryZ,0);
				}
			}
			else{
				goingToRing = true;
				p.moveBy(nextTarget.entryX, nextTarget.entryY, nextTarget.entryZ,0);
			}
		}
	}
}