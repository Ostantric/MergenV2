#ifndef _ROS_motor_controller_Motor_h
#define _ROS_motor_controller_Motor_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"
#include "motor_controller/MotorID.h"

namespace motor_controller
{

  class Motor : public ros::Msg
  {
    public:
      typedef motor_controller::MotorID _ID_type;
      _ID_type ID;
      typedef bool _motor_enable_type;
      _motor_enable_type motor_enable;
      typedef bool _clutch_enable_type;
      _clutch_enable_type clutch_enable;
      typedef bool _break_enable_type;
      _break_enable_type break_enable;
      typedef int16_t _turn_integer_type;
      _turn_integer_type turn_integer;
      typedef int16_t _turn_rational_type;
      _turn_rational_type turn_rational;

    Motor():
      ID(),
      motor_enable(0),
      clutch_enable(0),
      break_enable(0),
      turn_integer(0),
      turn_rational(0)
    {
    }

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      offset += this->ID.serialize(outbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_motor_enable;
      u_motor_enable.real = this->motor_enable;
      *(outbuffer + offset + 0) = (u_motor_enable.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->motor_enable);
      union {
        bool real;
        uint8_t base;
      } u_clutch_enable;
      u_clutch_enable.real = this->clutch_enable;
      *(outbuffer + offset + 0) = (u_clutch_enable.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->clutch_enable);
      union {
        bool real;
        uint8_t base;
      } u_break_enable;
      u_break_enable.real = this->break_enable;
      *(outbuffer + offset + 0) = (u_break_enable.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->break_enable);
      union {
        int16_t real;
        uint16_t base;
      } u_turn_integer;
      u_turn_integer.real = this->turn_integer;
      *(outbuffer + offset + 0) = (u_turn_integer.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_turn_integer.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->turn_integer);
      union {
        int16_t real;
        uint16_t base;
      } u_turn_rational;
      u_turn_rational.real = this->turn_rational;
      *(outbuffer + offset + 0) = (u_turn_rational.base >> (8 * 0)) & 0xFF;
      *(outbuffer + offset + 1) = (u_turn_rational.base >> (8 * 1)) & 0xFF;
      offset += sizeof(this->turn_rational);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      offset += this->ID.deserialize(inbuffer + offset);
      union {
        bool real;
        uint8_t base;
      } u_motor_enable;
      u_motor_enable.base = 0;
      u_motor_enable.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->motor_enable = u_motor_enable.real;
      offset += sizeof(this->motor_enable);
      union {
        bool real;
        uint8_t base;
      } u_clutch_enable;
      u_clutch_enable.base = 0;
      u_clutch_enable.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->clutch_enable = u_clutch_enable.real;
      offset += sizeof(this->clutch_enable);
      union {
        bool real;
        uint8_t base;
      } u_break_enable;
      u_break_enable.base = 0;
      u_break_enable.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->break_enable = u_break_enable.real;
      offset += sizeof(this->break_enable);
      union {
        int16_t real;
        uint16_t base;
      } u_turn_integer;
      u_turn_integer.base = 0;
      u_turn_integer.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_turn_integer.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->turn_integer = u_turn_integer.real;
      offset += sizeof(this->turn_integer);
      union {
        int16_t real;
        uint16_t base;
      } u_turn_rational;
      u_turn_rational.base = 0;
      u_turn_rational.base |= ((uint16_t) (*(inbuffer + offset + 0))) << (8 * 0);
      u_turn_rational.base |= ((uint16_t) (*(inbuffer + offset + 1))) << (8 * 1);
      this->turn_rational = u_turn_rational.real;
      offset += sizeof(this->turn_rational);
     return offset;
    }

    const char * getType(){ return "motor_controller/Motor"; };
    const char * getMD5(){ return "c2090cd341359e92cbbe09d7c09de378"; };

  };

}
#endif