#include "PanTilt.h"
#include <Servo.h>
#include <Arduino.h>


PanTilt::PanTilt(int pan_pin, int tilt_pin) : m_panPin(pan_pin), m_tiltPin(tilt_pin)  {
  tiltMotor.attach(this->m_tiltPin);
//  tiltMotor.write(90);  
//  pinMode(this->m_tiltPin, OUTPUT);
  
}
   
   
void PanTilt::pan(int deg) {
  panMotor.write(deg);
}

  
void PanTilt::tilt(int deg){
  tiltMotor.write(deg);  
}  
    
