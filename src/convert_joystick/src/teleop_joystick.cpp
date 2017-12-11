#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>
#include <std_msgs/Bool.h>

class TeleopDongbu
{
public:
  TeleopDongbu();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);
  bool light=false;
  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Publisher xbox_light_pub;
  ros::Subscriber joy_sub_;

};


TeleopDongbu::TeleopDongbu():
  linear_(1),
  angular_(2)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/cmd_vel", 1);
  xbox_light_pub = nh_.advertise<std_msgs::Bool>("/xbox_light", 1);


  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &TeleopDongbu::joyCallback, this);

}

void TeleopDongbu::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
  std_msgs::Bool msg_light;
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*joy->axes[angular_];
  twist.linear.x = l_scale_*joy->axes[linear_];
  if ((twist.angular.z == 0) && (twist.linear.x == 0))
  {
    light=false;
  }
  else
  {
    light=true;
  }
  msg_light.data=light;
  xbox_light_pub.publish(msg_light);
  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "teleop_Mergen");
  TeleopDongbu object;

  ros::spin();
}
