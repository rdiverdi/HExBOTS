#include <Wire.h>

//Stuff for Serial Comms:
char current_line[50]; // allocate some space for the string
int angles[18];

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

void setup() {
  Serial.begin(9600);
  Serial.println("started");

  S6B.attach(9);
  S6C.attach(10);

  pwm.begin();
  
  pwm.setPWMFreq(60); 
}

void loop() {
  read_line(current_line);
//  for (int i=0; i<18; i++){
    pwm.setPWM(S1A, 0, 320+(2.2*angles[0]));
    pwm.setPWM(S1B, 0, 320+(2.2*angles[1]));
    pwm.setPWM(S1C, 0, 122+(2.2*angles[2]));
    
    pwm.setPWM(S2A, 0, 320+(2.2*angles[3]));
    pwm.setPWM(S2B, 0, 320+(2.2*angles[4]));
    pwm.setPWM(S2C, 0, 122+(2.2*angles[5));
    
    pwm.setPWM(S3A, 0, 320+(2.2*angles[6]));
    pwm.setPWM(S3B, 0, 320+(2.2*angles[7]));
    pwm.setPWM(S3C, 0, 122+(2.2*angles[8]));

    pwm.setPWM(S4A, 0, 320-(2.2*angles[9]));
    pwm.setPWM(S4B, 0, 320-(2.2*angles[10]));
    pwm.setPWM(S4C, 0, 518-(2.2*angles[11]));
    
    pwm.setPWM(S5A, 0, 320-(2.2*angles[12]));
    pwm.setPWM(S5B, 0, 320-(2.2*angles[13]));
    pwm.setPWM(S5C, 0, 518-(2.2*angles[14]));
    
    pwm.setPWM(S6A, 0, 320-(2.2*angles[15]));
    S6B.write(90-angles[16]);
    S6C.write(180-angles[17]);
//  }

}
