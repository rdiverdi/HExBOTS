#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

// called this way, it uses the default address 0x40
Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

//#define SERVOMIN  122 // this is the servo's "zero", don't go below this
//#define SERVOMAX  320 // this is the servo's 90 point. The tests didn't like hitting 180.
// Basically, 

int n = 1;
int j = 1;  

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
int top[24] = {
87,85,83,82,80,78,76,74,72,70,67,65,63,61,58,56,53,51,48,45,43,40,37,34
};

int back[24] = {
210,207,204,201,199,196,193,191,188,186,183,181,179,177,174,172,170,168,166,164,162,161,159,157
};

int mid[24] = {
159,156,153,150,146,143,140,137,133,130,127,124,120,117,114,111,107,104,101,98,94,91,88,85
};

int phi[24] = {
174,177,180,183,186,189,192,194,197,199,201,203,205,207,209,211,213,214,216,217,218,220,221,222
};

int psi[24] = {
398,391,385,379,374,369,364,359,355,350,346,342,338,335,331,328,325,322,319,316,314,311,309,307
};

int sa_phi[24] = {
225,225,226,227,228,228,229,229,229,230,230,230,230,230,230,229,229,229,228,228,227,226,225,225
};

int sa_psi[24] = {
302,301,299,298,297,296,295,294,293,293,293,293,293,293,293,293,294,295,296,297,298,299,301,302
};

int sixphi[24] = {
23,25,27,28,29,31,32,33,34,35,36,37,38,39,40,40,41,42,43,43,44,44,45,45
};

int sixpsi[24] = {
125,122,120,117,115,112,110,108,106,104,102,100,98,97,95,94,92,91,90,88,87,86,85,84
};

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

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
int rev = 23; // Will allow matrix in reverse when place pointer is subtracted from.

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

    // 1,3,5 lifting, 2,4,6 walking
    pwm.setPWM(S1A, 0, top[rev-n]+198); // Reversed because lifting, same for 3 and 5. 
    pwm.setPWM(S1B, 0, 198+phi[rev-n]);
    pwm.setPWM(S1C, 0, 640-psi[rev-n]);
    pwm.setPWM(S2A, 0, mid[n]+198); 
    pwm.setPWM(S2B, 0, 198+sa_phi[n]);
    pwm.setPWM(S2C, 0, 640-sa_psi[n]);
    pwm.setPWM(S3A, 0, back[rev-n]+198);
    pwm.setPWM(S3B, 0, 198+phi[rev-n]);
    pwm.setPWM(S3C, 0, 640-psi[rev-n]);

    pwm.setPWM(S4A, 0, 442-back[n]); // 442- because mirroring...
    pwm.setPWM(S4B, 0, 442-phi[n]);
    pwm.setPWM(S4C, 0, psi[n]);
    pwm.setPWM(S5A, 0, 442-mid[rev-n]); // Jayce, 11/17, 19:32, questioning reversal for this one
                                        // No longer questioning because old code used lift...
    pwm.setPWM(S5B, 0, 442-sa_phi[rev-n]);
    pwm.setPWM(S5C, 0, sa_psi[rev-n]);
    pwm.setPWM(S6A, 0, 442-top[n]);
    S6B.write(180-sixphi[n]);
    S6C.write(sixpsi[n]);
    
    
    delay(100);
  }
  n = 0;
  for (n = 0; n <= 23; n ++) {  

    // 1,3,5 walking, 2,4,6 lifting
    pwm.setPWM(S1A, 0, top[n]+198);
    pwm.setPWM(S1B, 0, 198+phi[n]);
    pwm.setPWM(S1C, 0, 640-psi[n]);
    pwm.setPWM(S2A, 0, mid[rev-n]+198); 
    pwm.setPWM(S2B, 0, 198+sa_phi[rev-n]);
    pwm.setPWM(S2C, 0, 640-sa_psi[rev-n]);
    pwm.setPWM(S3A, 0, back[n]+198);
    pwm.setPWM(S3B, 0, 198+phi[n]);
    pwm.setPWM(S3C, 0, 640-psi[n]);

    pwm.setPWM(S4A, 0, 442-back[rev-n]);
    pwm.setPWM(S4B, 0, 442-phi[rev-n]);
    pwm.setPWM(S4C, 0, psi[rev-n]);
    pwm.setPWM(S5A, 0, 442-mid[n]);
    pwm.setPWM(S5B, 0, 442-sa_phi[n]);
    pwm.setPWM(S5C, 0, sa_psi[n]);
    pwm.setPWM(S6A, 0, 442-top[rev-n]);
    S6B.write(180-sixphi[rev-n]);
    S6C.write(sixpsi[rev-n]);
    
    delay(100);
  }
  n = 0; // REMEMBER TO UNCOMMENT THIS!!!!!!!
}
