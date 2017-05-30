#include "PossibleRings.h"
#include "Ring.h"
#include "Vector.h"
#include <vector>

void opencvCallback(const std_msgs::String::ConstPtr& msg){
	ROS_INFO("I heard: [%s]", msg->data.c_str());
	msgHandle(msg);
}

void msgHandle(std_msgs::String::ConstPtr& msg){
	std::getline(std::cin, msg);
	std::stringstream stream(msg);
	float chance; 
	int ringnumber;
	Ring r;
	vector<float> fv;
	stream >> f;
	Vector origo, direction;
	bool ringFoundInList = false;
	if(!stream)
		break;
	while(stream >> f){	
		fv.push_back(f);
	}
	if(!fv.empty()){
		origo.x = fv.at(0);
		origo.y = fv.at(1);
		origo.z = fv.at(2);
		direction.x = fv.at(3);
		direction.y = fv.at(4);
		direction.z = fv.at(5);
		ringnumber = static_cast<int>(fv.at(6));
		chance = fv.at(7);
		r = Ring::Ring(origo, direction, ringnumber, chance);
	}

	for(int i = 0; i < ringlist.length(); i++){
		float posx, posy, posz, pos;
		posx = float abs(r.x - ringlist.at(i).x);
		posy = float abs(r.y - ringlist.at(i).y);
		posz = float abs(r.z - ringlist.at(i).z);
		pos = posx + posy + posz;
		if(r.ringnumber == ringlist.at(i).ringnumber && pos < 1,5){
			if(r.chance > ringlist.at(i).chance){
				//TODO update ringlist
				ringFoundList = true;
				break;
			} else {
				ringFoundInList = true;
				break;
			}
		}
		if(r.ringnumber != ringlist.at(i).ringnumber && pos < 1,5){
			if(r.chance > ringlist.at(i).chance){
				//TODO update ringlist
				ringFoundList = true;
				break;
			} else {
				ringlist.at(i).ringnumber = r.ringnumber;
				ringFoundInList = true;
				break;
			}
		}
	}

	if(ringFoundInList == false){
		ringlist.add(r);
	}

}