#ifndef __PACO_H__
#define __PACO_H__
#include <Arduino.h>
#include "PacoConfig.h"
#include "PanTilt.h"
#include "Adafruit_Neopixel.h"

class Adafruit_SSD1306;
class PingSensor;

class Paco {
  
  public:
 
      Paco();
      void init();
      /** Read the distance in centimeters from the nearest object in front of Paco **/
      long readDistance();
      /** Show a text on the screen **/
      void showText(char* text);
      /** Show a bitmap on the screen **/
      void showBitmap(int bitmap);
      /** Clear the screen **/
      void clearScreen();
      /** Pan the camera **/
      void panCamera(int deg);
      /** Tilt the camera **/
      void tiltCamera(int deg);
      void testServo();
        /** Set a led color **/
      void setLed(int ledno, int red, int green, int blue);
      /** Set global led brightness **/
      void setLedBrightness(int brightness);
      
      /** show test sequence **/
      
      void test();
  
    private:
  
      void showBootInfo();
      void drawXBM(prog_uchar* logo_data);
      PingSensor* pingSensor;
      Adafruit_SSD1306* screen;
      Adafruit_NeoPixel* pixels;
//      Servo panTilt;

};
















#endif


