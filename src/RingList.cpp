#include "Ring.h"
#include "RingList.h"
#include <math.h>
#include <mutex>
#include <thread>
#include <string>
#include <sstream>
#include <vector>
#include "ros/ros.h"
#include "std_msgs/String.h"

RingList::RingList() : loop_rate(10){
	ros::Subscriber sub = n.subscribe("opencv", 1000, opencvCallback);
}

void RingList::updateRing(Ring newr, Ring old){
	std::lock_guard<std::mutex> lock(ringList_mutex);
		old.origo = newr.origo;
		old.direction = newr.direction;
		old.ringnumber = newr.ringnumber;
		old.chance = newr.chance;
	return;
}

void RingList::updateRingnumber(Ring newr, Ring old){
	std::lock_guard<std::mutex> lock(ringList_mutex);
		old.ringnumber = newr.ringnumber;
	return;
}

Ring RingList::getRing(int i){
	for(i; i<ringList.length(); i++){
		if(i == ringList.at(i).ringnumber){
			return ringList.at(i);
		}
	}
	return null;
}

Ring RingList::getClosestRing(){

}

void RingList::updateList(Ring r){
	for(int i = 0; i < ringList.length(); i++){
		float posx, posy, posz, pos;
		posx = float abs(r.x - ringList.at(i).x);
		posy = float abs(r.y - ringList.at(i).y);
		posz = float abs(r.z - ringList.at(i).z);
		pos = sqrt(pow(posx,2) + pow(posy,2) + pow(posz,2));
		if(r.ringnumber == ringList.at(i).ringnumber && pos < 1){
			if(r.chance > ringList.at(i).chance){
				ringList.updateRing(r, ringList.getRing(id);
				ringFoundList = true;
				break;
			} else {
				ringFoundInList = true;
				break;
			}
		}
		if(r.ringnumber != ringList.at(i).ringnumber && pos < 1){
			if(r.chance > ringList.at(i).chance){
				ringList.updateRing(r, ringList.at(i));
				ringFoundList = true;
				break;
			} else {
				ringList.updateRingnumber(r, ringList.at(i));
				ringFoundInList = true;
				break;
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

void RingList::msgHandle(std_msgs::String::ConstPtr& msg){
	std::stringstream stream(*msg);
	float chance;
	int ringnumber;
	Vector origo, direction;
	stream >> origo->x; 
	stream >> origo->y; 
	stream >> origo->z; 
	stream >> direction->x; 
	stream >> direction->y; 
	stream >> direction->z; 
	stream >> ringnumber; 
	stream >> chance;

	Ring r(origo, direction, ringnumber, chance);

	updateList(r);
}