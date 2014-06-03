#ifndef __PACO_PING_H__
#define __PACO_PING_H__

#include <Arduino.h>

class PingSensor {
  
  public:
  
    PingSensor(int pingPin);
        
    long readDistance();
  
  private:
  
    int sensorPin;
    long duration;
  
    long microsecondsToCentimeters(long microseconds);
};


#endif
