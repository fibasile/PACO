#ifndef __PACO_PAN_TILT__
#define __PACE_PAN_TILT__

#include <Servo.h>

class PanTilt {
 
 public:

    PanTilt(int pan_pin, int tilt_pin);
   
   
    void pan(int deg);
    void tilt(int deg);
    
 private:
 
    int m_panPin;
    int m_tiltPin;
    Servo panMotor;
    Servo tiltMotor;
 
  
  
};

#endif
