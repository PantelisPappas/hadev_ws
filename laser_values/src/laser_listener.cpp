#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "vector"

void poseMessageReceived(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  std::vector<float> v = scan->ranges;

  for (unsigned int i=0; i<v.size();i++) {
    std::cout << v[i];
  }
}

  //ROS_INFO(); //pws mporw na travi3w olo to vector???

int main(int argc, char **argv)
{
  ros::init(argc, argv, "laser_listener");
  ros::NodeHandle nh;

  ros::Subscriber sub = nh.subscribe("/scan_with_noise",1000, poseMessageReceived);

  ros::spin();

  return 0;
}
