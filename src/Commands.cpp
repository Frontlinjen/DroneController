#include "Commands.h"
	Commands::Commands() : loop_rate(10){
		comPub = n.advertise<std_msgs::String>(n.resolveName("tum_ardrone/com"), 1000);
		flattrimClient = n.serviceClient<std_srvs::Empty>(n.resolveName("ardrone/flattrim"),1000);	
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
		ros::Duration(2).sleep();
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

	void Commands::setReference(){
		comPub.publish(command("c setReference $POSE$"));
		ROS_INFO("Sent set reference point");
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
		std::cout << com.str() << "\n";
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

	void Commands::clearCommands(){
		comPub.publish(command("c clearCommands"));
		ROS_INFO("Sent clearCommands");
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::prepare(){
		ROS_INFO("Preparing...");
		comPub.publish(command("c start"));
		comPub.publish(command("c setReference $POSE$"));
		comPub.publish(command("c setInitialReachDist 0.2"));
		comPub.publish(command("c setStayWithinDist 0.3"));
		comPub.publish(command("c setStayTime 3"));
		comPub.publish(command("c lockScaleFP"));
		ros::spinOnce();
		loop_rate.sleep();
	}

	void Commands::lookForRings(){
		goTo(0,0,0,360);
	}