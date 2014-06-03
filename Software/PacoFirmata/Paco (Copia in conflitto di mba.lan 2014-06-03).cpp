#include <Arduino.h>
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ping.h>
#include "PingSensor.h"
#include "Paco.h"
#include "PacoBitmaps.h"


Paco::Paco() {
 
 this->pingSensor = new PingSensor( PACO_ULTRASONIC_PIN); 
 this->screen = new Adafruit_SSD1306(PACO_DISPLAY_RESET);
//  this->panTilt = new PanTilt(PACO_MOTOR1_PWM, PACO_MOTOR2_PWM);
//  this->panTilt.attach(A3);
}

void Paco::init(){
  // Init display
  screen->begin(SSD1306_SWITCHCAPVCC,0x3D);
  this->showBootInfo();
  delay(2000);
  this->showBitmap(0);
  screen->display();
}



void Paco::showBootInfo() { 
  screen->clearDisplay();
  screen->setTextSize(1);
  screen->setTextColor(WHITE);
  screen->setCursor(0,0);
  screen->println("PACO Booting...");
  screen->display();
  delay(1000);
  screen->setCursor(0,20);
  screen->println("Version 0.1");
  screen->display();  
  delay(1000);
  for (int i=0; i<10; i++){
  screen->clearDisplay();
  screen->setCursor(0,0);
  screen->println("Ultrasonic test");
  screen->setCursor(0,20);
  screen->println(i);
  screen->setCursor(0,40);
  long dist = this->readDistance();
  screen->println(dist);
  screen->display();
  delay(1000);
  }
  screen->clearDisplay();
  screen->setCursor(0,0);
  screen->println("Tilt test");
  screen->display();  
//  this->testServo();
}

long Paco::readDistance(){

 return this->pingSensor->readDistance(); 
}

void Paco::testServo(){
//  for (int i=0; i<=180; i++){
//    this->panTilt.write(i);
//    delay(15);
//  }
//  for (int i=180; i>=0; i++){
//    this->panTilt.write(i);
//    delay(15);
//  }  
}


/** Show a text on the screen **/
void Paco::showText(char* text) {
  screen->clearDisplay();
  screen->setTextSize(1);
  screen->setTextColor(WHITE);
  screen->setCursor(0,0);
  screen->println(text);
  screen->display();   
}

/** Show a bitmap on the screen **/
void Paco::showBitmap(int bitmap) {
  switch (bitmap){
     default:
        this->drawXBM(Grin_bits); 
        break;
  }
}

void Paco::drawXBM(prog_uchar* logo_data) {
uint8_t xbmx, xbmy;
uint8_t xbmdata;
screen->clearDisplay();
	/*
	 * Traverse through the XBM data byte by byte and plot pixel by pixel
	 */
	for(xbmy = 0; xbmy < screen->height(); xbmy++)
	{
		for(xbmx = 0; xbmx < screen->width(); xbmx++)
		{
                  if(!(xbmx & 7))	// read the flash data only once per byte
  				xbmdata = pgm_read_word(logo_data++);
  
                  if(xbmdata & _BV((xbmx & 7))) {
                    screen->drawPixel(xbmx, xbmy, WHITE);
                  } else {
                    
                    screen->drawPixel(xbmx, xbmy, BLACK);                    
                  }
                }
                
        }

screen->display();

 // display.refresh();
}


/** Clear the screen **/
void Paco::clearScreen() {
  screen->clearDisplay();
  screen->display();
} 
/** Pan the camera **/
void Paco::panCamera(int deg) {
  
//  panTilt->pan(deg);
  
}
/** Tilt the camera **/
void Paco::tiltCamera(int deg) {
//  this->panTilt.write(deg);
  
}

