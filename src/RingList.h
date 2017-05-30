class RingList{
	
	private:
		std::mutex ringList_mutex;
		vector<Ring> ringList;
		ros::NodeHandle n;
		ros::Rate loop_rate;
		ros::Subscriber sub;
		
		void updateRing(Ring r1, Ring r2);
		void updateRingnumber(Ring r1, Ring r2);
		Ring getRing(int i);
		void updateList(Ring r);
		void opencvCallback(const std_msgs::String::ConstPtr& msg);
		void msgHandle(std_msgs::String::ConstPtr& msg);
		bool listening = false;

	public:
		RingList();
}
