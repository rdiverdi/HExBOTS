#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//#define SERVOMIN  122 // this is the servo's "zero", don't go below this
//#define SERVOMAX  320 // this is the servo's 90 point. The tests didn't like hitting 180.
///////////////////////////////////////////////////////////////////////////
/
/
// VERY IMPORTANT NOTE: THIS IS NOT RASPI COMPATIBLE. IT'LL JUST WORK WITH 
// THE CODE THAT I'M HAVING PYTHON SPIT OUT. 
/
/
//////////////////////////////////////////////////////////////////////////

int walk1[3] = {
  // Python pull
}
int walk2[3] = {
  // Python pull
}
int walk3[3] = {
  // Python pull
}
int lift1[3] = {
  // Python pull
}
int lift2[3] = {
  // Python pull
}
int lift3[3] = {
  // Python pull
}

int n = 1;
int j = 1;  


int S1A = 0;
int S1B = 1;
int S1C = 2;
int S2A = 3;
int S2B = 4;
int S2C = 5;
int S3A = 6;
int S3B = 7;
int S3C = 8;
int S4A = 9;
int S4B = 10;
int S4C = 11;
int S5A = 12;
int S5B = 13;
int S5C = 14;
int S6A = 15;
Servo S6B;
Servo S6C;

// our servo # counter
uint8_t servonum = 0;
int pulselen;

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  S6B.attach(9);
  S6C.attach(10);

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}


void loop() {
  for (n = 0; n <= 23; n++) {
    
    // The backwards things might be a problem. For now ignore. 
    
    pwm.setPWM(S1A, 0, 320+(2.2*lift1[(n*3)]));
    pwm.setPWM(S1B, 0, 320+(2.2*lift1[1+(n*3)]));
    pwm.setPWM(S1C, 0, 122+(2.2*lift1[2+(n*3)]));
    pwm.setPWM(S2A, 0, 320+(2.2*walk2[(n*3)]));
    pwm.setPWM(S2B, 0, 320+(2.2*walk2[1+(n*3)]));
    pwm.setPWM(S2C, 0, 122+(2.2*walk2[2+(n*3)]));
    pwm.setPWM(S3A, 0, 320+(2.2*lift3[(n*3)]));
    pwm.setPWM(S3B, 0, 320+(2.2*lift3[1+(n*3)]));
    pwm.setPWM(S3C, 0, 122+(2.2*lift3[2+(n*3)]));

    pwm.setPWM(S4A, 0, 320-(2.2*walk3[(n*3)]));
    pwm.setPWM(S4B, 0, 320-(2.2*walk3[1+(n*3)]));
    pwm.setPWM(S4C, 0, 518-(2.2*walk3[2+(n*3)]));
    pwm.setPWM(S5A, 0, 320-(2.2*lift2[(n*3)]));
    pwm.setPWM(S5B, 0, 320-(2.2*lift2[1+(n*3)]));
    pwm.setPWM(S5C, 0, 518-(2.2*lift2[2+(n*3)]));
    pwm.setPWM(S6A, 0, 320-(2.2*walk1[(n*3)]));
    S6B.write(90-walk1[1+(n*3)]);
    S6C.write(180-walk1[2+(n*3)]);

    
    
    delay(200);
  }
  n = 0;
  for (n = 0; n <= 23; n ++) {  
    pwm.setPWM(S1A, 0, 320+(2.2*walk1[(n*3)]));
    pwm.setPWM(S1B, 0, 320+(2.2*walk1[1+(n*3)]));
    pwm.setPWM(S1C, 0, 122+(2.2*walk1[2+(n*3)]));
    pwm.setPWM(S2A, 0, 320+(2.2*lift2[(n*3)]));
    pwm.setPWM(S2B, 0, 320+(2.2*lift2[1+(n*3)]));
    pwm.setPWM(S2C, 0, 122+(2.2*lift2[2+(n*3)]));
    pwm.setPWM(S3A, 0, 320+(2.2*walk3[(n*3)]));
    pwm.setPWM(S3B, 0, 320+(2.2*walk3[1+(n*3)]));
    pwm.setPWM(S3C, 0, 122+(2.2*walk3[2+(n*3)]));

    pwm.setPWM(S4A, 0, 320-(2.2*lift3[(n*3)]));
    pwm.setPWM(S4B, 0, 320-(2.2*lift3[1+(n*3)]));
    pwm.setPWM(S4C, 0, 518-(2.2*lift3[2+(n*3)]));
    pwm.setPWM(S5A, 0, 320-(2.2*walk2[(n*3)]));
    pwm.setPWM(S5B, 0, 320-(2.2*walk2[1+(n*3)]));
    pwm.setPWM(S5C, 0, 518-(2.2*walk2[2+(n*3)]));
    pwm.setPWM(S6A, 0, 320-(2.2*lift1[(n*3)]));
    S6B.write(90-lift1[1+(n*3)]);
    S6C.write(180-lift1[2+(n*3)]);
    
    delay(200);
  }
  n = 0;
}