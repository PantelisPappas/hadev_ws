#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "vector"

class PolarHistogram
{
private:
  ros::Subscriber sub;
  ros::Publisher histogram_pub;
  ros::NodeHandle nh;

public:
  PolarHistogram(){
   sub = nh.subscribe<sensor_msgs::LaserScan>("/scan_with_noise",1000, &PolarHistogram::laserCallback, this);
   histogram_pub = nh.advertise<sensor_msgs::LaserScan>("laser_histogram", 20);


  }
  void createHistogram(const sensor_msgs::LaserScan::ConstPtr& scan)//create a histogram with 720 data vector in a -120 -- +120 degree range
  {
    const std::vector<float> v = scan->ranges; //get data
    std::vector<float> histvalues; //create a vector for histogram
    histvalues.resize(269);     //resize in 270 range
    std::fill(histvalues.begin(), histvalues.end(), 0); //fill it up with 0s
    for (unsigned int pos = 0; pos < v.size(); pos=+2)
    {
      if (v[pos] > v[pos+1])
      {
        histvalues.push_back(v[pos]);
      }
      else
      {
        histvalues.push_back(v[pos+1]);
      }
    }
  }


void laserCallback(const sensor_msgs::LaserScan::ConstPtr scan)
{

  //just a callback function
  //const std::vector<float> v = scan->ranges;
  //ROS_INFO("Vector Size [%f]", v[720]);
  //std::cout<<"test";
}


};

  //ROS_INFO(); //pws mporw na travi3w olo to vector???

int main(int argc, char **argv)
{
  ros::init(argc, argv, "laser_listener");

  PolarHistogram VPH;

  ros::spin();
}
