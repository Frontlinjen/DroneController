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
		//comPub.publish(command("c autoInit 500 800 4000 0.5"));
		ROS_INFO("Sent autoInit");
	}

	void Commands::land(){
		//comPub.publish(command("c land"));
		ROS_INFO("Sent land");
	}

	void Commands::takeoff(){
		//comPub.publish(command("c takeoff"));
		ROS_INFO("Sent takeoff");
	}

	void Commands::setReference(){
		//comPub.publish(command("c setReference $POSE$"));
		ROS_INFO("Sent set reference point");

	}

	void Commands::flattrim(){
		std_srvs::Empty flat;
		//flattrimClient.call(flat);
		ROS_INFO("Sent flattrim");
	}

	void Commands::reset(){
		//TODO call reset
		ROS_INFO("Sent reset");
	}

	void Commands::goTo(float x, float y, float z, float yaw){
		std::stringstream com1;
		//std::stringstream com2;
		Vector mypos = transformDataListener.getPosition();
		com1 << "c goto " << x << " " << y << " " << z << " " << yaw;
		//com2 << "c goto " << x << " " << y << " " << mypos.z << " " << yaw;
			//comPub.publish(command(com1.str()));
		//comPub.publish(command(com2.str()));
		std::cout << com1.str() << "\n";
		//std::cout << com2.str() << "\n";
	}
	
	void Commands::moveBy(float x, float y, float z, float yaw){
		std::stringstream com;
		com << "c moveBy " << x << " " << y << " " << z << " " << yaw;
		//comPub.publish(command(com.str()));
		ROS_INFO("Sent moveBy");
	}

	void Commands::clearCommands(){
		//comPub.publish(command("c clearCommands"));
		ROS_INFO("Sent clearCommands");
	}

	void Commands::prepare(){
		ROS_INFO("Preparing...");
		comPub.publish(command("c start"));
		comPub.publish(command("c setReference $POSE$"));
		comPub.publish(command("c setInitialReachDist 0.2"));
		comPub.publish(command("c setStayWithinDist 0.3"));
		comPub.publish(command("c setStayTime 3"));
		comPub.publish(command("c lockScaleFP"));
	}

	void Commands::lookForRings(){
		/*goTo(0,0,0,90);
		goTo(0,0,0,180);
		goTo(0,0,0,270);
		goTo(0,0,0,0);*/
	}
