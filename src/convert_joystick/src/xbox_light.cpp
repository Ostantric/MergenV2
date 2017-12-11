#include <ros/ros.h>
#include <std_msgs/Bool.h>
#include <iostream>

/**
 * This tutorial demonstrates simple receipt of messages over the ROS system.
 */
void LightCallback(const std_msgs::Bool msg)
{
    std::system("sudo chmod 777 /sys/class/leds/xpad0/brightness");
    if (msg.data==true)
    {
        std::system("echo 13 > /sys/class/leds/xpad0/brightness");
        ROS_INFO("moving");
    }
    else
    {
        std::system("echo 6 > /sys/class/leds/xpad0/brightness");
        ROS_INFO("idle");
    }
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "teleop_Mergen");

  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("xbox_light", 1000, LightCallback);
  ros::spin();
  return 0;
}


