#include <ros/ros.h>
#include <std_msgs/Float64.h>
#include <std_msgs/Float64MultiArray.h>
using namespace std;


class Pubsub{

  private:

	  ros::NodeHandle handle;
	  ros::Publisher rf_pub;
	  ros::Publisher rb_pub;
	  ros::Publisher lf_pub;
	  ros::Publisher lb_pub;
	  ros::Subscriber sub;
    std_msgs::Float64 rf;
    std_msgs::Float64 rb;
    std_msgs::Float64 lf;
    std_msgs::Float64 lb;

  public:
    Pubsub(ros::NodeHandle n){
      handle = n;
	    sub = handle.subscribe("/quadrupedal_robot/cpg_state", 10, &Pubsub::Callback, this);
	    rf_pub =handle.advertise<std_msgs::Float64>("/RF", 100);
	    rb_pub =handle.advertise<std_msgs::Float64>("/RH", 100);
	    lf_pub =handle.advertise<std_msgs::Float64>("/LF", 100);
	    lb_pub =handle.advertise<std_msgs::Float64>("/LH", 100);
    }

    
    void Callback(const std_msgs::Float64MultiArray& msg);



};


void Pubsub::Callback(const std_msgs::Float64MultiArray& msg){
	rf.data = msg.data[0];
	rb.data = msg.data[1];
	lf.data = msg.data[2];
	lb.data = msg.data[3];
  

  rf_pub.publish(rf);
  rb_pub.publish(rb);
  lf_pub.publish(lf);
  lb_pub.publish(lb);


}

int main(int argc, char **argv){
	ros::init(argc, argv, "cpg_reader");

	ros::NodeHandle n;

  Pubsub pusub(n);


  ros::spin();


	


}
