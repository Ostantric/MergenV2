#ifndef _ROS_motor_controller_MotorID_h
#define _ROS_motor_controller_MotorID_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace motor_controller
{

  class MotorID : public ros::Msg
  {
    public:
      typedef int16_t _Id_type;
      _Id_type Id;

    MotorID():
      Id(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_Id;
      u_Id.real = this->Id;
      *(outbuffer + offset + 0) = (u_Id.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_Id.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->Id);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      union {
        int16_t real;
        uint16_t base;
      } u_Id;
      u_Id.base = 0;
      u_Id.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_Id.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->Id = u_Id.real;
      offset += sizeof(this->Id);
     return offset;
    }

    const char * getType(){ return "motor_controller/MotorID"; };
    const char * getMD5(){ return "e27d3f577f1e4f621c9665623a965abc"; };

  };

}
#endif