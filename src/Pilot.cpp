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
			commands.moveBy(ventry.x, ventry.y, ventry.z, 0);
			pointReached.listenForPointReached();
		}
	}
	else{
		ROS_INFO("Going to next ring");
		currentStatus = GoingToNextRing;
		Vector ventry = (*nextTarget).calculateEntry();
		Vector vexit = (*nextTarget).calculateExit();
		commands.moveBy(ventry.x, ventry.y, ventry.z, 0);
		pointReached.listenForPointReached();
	}
}

void Pilot::stateAtEntry()
{
	//Passed Ring?
	if(pointReached.isPointReached()){
		nextRingNumber++;
		currentStatus = Idle;
		ROS_INFO("Reached Entry Point");
	}
}

void Pilot::stateGoingToNextRing()
{
	//Reached destination?
	if(pointReached.isPointReached()){
		ROS_INFO("Reached Entry Point");
		Vector vexit = (*nextTarget).calculateExit();
		currentStatus = AtEntryPoint;
		commands.moveBy(vexit.x, vexit.y, vexit.z, 0);
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
		commands.moveBy(ventry.x, ventry.y, ventry.z, 0);
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