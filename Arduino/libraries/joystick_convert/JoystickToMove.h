/*
 JoystickToMove.h
*/

// include types & constants of Wiring core API
#if defined(ARDUINO) && ARDUINO >= 100
#include <Arduino.h>
#else
#include <WProgram.h>
#endif

#include <math.h>

// library interface description
class JoystickToMove
{
  // user-accessible "public" interface
  public:
    float motor_clock(float, float);
    float motor_counterclock(float, float);

  // library-accessible "private" interface
  private:
    double mapf(double, double, double, double, double);
};


