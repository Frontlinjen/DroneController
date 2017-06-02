#include "Commands.h"
	Commands::Commands() : loop_rate(10){
		comPub = n.advertise<std_msgs::String>(n.resolveName("tum_ardrone/com"), 50);
		flattrimClient = n.serviceClient<std_srvs::Empty>(n.resolveName("ardrone/flattrim"),1);	
		ros::Duration(2).sleep();
	}

	void Commands::comCallback(const std_msgs::String::ConstPtr& msg){
		ROS_INFO("com: I heard: %s", msg->data.c_str());
	}

	std_msgs::String Commands::command(std::string command){
		std_msgs::String st_cmd;
		st_cmd.data = command;
		return st_cmd;
	}

	void Commands::autoInit(){
		comPub.publish(command("c autoInit 500 800 4000 0.5"));
		ROS_INFO("Sent autoInit");
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::land(){
		comPub.publish(command("c land"));
		ROS_INFO("Sent land");
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::takeoff(){
		comPub.publish(command("c takeoff"));
		ROS_INFO("Sent takeoff");
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::flattrim(){
		std_srvs::Empty flat;
		flattrimClient.call(flat);
		ROS_INFO("Sent flattrim");
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::reset(){
		//TODO call reset
		ROS_INFO("Sent reset");
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::goTo(float x, float y, float z, float yaw){
		std::stringstream com;
		com << "c goto " << x << " " << y << " " << z << " " << yaw;
		comPub.publish(command(com.str()));
		ROS_INFO("Sent goto");
		ros::spinOnce();
		loop_rate.sleep();
	}
	
	void Commands::moveBy(float x, float y, float z, float yaw){
		std::stringstream com;
		com << "c moveBy " << x << " " << y << " " << z << " " << yaw;
		comPub.publish(command(com.str()));
		ROS_INFO("Sent moveBy");
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::prepare(){
		ROS_INFO("Preparing...");
		comPub.publish(command("c start"));
		ros::spinOnce();
		loop_rate.sleep();
		//TODO Calibrate
		//ros::spinOnce();
		//loop_rate.sleep();
		//TODO Flattrim
		//ros::spinOnce();
		//loop_rate.sleep();
		ROS_INFO("Done.");
	}

	void Commands::lookForRings(){
		goTo(0,0,0,360);
	}