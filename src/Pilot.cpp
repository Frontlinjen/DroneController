#include "Pilot.h"

void Pilot::stateIdle()
{
	//Find next objective
	nextTarget = ringList.getRing(nextRingNumber);
	if(nextTarget == NULL){
		nextTarget = ringList.getClosestRing();
		if(nextTarget == NULL){
			if(!pointReached.isListening()){
				ROS_INFO("No ring found, spinning...");
				commands.lookForRings();
				pointReached.listenForPointReached();
			}
		}
		else{
			ROS_INFO("Going to unknown ring");
			currentStatus = GoingToUnknownRing;
			Vector ventry = (*nextTarget).calculateEntry();
			Vector vexit = (*nextTarget).calculateExit();
			commands.goTo(ventry.x, ventry.y, ventry.z, nextTarget->angleDegrees());
			pointReached.listenForPointReached();
		}
	}
	else{
		ROS_INFO("Going to next ring");
		currentStatus = GoingToNextRing;
		Vector ventry = (*nextTarget).calculateEntry();
		Vector vexit = (*nextTarget).calculateExit();
		commands.goTo(ventry.x, ventry.y, ventry.z, nextTarget->angleDegrees());
		pointReached.listenForPointReached();
	}
}

void Pilot::stateAtEntry()
{
	//Passed Ring?
	if(pointReached.isPointReached()){
		nextRingNumber++;
		currentStatus = Idle;
		ROS_INFO("Reached exit point");
		//Is the track completed?
		if(ringList.ringCount() >= 6 && (nextRingNumber - 1) == ringList.ringCount()){
			//Should we do a lookForRings just to be sure?
			ROS_INFO("Track completed, landing...");
			commands.goTo(0,0,0,0);
			commands.land();
		}
	}
}

void Pilot::stateGoingToNextRing()
{
	//Reached destination?
	if(pointReached.isPointReached()){
		ROS_INFO("Reached entry point");
		Vector vexit = (*nextTarget).calculateExit(); //Calculate again in case of updates
		currentStatus = AtEntryPoint;
		commands.goTo(vexit.x, vexit.y, vexit.z, nextTarget->angleDegrees());
		pointReached.listenForPointReached();
	}
}

void Pilot::stateGoingToUnknownRing()
{
	//Found ring?
	Ring * potentialRing = ringList.getRing(nextRingNumber);
	if(potentialRing != NULL){
		ROS_INFO("Going to next ring");
		currentStatus = GoingToNextRing;
		nextTarget = potentialRing;
		Vector ventry = (*nextTarget).calculateEntry();
		Vector vexit = (*nextTarget).calculateExit();
		commands.clearCommands();
		commands.goTo(ventry.x, ventry.y, ventry.z, nextTarget->angleDegrees());
		pointReached.listenForPointReached();
	}
	//Reached destination?
	else if(pointReached.isPointReached()){
		currentStatus = Idle;
	}
}

void Pilot::mainLoop(){
	if(ros::ok()){
		commands.prepare();
		commands.flattrim();
		commands.autoInit();
		commands.goTo(0,0,1,0);
	}
	while(ros::ok()){ //Main loop
		switch(currentStatus){
			case GoingToNextRing:
				stateGoingToNextRing();
				break;
			case GoingToUnknownRing:
				stateGoingToUnknownRing();
				break;
			case AtEntryPoint:
				stateAtEntry();
				break;
			case Idle:{
				stateIdle();	
				break;
			}
		}
	}
}
