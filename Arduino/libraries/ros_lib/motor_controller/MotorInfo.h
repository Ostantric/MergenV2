#ifndef _ROS_motor_controller_MotorInfo_h
#define _ROS_motor_controller_MotorInfo_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "motor_controller/Motor.h"

namespace motor_controller
{

  class MotorInfo : public ros::Msg
  {
    public:
      typedef int16_t _numberOfMotors_type;
      _numberOfMotors_type numberOfMotors;
      uint32_t MotorData_length;
      typedef motor_controller::Motor _MotorData_type;
      _MotorData_type st_MotorData;
      _MotorData_type * MotorData;

    MotorInfo():
      numberOfMotors(0),
      MotorData_length(0), MotorData(NULL)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_numberOfMotors;
      u_numberOfMotors.real = this->numberOfMotors;
      *(outbuffer + offset + 0) = (u_numberOfMotors.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_numberOfMotors.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->numberOfMotors);
      *(outbuffer + offset + 0) = (this->MotorData_length >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (this->MotorData_length >> (8 * 1)) & 0xFF;
      *(outbuffer + offset + 2) = (this->MotorData_length >> (8 * 2)) & 0xFF;
      *(outbuffer + offset + 3) = (this->MotorData_length >> (8 * 3)) & 0xFF;
      offset += sizeof(this->MotorData_length);
      for( uint32_t i = 0; i < MotorData_length; i++){
      offset += this->MotorData[i].serialize(outbuffer + offset);
      }
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_numberOfMotors;
      u_numberOfMotors.base = 0;
      u_numberOfMotors.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_numberOfMotors.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->numberOfMotors = u_numberOfMotors.real;
      offset += sizeof(this->numberOfMotors);
      uint32_t MotorData_lengthT = ((uint32_t) (*(inbuffer + offset))); 
      MotorData_lengthT |= ((uint32_t) (*(inbuffer + offset + 1))) << (8 * 1); 
      MotorData_lengthT |= ((uint32_t) (*(inbuffer + offset + 2))) << (8 * 2); 
      MotorData_lengthT |= ((uint32_t) (*(inbuffer + offset + 3))) << (8 * 3); 
      offset += sizeof(this->MotorData_length);
      if(MotorData_lengthT > MotorData_length)
        this->MotorData = (motor_controller::Motor*)realloc(this->MotorData, MotorData_lengthT * sizeof(motor_controller::Motor));
      MotorData_length = MotorData_lengthT;
      for( uint32_t i = 0; i < MotorData_length; i++){
      offset += this->st_MotorData.deserialize(inbuffer + offset);
        memcpy( &(this->MotorData[i]), &(this->st_MotorData), sizeof(motor_controller::Motor));
      }
     return offset;
    }

    const char * getType(){ return "motor_controller/MotorInfo"; };
    const char * getMD5(){ return "e87bb0de12079d007e229ed3025b3d68"; };

  };

}
#endif