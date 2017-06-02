#include "RingList.h"

RingList::RingList() : loop_rate(10), minAcceptDistance(0.5){
	ros::Subscriber sub = n.subscribe("opencv", 1000, &RingList::opencvCallback, this);

	//Test ring
	Vector origo(0,2,2);
	Vector direction(0,1,0);
	int ringNumber = 1;
	float chance = 100;
	Ring r(origo, direction, ringNumber, chance);
	updateList(r);
}

void RingList::updateRing(Ring newr, Ring old){
	std::lock_guard<std::mutex> lock(ringList_mutex);
	old = newr;
}

void RingList::updateRingnumber(Ring newr, Ring old){
	std::lock_guard<std::mutex> lock(ringList_mutex);
	old.ringNumber = newr.ringNumber;
}

Ring* RingList::getRing(int x){
	for(int i = 0; i<ringList.size(); i++){
		if(x == ringList.at(i).ringNumber){
			return &(ringList.at(i));
		}
	}
	return NULL;
}

Ring* RingList::getClosestRing(){
	Vector mypos = transformDataListener.getPosition();
	float shortestDistance;
	Ring* bestCandidate = NULL;

	for(int i = 0; i < ringList.size(); i++){
		Ring r = ringList.at(i);
		if(r.ringNumber == -1){
			float distanceToRing = pow((r.origo.x - mypos.x), 2) + pow((r.origo.y - mypos.y), 2) + pow((r.origo.z - mypos.z), 2);
			if(bestCandidate == NULL){
				*bestCandidate = r;
			}
			if(distanceToRing < shortestDistance){
				shortestDistance = distanceToRing;
				*bestCandidate = r;
			}
		}
	}
	return bestCandidate;
}

void RingList::updateList(Ring r){
	bool ringFoundInList = false;
	for(int i = 0; i < ringList.size(); i++){
		float posx, posy, posz, pos;
		//Find the distance between the two rings
		posx = std::abs(r.origo.x - ringList.at(i).origo.x);
		posy = std::abs(r.origo.y - ringList.at(i).origo.y);
		posz = std::abs(r.origo.z - ringList.at(i).origo.z);
		pos = sqrt(pow(posx,2) + pow(posy,2) + pow(posz,2));
		if(pos < minAcceptDistance){
			if(r.ringNumber == ringList.at(i).ringNumber){
				if(r.chance > ringList.at(i).chance){
					updateRing(r, ringList.at(i));
				}
				ringFoundInList = true;
				break;
			}
			else{
				if(r.chance > ringList.at(i).chance){
					updateRing(r, ringList.at(i));
					ringFoundInList = true;
					break;
				} else {
					updateRingnumber(r, ringList.at(i));
					ringFoundInList = true;
					break;
				}
			}
		}
	}
	if(ringFoundInList == false){
		ringList.push_back(r);
	}
}

void RingList::opencvCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	msgHandle(msg);
}

void RingList::msgHandle(std_msgs::String::ConstPtr msg){
	/*std::stringstream stream(*msg);
	float chance;
	int ringnumber;
	Vector origo, direction;
	stream >> origo.x; 
	stream >> origo.y; 
	stream >> origo.z; 
	stream >> direction.x; 
	stream >> direction.y; 
	stream >> direction.z; 
	stream >> ringNumber; 
	stream >> chance;

	Ring r(origo, direction, ringNumber, chance);

	updateList(r);*/
}