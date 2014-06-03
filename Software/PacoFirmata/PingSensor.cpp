#include "PingSensor.h"


long PingSensor::microsecondsToCentimeters(long microseconds)
{
  // The speed of sound is 340 m/s or 29 microseconds per centimeter.
  // The ping travels out and back, so to find the distance of the
  // object we take half of the distance travelled.
  return microseconds / 29 / 2;
}


PingSensor::PingSensor(int pin){
   this->duration = 0;
   this->sensorPin = pin;
   pinMode(this->sensorPin, OUTPUT);
   digitalWrite(this->sensorPin, HIGH); // Trig pin is normally HIGH    
}


long PingSensor::readDistance(){
  
  pinMode(this->sensorPin, OUTPUT);
  digitalWrite(this->sensorPin, LOW);
  delayMicroseconds(25);
  digitalWrite(this->sensorPin, HIGH);
  this->duration = micros();
  pinMode(this->sensorPin, INPUT);
  int  sizeofpulse = pulseIn(this->sensorPin, LOW, 18000); //should be approx 150usec, timeout at 18msec
  this->duration = micros() - this->duration - sizeofpulse; // amount of time elapsed since we sent the trigger pulse and detect the echo pulse, then subtract the size of the echo pulse
  return  (this->duration *340.29/2/10000)-3;
}
