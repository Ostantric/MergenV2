
/* FreeRTOS.org includes. */
#include "FreeRTOS_AVR.h"
//#include "task.h"

/* Demo includes. */
#include "basic_io_avr.h"

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
std_msgs::String str_msg;
ros::Publisher pub("arduino", &msg_flt);
ros::Publisher hi("arduino_str", &str_msg);
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
/* The task function. */
void vTaskFunction( void *pvParameters );
void vTaskSpin( void *pvParameters );

/*-----------------------------------------------------------*/
char hello[13] = "hello world!";

void setup( void )
{
  nh.initNode();
  nh.subscribe(sub);
  nh.advertise(pub);
  nh.advertise(hi);
  HWS1.begin(9600);
  HWS2.begin(9600);
  ST1.autobaud();
  ST2.autobaud();
  //Serial.begin(9600);
  /* Create the first task at priority 1... */
  xTaskCreate( vTaskFunction, "Task 1", 200, NULL, 2, NULL );
  xTaskCreate( vTaskSpin, "Spin Task", 200, NULL, 1, NULL);
  /* ... and the second task at priority 2.  The priority is the second to
  last parameter. */
  //xTaskCreate( vTaskFunction, "Task 2", 200, NULL, 2, NULL );

  /* Start the scheduler so our tasks start executing. */
  vTaskStartScheduler();

  for( ;; );
//  return 0;
}
/*-----------------------------------------------------------*/

void vTaskFunction( void *pvParameters )
{
  /* As per most tasks, this task is implemented in an infinite loop. */
  for( ;; )
  {
    /* Print out the name of this task. */
    str_msg.data = hello;
    hi.publish(&str_msg);
    /* Delay for a period.  This time we use a call to vTaskDelay() which
    puts the task into the Blocked state until the delay period has expired.
    The delay period is specified in 'ticks'. */
    
    vTaskDelay( 25 / portTICK_PERIOD_MS );
  }
}

void vTaskSpin( void *pvParameters )
{
  for( ;; )
  {
      nh.spinOnce(); 
    vTaskDelay( 5 / portTICK_PERIOD_MS );
  }
}


//------------------------------------------------------------------------------
void loop() {
  //delay(1);
  }

  double mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}

