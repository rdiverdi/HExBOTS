#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//#define SERVOMIN  122 // this is the 'minimum' pulse length count (out of 4096)
//#define SERVOMAX  320 // this is the 'maximum' pulse length count (out of 4096

// our servo # counter
uint8_t servonum = 0;
int pulselen;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  pwm.begin();
  
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates
}

// THIS IS THE CALIBRATION FUNCTION. YOU SHOULD USE IT.


void loop() {
  pwm.setPWM(0, 0, 255);
  pwm.setPWM(3, 0, 221);
  pwm.setPWM(6, 0, 122);
  pwm.setPWM(9, 0, 122);
  pwm.setPWM(12, 0, 221);
  pwm.setPWM(15, 0, 255);

// These are the long middle joints set to 45 degrees. Again, use the chart
  pwm.setPWM(1, 0, 221);
  pwm.setPWM(4, 0, 221);
  pwm.setPWM(7, 0, 221);
  pwm.setPWM(10, 0, 221);
  pwm.setPWM(13, 0, 221);

// These are the feet going to 125 degrees. Use the chart. 
  pwm.setPWM(2, 0, 397);
  pwm.setPWM(5, 0, 397);
  pwm.setPWM(8, 0, 397);
  pwm.setPWM(11, 0, 397);
  pwm.setPWM(14, 0, 397);

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
