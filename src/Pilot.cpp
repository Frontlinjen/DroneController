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
			commands.goTo(ventry.x, ventry.y, ventry.z, 0);
			pointReached.listenForPointReached();
		}
	}
	else{
		ROS_INFO("Going to next ring");
		currentStatus = GoingToNextRing;
		Vector ventry = (*nextTarget).calculateEntry();
		Vector vexit = (*nextTarget).calculateExit();
		commands.goTo(ventry.x, ventry.y, ventry.z, 0);
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
		//temp
		commands.land();
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
		Vector vexit = (*nextTarget).calculateExit();
		currentStatus = AtEntryPoint;
		commands.goTo(vexit.x, vexit.y, vexit.z, 0);
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
		commands.goTo(ventry.x, ventry.y, ventry.z, 0);
		pointReached.listenForPointReached();
	}
	//Reached destination?
	else if(pointReached.isPointReached()){
		currentStatus = Idle;
	}
}

void Pilot::collisionHandling(*Ring ring){
	float a, b, c, aLine, bLine; //a,b,c del af andengradsligningen til at se kollision. aLine og bLine er vectorens koordinater
	TransformDataListener tdl;
	bool freePath = true;
	Vector pos = tdl.getPosition();
	for(int i = 0; i < ringList.ringCount(); i++){
		if(ringList.getRing(i).ringNumber == nextRingNumber){
			continue;
		}
		else{
			Ring r = ringList.getRing(i);
			aLine = (r.y - pos.y) / (r.x - pos.x);
			bLine = r.y - (aline * r.x);
			a = pow(aline, 2) + 1;
			b = (-2 * r.x) + (2 * aline * bline) + (-2 * aline * r.y);
			c = pow(-r.x, 2) + pow(bline, 2) + pow(r.y, 2) + (-2 * bline * r.y) - pow(0.75, 2);
			d = pow(b, 2) - 4 * a * c;
			if(d < 0){
				continue;
			}
			else{
				freePath = false;
				Vector intermediatePoint = r.origo; //Gang origo med vinkelret vektor til den normale rute ganget med sikkerhedsafstanden
			}
		}
	}
	if(freePath){
		commands.goTo(ring->entry.x, ring->entry.y, ring->entry.z, ring->angleDegrees);
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