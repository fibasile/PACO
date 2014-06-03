#include <Arduino.h>
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Ping.h>
#include "PingSensor.h"
#include "Paco.h"
#include "PacoBitmaps.h"

#define BOOT_DELAY 1000

Paco::Paco() {
 
 this->pingSensor = new PingSensor( PACO_ULTRASONIC_PIN); 
 this->screen = new Adafruit_SSD1306(PACO_DISPLAY_RESET);
  this->pixels = new Adafruit_NeoPixel(PACO_LEDS_COUNT, PACO_LEDS_PIN, 0x01 + 0x02);
}

void Paco::init(){
  // Init display
  pixels->begin();
  pixels->setBrightness(0);
  pixels->show();
  screen->begin(SSD1306_SWITCHCAPVCC,0x3D);
 
  this->showBitmap(1);
  screen->display();
  delay(BOOT_DELAY);
  this->showBitmap(0);
  screen->display();
  delay(BOOT_DELAY);
}

void Paco::test(){

  this->showBootInfo();
  delay(BOOT_DELAY);
   screen->display();
}



void Paco::setLed(int ledno, int red, int green, int blue) {
  if (ledno < 9) {
  this->pixels->setPixelColor(ledno, red, green, blue);
  this->pixels->show();
  } else {
     for (int i=0; i<9; i++) {
      this->pixels->setPixelColor(i, red, green, blue);
     } 
     this->pixels->show();
  }
}


void Paco::setLedBrightness(int brightness) {
  
  this->pixels->setBrightness(brightness);
  this->pixels->show();
}

      

void Paco::showBootInfo() { 
  screen->clearDisplay();
  screen->setTextSize(1);
  screen->setTextColor(WHITE);
  screen->setCursor(0,0);
  screen->println("PACO Booting...");
  screen->display();
  delay(BOOT_DELAY);
  screen->setCursor(0,20);
  screen->println("Version 0.1");
  screen->display();  
  delay(BOOT_DELAY);
  for (int i=0; i<3; i++){
  screen->clearDisplay();
  screen->setCursor(0,0);
  screen->println("Ultrasonic test");
  screen->setCursor(0,20);
  screen->println(i);
  screen->setCursor(0,40);
  long dist = this->readDistance();
  screen->println(dist);
  screen->display();
  delay(BOOT_DELAY);
  }
    screen->clearDisplay();
  screen->setCursor(0,0);
  screen->println("Led Test");
  screen->display();  
  pixels->setBrightness(128);
  for (int i=0; i<9;i++){
   this->setLed(i,0,255,0); 
   delay(100);
  }
  delay(100);
  this->setLedBrightness(0);
  delay(BOOT_DELAY);  
  this->setLedBrightness(0);
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

}


/** Show a text on the screen **/
void Paco::showText(char* text) {
  screen->clearDisplay();
  screen->display();   
  screen->setTextSize(2);
  screen->setTextColor(WHITE);
  screen->setCursor(0,0);
  screen->println(text);
  screen->display();   
  free(text);
}

/** Show a bitmap on the screen **/
void Paco::showBitmap(int bitmap) {
  switch (bitmap){
     case 1:
        this->drawXBM(Beach_bits); 
        break;         
     case 2:
        this->drawXBM(Smile_bits); 
        break;         
     case 3:
        this->drawXBM(Grin_bits); 
        break;         
     case 4:
        this->drawXBM(Sad_bits); 
        break;         
     default:
        this->drawXBM(Logo_bits); 
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

