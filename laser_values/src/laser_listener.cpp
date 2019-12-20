#include "ros/ros.h"
#include "sensor_msgs/LaserScan.h"
#include "std_msgs/Float32MultiArray.h"

class PolarHistogram
{
private:
  ros::Subscriber sub;
  ros::Publisher histogram_pub;
  ros::NodeHandle nh;
public:
  PolarHistogram(){

   histogram_pub = nh.advertise<std_msgs::Float32MultiArray>("/laser_histogram", 1);
   sub = nh.subscribe<sensor_msgs::LaserScan>("/scan_with_noise",1000,
                                              &PolarHistogram::laserCallback, this);

  }

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
{
  const std::vector<float> v = scan->ranges; //get data
  std_msgs::Float32MultiArray histvalues;
  histvalues.data.clear();
  //for (unsigned int i= 0; i < v.size(); i+=2){    //360degree range
   // histvalues.data.push_back(std::max(v[i] , (v[i+1] )));
 // }
  for (unsigned int i= 0; i < v.size(); i+=3){      //240 degree range
    histvalues.data.push_back(std::max(v[i] , std::max(v[i+1] , v[i + 2]))); //condition of histogram max( of 3 laser readings)
  }

 histogram_pub.publish(histvalues);
 //ROS_INFO("Size [%lu]", histvalues.data.size());


//  histvalues.resize(269);     //resize in 270 range
//  std::fill(histvalues.begin(), histvalues.end(), 0); //fill it up with 0s
//  for (unsigned int pos = 0; pos < v.size(); pos=+2)
//  {
//   if (v[pos] > v[pos+1])
//    {
//      histvalues.push_back(v[pos]);
//    }
//   else
//    {
//      histvalues.push_back(v[pos+1]);
//    }
//  }
  //histogram_pub.publish(histvalues); //pws kanoume publish to vector???
}
  //just a callback function
  //const std::vector<float> v = scan->ranges;
  //ROS_INFO("Vector Size [%f]", v[720]);
  //std::cout<<"test";

};

  //ROS_INFO(); //pws mporw na travi3w olo to vector???

int main(int argc, char **argv)
{
  ros::init(argc, argv, "laser_listener");
  PolarHistogram VPH;
  ros::spin();
}
