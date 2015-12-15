#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//#define SERVOMIN  122 // this is the 'minimum' pulse length count (out of 4096)
//#define SERVOMAX  320 // this is the 'maximum' pulse length count (out of 4096

// our servo # counter
uint8_t servonum = 0;
int pulselen;
Servo S6B;
Servo S6C;
void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();

  S6B.attach(9);
  S6C.attach(10);
  
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
  pwm.setPWM(0,0,0);
  pwm.setPWM(1,0,0);
  pwm.setPWM(2,0,0);
  pwm.setPWM(3,0,0);
  pwm.setPWM(4,0,0);
  pwm.setPWM(5,0,0);
  pwm.setPWM(6,0,0);
  pwm.setPWM(7,0,0);
  pwm.setPWM(8,0,0);
  pwm.setPWM(9,0,0);
  pwm.setPWM(10,0,0);
  pwm.setPWM(11,0,0);
  pwm.setPWM(12,0,0);
  pwm.setPWM(13,0,0);
  pwm.setPWM(14,0,0);
  pwm.setPWM(15,0,0);
}

// THIS IS THE CALIBRATION FUNCTION. YOU SHOULD USE IT.
// 320 is 90, 221 is 45, 122 is 0. I don't know what 255 is.

void loop() {
  pwm.setPWM(0, 0, 320-(2.2*23));
  pwm.setPWM(3, 0, 320);
  pwm.setPWM(6, 0, 320);
  pwm.setPWM(9, 0, 320);
  pwm.setPWM(12, 0, 320);
  pwm.setPWM(15, 0, 320);

// These are the long middle joints set to 45 degrees. Again, use the chart
  pwm.setPWM(1, 0, 320);
  pwm.setPWM(4, 0, 320);
  pwm.setPWM(7, 0, 320);
  pwm.setPWM(10, 0, 320);
  pwm.setPWM(13, 0, 320);
  S6B.write(90);
  

// These are the feet going to 125 degrees. Use the chart. 
  pwm.setPWM(2, 0, 320);
  pwm.setPWM(5, 0, 320);
  pwm.setPWM(8, 0, 320);
  pwm.setPWM(11, 0, 320);
  pwm.setPWM(14, 0, 320);
  S6C.write(90); //13

  // Drive each servo one at a time
//  for (int angle = SERVOMIN; angle < SERVOMAX; angle++) {
//    pulselen = map(angle, -45, 45, 122, 320); 
//    pwm.setPWM(servonum, 0, pulselen);
//    delay(10);
//  }
//  //delay(1000);
//  for (int angle = SERVOMAX; angle > SERVOMIN; angle--) {
//    pulselen = map(angle, -45, 45, 122, 320); 
//    pwm.setPWM(servonum, 0, pulselen);
//    delay(10);
//  }
  //delay(1000);

  //servonum ++;
  //if (servonum > 15) servonum = 0;
}
