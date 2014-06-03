  
#include <Wire.h>
//#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>
#include <Ping.h>
#include "Paco.h"
#include "PacoConfig.h"
#include "PacoCommands.h"
#include "Firmata.h"

Paco paco;
Servo panServo;
Servo tiltServo;
int panAngle=85;
int npanAngle=90;
int tiltAngle=45;
int ntiltAngle=50;
int dst;
long lastUpdate = 0;

void IntegerToBytes(long val, byte b[4]) {
  b[0] = (byte )((val >> 24) & 0xff);
  b[1] = (byte )((val >> 16) & 0xff);
  b[2] = (byte )((val >> 8) & 0xff);
  b[3] = (byte )(val & 0xff);
}

void stringCallback(char *myString)
{
    Firmata.sendString(myString);
}





void sysexCallback(byte command, byte argc, byte*argv){
//    Serial.println("Sysex command");

//    for (byte i=0;i<argc; i++){
//      Serial.println(argv[i], DEC);
//    }
   
    
    if (argc > 0) {
    
            switch (command) {
              case PACO_CMD_PAN:
                if (argc >= 1){
//                  Serial.println("Pan command received");
                  npanAngle = argv[0] | argv[1] << 7 ;
                  updateServo();
                } else {
//                   Serial.println("Invalid param count for PACO_CMD_PAN"); 
                }
                break;
              case PACO_CMD_TILT:
                if (argc >= 1){
//                  Serial.println("Tilt command received");
                  ntiltAngle = argv[0] | argv[1] << 7;
                  updateServo();
                } else {
//                   Serial.println("Invalid param count for PACO_CMD_TILT"); 
                }
                break;
              case PACO_CMD_SHOW_TXT:
               if (argc >0) {
                  paco.showText((char*)argv);
                } else {
//                   Serial.println("Invalid param count for PACO_CMD_SHOW_TXT"); 
                }
                break;
              case PACO_CMD_SHOW_BMP:
                if (argc >= 1){
//                  Serial.println("Show bitmap command received");
                    paco.showBitmap(argv[0]);
                } else {
//                   Serial.println("Invalid param count for PACO_CMD_SHOW_BMP"); 
                }
              
                break;
              case PACO_CMD_CLEAR_SCREEN:
//                Serial.println("Clear screen command received");
                paco.clearScreen();
                Firmata.sendSysex(0x0A,0,NULL);
                break;
              case PACO_CMD_READ_DISTANCE:
//                Serial.println("Read distance command received");
//                sendDistance();
                break;
              case PACO_CMD_SET_LED:
                if (argc >= 8){
                  int led_no = argv[0] | argv[1] << 7;
                  int red = argv[2] | argv[3] << 7;
                  int green = argv[4] | argv[5] << 7;
                  int blue = argv[6] | argv[7] << 7;
                  paco.setLed(led_no,red,green,blue);
                } else {
//                  Serial.println("Invalid param count for PACO_CMD_SET_LED"); 
                }            
                break;
              case PACO_CMD_SET_BRIGHT:
//                Serial.println("Set led brightness command received");
                if (argc >= 2){
                  int bright = argv[0] | argv[1] << 7;
                  paco.setLedBrightness(bright);              
                } else {
//                  Serial.println("Invalid param count for PACO_CMD_SET_BRIGHT");               
                }
                break;
              case PACO_CMD_TEST:
                paco.test();
                break;
            }
    }
}





void setup() {
  // put your setup code here, to run once:
//  Serial.begin(57600);
//   pinMode(13, OUTPUT);

  tiltServo.attach(9);
  panServo.attach(11);
  updateServo();
  
   Firmata.setFirmwareVersion(0, 1);
    Firmata.attach(STRING_DATA, stringCallback);
    Firmata.attach(START_SYSEX, sysexCallback);
    Firmata.begin(115200);


  paco.init();
}

int ease(int cur, int target){
   if (cur > target) {
    return -1 ;
   } else if (cur < target) {
     return 1;
   } else {
     return 0;
   }
}

void updateServo(){
    while (tiltAngle!=ntiltAngle){
      tiltAngle+= ease( tiltAngle, ntiltAngle);
      tiltServo.write(tiltAngle);
      delay(15); 
    }
    while (panAngle!=npanAngle){
      panAngle+= ease( panAngle, npanAngle);
      panServo.write(panAngle);
      delay(15); 
    } 
}

void sendDistance(){
    int a = paco.readDistance();
    byte da[1] = { a }; 
    Firmata.sendSysex(PACO_EVT_DISTANCE,1,da);

}

void loop() {
  // put your main code here, to run repeatedly:

//  while(Serial.available()){
//     Serial.write(Serial.read()); 
//  }
// 
    while(Firmata.available()) {
        Firmata.processInput();
    }
//     delay(100);  
    if (lastUpdate == 0 || millis() - lastUpdate > 2000){ 
      lastUpdate = millis();
      sendDistance();
    }
}
