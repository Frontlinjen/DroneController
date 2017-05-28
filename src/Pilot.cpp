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

Ring* Pilot::searchForNextRing(){ //TODO slå sammen med den anden method
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
		if(goingToRing){
			if(entryPointReached){
				commands.moveBy((*nextTarget).exitX, (*nextTarget).exitY, (*nextTarget).exitZ,0);
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
					commands.moveBy((*nextTarget).entryX, (*nextTarget).entryY, (*nextTarget).entryZ,0);
				}
			}
			else{
				goingToRing = true;
				commands.moveBy((*nextTarget).entryX, (*nextTarget).entryY, (*nextTarget).entryZ,0);
			}
		}
	}
}