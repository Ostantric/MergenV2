#include "JoystickToMove.h"
#define maxturn 100

float JoystickToMove::motor_clock(float x, float z)
{
    float motor;
    if ((x==0) && (z==0))
    {
        motor = 0;
    }
    else if (((x>0) || (x<0)) && (z==0)) //forward or backward
    {
        motor = x;
    }
    else if ((x==0) && ((z<0) || (z>0))) //left or right
    {
        motor = z;
    }
    else
    {
        motor =0;
    }
    return motor;
}

float JoystickToMove::motor_counterclock(float x, float z)
{
    float motor;
    if ((x==0) && (z==0))
    {
        motor = 0;
    }
    else if (((x>0) || (x<0)) && (z==0)) //forward or backward
    {
        motor = -x;
    }
    else if ((x==0) && ((z<0) || (z>0))) //left or right
    {
        motor = -z;
    }
    else
    {
        motor =0;
    }
    return motor;
}

double JoystickToMove::mapf(double val, double in_min, double in_max, double out_min, double out_max) {
    return (val - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
