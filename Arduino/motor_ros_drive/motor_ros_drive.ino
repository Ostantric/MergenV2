#include <JoystickToMove.h>



#include <ros.h>
#include <geometry_msgs/Twist.h>
#include <std_msgs/Float32.h>
#include <std_msgs/String.h>
#include <Sabertooth.h>
#define HWS1 Serial1
#define HWS2 Serial2

ros::NodeHandle nh;
std_msgs::Float32 msg_flt;
ros::Publisher pub("arduino", &msg_flt);
Sabertooth ST1(128,HWS1);
Sabertooth ST2(129,HWS2);
JoystickToMove joystick;
void motor_drive( const geometry_msgs::Twist& msg)
{
  float linear,angular,motor1_send, motor2_send, motor3_send, motor4_send;
  float linear_converted, angular_converted;
  float final_value;
  String state;
  linear=msg.linear.x;
  angular=msg.angular.z;
  linear_converted=mapf(linear,-2.0,2.0,-127.0,127.0);
  angular_converted=mapf(angular,-2.0,2.0,-127.0,127.0);
  motor1_send=joystick.motor_clock(linear_converted,angular_converted);
  motor2_send=joystick.motor_clock(linear_converted,angular_converted);
  motor3_send=joystick.motor_counterclock(linear_converted,angular_converted);
  motor4_send=joystick.motor_counterclock(linear_converted,angular_converted);
  
  //Serial.println(state);
  //Serial.println(linear_converted);
  msg_flt.data=motor1_send;  
  pub.publish(&msg_flt);
  
  ST1.motor(1,motor1_send);
  ST1.motor(2,motor2_send);
}
ros::Subscriber<geometry_msgs::Twist> sub("/cmd_vel", motor_drive);

void setup()
{
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
  HWS1.begin(9600);
  HWS2.begin(9600);
  ST1.autobaud();
  ST2.autobaud();
}
void loop()
{
  nh.spinOnce();
  delay(1);
}

double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
