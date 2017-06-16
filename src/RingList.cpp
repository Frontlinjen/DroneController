#include "RingList.h"

RingList::RingList() : loop_rate(10), minAcceptDistance(0.5){
	ros::Subscriber sub = n.subscribe("opencv", 1000, &RingList::opencvCallback, this);

	//Test ring
	Vector origo(0,2,1.5);
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

void RingList::opencvCallback(const ring_detector::RingData msg){
	//ROS_INFO("I heard: [%s]", msg->data.c_str());
	msgHandle(msg);
}

void RingList::msgHandle(ring_detector::RingData msg){
	float chance;
	int ringNumber;
	Vector origo, direction;
	
	chance = msg.possibility;
	ringNumber = msg.ring_number;
	Vector a = transformDataListener.getPosition();
	origo = Vector(msg.delta_x, msg.delta_y, msg.delta_z) + a;
	direction = Vector(msg.norm_x, msg.norm_y, 0);

	Ring r(origo, direction, ringNumber, chance);

	updateList(r);
}

int RingList::ringCount(){
	return ringList.size();
}
