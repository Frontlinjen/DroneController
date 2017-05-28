

int main(int argc, char **argv){
	ros::init(argc,argv,"pilot");
	Pilot p = Pilot();
	p.mainLoop();
}