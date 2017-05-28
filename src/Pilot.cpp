#include "Pilot.h"

void Pilot::successfullyReachedRing(){
	entryPointReached = true;
}

void Pilot::successfullyPassedRing(){
	nextRingNumber++;
	goingToRing = false;
	entryPointReached = false;
}

void Pilot::lookForRings(){
	commands.goTo(0,0,0,360);
}

Ring* Pilot::searchForNextRing(){
	for(int i = 0; i < commandqueue.size(); i++){
		if(commandqueue[i].ringNumber == nextRingNumber){ //If commandqueue contains next ring. go there.
			return &commandqueue[i];
		}
	}
	return NULL;
}

Ring* Pilot::searchForClosestUnknownRing(){
	Ring * bestCandidate = NULL;
	float shortestDistance;
	for(int i = 0; i < commandqueue.size(); i++){
		if(commandqueue[i].ringNumber != -1){
			//TODO Mypos does not exist. Find out position of drone (from stateestimation?)
			float distanceToRing = sqrt(pow(mypos.x - commandqueue[i].oX)+pow(mypos.y - commandqueue[i].oY)+pow(mypos.z - commandqueue[i].oZ)); //distance to point
			if(bestCandidate == NULL || distanceToRing < shortestDistance){
				bestCandidate = &commandqueue[i];
				shortestDistance = distanceToRing;
			}
		}
	}
	return bestCandidate;
}

void Pilot::mainLoop(){
	if(ros::ok()){
		commands.prepare();
		commands.flattrim();
		commands.autoInit();
		/*p.goTo(0,1,0,0);
		p.land();*/
	}

	while(ros::ok){ //Main loop

		switch(currentStatus){
			case GoingtToNextRing:
				//Reached destination?
				if(){
					currentStatus = AtEntryPoint;
					
				}
				break;
			case GoingToUnknownRing:
				//Found ring?
				if(){

				}
				//Reached destination?
				else if(){
					currentStatus = Idle;
				}
				break;
			case AtEntryPoint:
				//Passed Ring?
				if(){
					currentStatus = Idle;
				}
				break;
			case Idle:
				//Find next objective
				nextTarget = searchForNextRing();
				if(nextTarget == NULL){
					nextTarget = searchForClosestUnknownRing();
					if(nextTarget == NULL){
						lookForRings();
					}
					else{
						currentStatus = GoingToUnknownRing;
						Vec3f ventry = *nextTarget.calculateEntry();
						Vec3f vexit = *nextTarget.calculateExit();
						commands.moveBy(ventry.at(0), ventry.at(1), ventry.at(2), 0);
					}
				}
				else{
					currentStatus = GoingtToNextRing;
					Vec3f ventry = *nextTarget.calculateEntry();
					Vec3f vexit = *nextTarget.calculateExit();
					commands.moveBy(ventry.at(0), ventry.at(1), ventry.at(2), 0);
				}
				break;
		}

		//Old algorithm, scrapped because it was ugly
		/*if(goingToRing){
			if(entryPointReached){
				commands.moveBy(vexit.at(0), vexit.at(1), vexit.at(2), 0);
				//Listen for response
			}
		}
		else{
			nextTarget = searchForNextRing();
			if(nextTarget == NULL){
				nextTarget = searchForClosestUnknownRing();
				if(nextTarget == NULL){
					lookForRings();
				}
				else{
					Vec3f ventry = *nextTarget.calculateEntry();
					Vec3f vexit = *nextTarget.calculateExit();
					commands.moveBy(ventry.at(0), ventry.at(1), ventry.at(2), 0);
				}
			}
			else{
				Vec3f ventry = *nextTarget.calculateEntry();
				Vec3f vexit = *nextTarget.calculateExit();
				goingToRing = true;
				commands.moveBy(ventry.at(0), ventry.at(1), ventry.at(2), 0);
				//ListenforResponse
			}
		}
	}*/
}