#!/usr/bin/env python
import rospy
from std_msgs.msg import Float32MultiArray
from laser_values import histvalues


def callback(histvalues):
    rospy.loginfo(rospy.get_caller_id() + "I heard %s", Float32MultiArray.data)


def listener():

    # In ROS, nodes are uniquely named. If two nodes with the same
    # name are launched, the previous one is kicked off. The
    # anonymous=True flag means that rospy will choose a unique
    # name for our 'listener' node so that multiple listeners can
    # run simultaneously.
    rospy.init_node('histogram_plot', anonymous=True)

    rospy.Subscriber("/laser_histogram", Float32MultiArray, callback)

    # spin() simply keeps python from exiting until this node is stopped
    rospy.spin()


if __name__ == '__main__':
    listener()
