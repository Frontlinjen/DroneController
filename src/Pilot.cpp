#include "Pilot.h"

void Pilot::lookForRings(){
	commands.goTo(0,0,0,360);
}

void Pilot::mainLoop(){
	if(ros::ok()){
		commands.prepare();
		commands.flattrim();
		commands.autoInit();
	}

	while(ros::ok){ //Main loop
		switch(currentStatus){
			case GoingToNextRing:
				//Reached destination?
				if(pointReached.isPointReached()){
					Vector vexit = (*nextTarget).calculateExit();
					currentStatus = AtEntryPoint;
					commands.moveBy(vexit.x, vexit.y, vexit.z, 0);
					pointReached.listenForPointReached();
				}
				break;
			case GoingToUnknownRing:{
				//Found ring?
				Ring * potentialRing = ringList.getRing(nextRingNumber);
				if(potentialRing != NULL){
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
				break;
			}
			case AtEntryPoint:
				//Passed Ring?
				if(pointReached.isPointReached()){
					nextRingNumber++;
					currentStatus = Idle;
				}
				break;
			case Idle:{
				//Find next objective
				nextTarget = ringList.getRing(nextRingNumber);
				if(nextTarget == NULL){
					nextTarget = ringList.getClosestRing();
					if(nextTarget == NULL){
						lookForRings();
					}
					else{
						currentStatus = GoingToUnknownRing;
						Vector ventry = (*nextTarget).calculateEntry();
						Vector vexit = (*nextTarget).calculateExit();
						commands.moveBy(ventry.x, ventry.y, ventry.z, 0);
						pointReached.listenForPointReached();
					}
				}
				else{
					currentStatus = GoingToNextRing;
					Vector ventry = (*nextTarget).calculateEntry();
					Vector vexit = (*nextTarget).calculateExit();
					commands.moveBy(ventry.x, ventry.y, ventry.z, 0);
					pointReached.listenForPointReached();
				}
				break;
			}
		}
	}
}