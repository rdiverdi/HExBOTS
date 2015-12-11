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
int walk2[72] = {
159,142,350,
156,142,348,
153,143,347,
150,143,345,
146,143,344,
143,144,343,
140,144,342,
137,144,342,
133,144,341,
130,145,341,
127,145,340,
124,145,340,
120,145,340,
117,145,340,
114,145,341,
111,144,341,
107,144,342,
104,144,342,
101,144,343,
98,143,344,
94,143,345,
91,143,347,
88,142,348,
85,142,350
};

int lift1[72] = {
34,140,355,
38,149,345,
43,157,335,
47,166,327,
51,174,319,
56,182,312,
61,190,306,
65,198,300,
70,206,295,
75,213,291,
80,221,287,
85,228,285,
88,226,288,
88,215,299,
87,205,310,
87,194,321,
87,184,334,
87,173,347,
87,162,361,
87,151,377,
87,138,394,
87,125,415,
87,108,440,
87,85,479
};

int lift3[72] = {
157,85,479,
157,108,440,
157,125,415,
157,138,394,
157,151,377,
157,162,361,
157,173,347,
157,184,334,
157,194,321,
157,205,310,
156,215,299,
156,226,288,
159,228,285,
164,221,287,
169,213,291,
174,206,295,
179,198,300,
183,190,306,
188,182,312,
193,174,319,
197,166,327,
201,157,335,
206,149,345,
210,140,355
};

int walk1[72] = {
87,85,479,
85,92,464,
83,98,453,
82,103,443,
80,107,435,
78,110,427,
76,113,420,
74,116,414,
72,119,408,
70,121,403,
67,123,398,
65,125,393,
63,127,389,
61,129,385,
58,130,381,
56,132,377,
53,133,374,
51,134,370,
48,135,367,
45,137,365,
43,138,362,
40,138,359,
37,139,357,
34,140,355
};

int walk3[72] = {
210,140,355,
207,139,357,
204,138,359,
201,138,362,
199,137,365,
196,135,367,
193,134,370,
191,133,374,
188,132,377,
186,130,381,
183,129,385,
181,127,389,
179,125,393,
177,123,398,
174,121,403,
172,119,408,
170,116,414,
168,113,420,
166,110,427,
164,107,435,
162,103,443,
161,98,453,
159,92,464,
157,85,479
};

int lift2[72] = {
85,142,350,
87,151,336,
90,161,323,
92,171,311,
95,180,300,
97,190,289,
101,199,279,
104,209,269,
107,219,259,
111,230,250,
115,241,242,
120,253,234,
124,253,234,
129,241,242,
133,230,250,
137,219,259,
140,209,269,
143,199,279,
147,190,289,
149,180,300,
152,171,311,
154,161,323,
157,151,336,
159,142,350
};

int walk6[48] = {
-17,162,
-13,156,
-11,150,
-9,146,
-7,142,
-5,139,
-4,136,
-3,133,
-1,130,
-0,128,
1,125,
1,123,
2,121,
3,119,
4,118,
4,116,
5,114,
6,113,
6,112,
7,110,
7,109,
7,108,
8,107,
8,106
};

int lift6[48] = {
8,106,
12,101,
16,97,
20,93,
24,90,
27,86,
31,84,
34,81,
38,79,
42,77,
45,75,
48,74,
47,76,
42,80,
38,85,
33,91,
28,96,
23,102,
18,109,
13,116,
7,124,
1,133,
-6,145,
-17,162
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

void setup() {
  Serial.begin(9600);
  Serial.println("16 channel Servo test!");

  S6B.attach(9);
  S6C.attach(10);

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}


void Walk() {
  for (n = 0; n <= 23; n++) {
    pwm.setPWM(S1A, 0, 198+walk1[23*3-(n*3)]);
    pwm.setPWM(S1B, 0, 198+lift1[1+(n*3)]);
    pwm.setPWM(S1C, 0, lift1[2+(n*3)]);
    pwm.setPWM(S2A, 0, 198+walk2[(n*3)]);
    pwm.setPWM(S2B, 0, 198+walk2[1+(n*3)]);
    pwm.setPWM(S2C, 0, walk2[2+(n*3)]);
    pwm.setPWM(S3A, 0, 198+walk3[23*3-(n*3)]);
    pwm.setPWM(S3B, 0, 198+lift3[1+(n*3)]);
    pwm.setPWM(S3C, 0, lift3[2+(n*3)]);

    pwm.setPWM(S4A, 0, 442-walk3[(n*3)]);
    pwm.setPWM(S4B, 0, 442-walk3[1+(n*3)]);
    pwm.setPWM(S4C, 0, 640-walk3[2+(n*3)]);
    pwm.setPWM(S5A, 0 , 442-lift2[(n*3)]);
    pwm.setPWM(S5B, 0, 442-lift2[1+(n*3)]);
    pwm.setPWM(S5C, 0, 640-lift2[2+(n*3)]);
    pwm.setPWM(S6A, 0, 442-walk1[(n*3)]);
    S6B.write(90-walk6[(n*2)]);
    S6C.write(180-walk6[1+(n*2)]);
    delay(200);
  }
  n = 0;

  for (n = 0; n <= 23; n ++) {  
    pwm.setPWM(S1A, 0, 198+walk1[(n*3)]);
    pwm.setPWM(S1B, 0, 198+walk1[1+(n*3)]);
    pwm.setPWM(S1C, 0, walk1[2+(n*3)]);
    pwm.setPWM(S2A, 0, 198+lift2[(n*3)]);
    pwm.setPWM(S2B, 0, 198+lift2[1+(n*3)]);
    pwm.setPWM(S2C, 0, lift2[2+(n*3)]);
    pwm.setPWM(S3A, 0, 198+walk3[(n*3)]);
    pwm.setPWM(S3B, 0, 198+walk3[1+(n*3)]);
    pwm.setPWM(S3C, 0, walk3[2+(n*3)]);

    pwm.setPWM(S4A, 0, 442-walk3[23*3-(n*3)]);
    pwm.setPWM(S4B, 0, 442-lift3[1+(n*3)]);
    pwm.setPWM(S4C, 0, 640-lift3[2+(n*3)]);
    pwm.setPWM(S5A, 0 , 442-walk2[(n*3)]);
    pwm.setPWM(S5B, 0, 442-walk2[1+(n*3)]);
    pwm.setPWM(S5C, 0, 640-walk2[2+(n*3)]);
    pwm.setPWM(S6A, 0, 442-walk1[23*3-(n*3)]);
    S6B.write(90-lift6[(n*2)]);
    S6C.write(180-lift6[1+(n*2)]);
    
    delay(200);
  }
  n = 0;
}

void Turn(int angle) {
  for (n = 0; n <= 11; n++) {
    pwm.setPWM(S1A, 0, 198+walk1[23*3-(n*3)]);
    pwm.setPWM(S1B, 0, 198+lift1[1+(n*3)]);
    pwm.setPWM(S1C, 0, lift1[2+(n*3)]);
    pwm.setPWM(S2A, 0, 198+walk2[(n*3)]+angle);
    pwm.setPWM(S2B, 0, 198+walk2[1+(n*3)]);
    pwm.setPWM(S2C, 0, walk2[2+(n*3)]);
    pwm.setPWM(S3A, 0, 198+walk3[23*3-(n*3)]);
    pwm.setPWM(S3B, 0, 198+lift3[1+(n*3)]);
    pwm.setPWM(S3C, 0, lift3[2+(n*3)]);

    pwm.setPWM(S4A, 0, 442-walk3[(n*3)]+angle);
    pwm.setPWM(S4B, 0, 442-walk3[1+(n*3)]);
    pwm.setPWM(S4C, 0, 640-walk3[2+(n*3)]);
    pwm.setPWM(S5A, 0 , 442-lift2[(n*3)]);
    pwm.setPWM(S5B, 0, 442-lift2[1+(n*3)]);
    pwm.setPWM(S5C, 0, 640-lift2[2+(n*3)]);
    pwm.setPWM(S6A, 0, 442-walk1[(n*3)]+angle);
    S6B.write(90-walk6[(n*2)]);
    S6C.write(180-walk6[1+(n*2)]);
    delay(200);
  }
  for (n = 12; n <= 23; n++) {
    pwm.setPWM(S1A, 0, 198+walk1[23*3-(n*3)]-angle);
    pwm.setPWM(S1B, 0, 198+lift1[1+(n*3)]);
    pwm.setPWM(S1C, 0, lift1[2+(n*3)]);
    pwm.setPWM(S2A, 0, 198+walk2[(n*3)]);
    pwm.setPWM(S2B, 0, 198+walk2[1+(n*3)]);
    pwm.setPWM(S2C, 0, walk2[2+(n*3)]);
    pwm.setPWM(S3A, 0, 198+walk3[23*3-(n*3)]-angle);
    pwm.setPWM(S3B, 0, 198+lift3[1+(n*3)]);
    pwm.setPWM(S3C, 0, lift3[2+(n*3)]);

    pwm.setPWM(S4A, 0, 442-walk3[(n*3)]);
    pwm.setPWM(S4B, 0, 442-walk3[1+(n*3)]);
    pwm.setPWM(S4C, 0, 640-walk3[2+(n*3)]);
    pwm.setPWM(S5A, 0 , 442-lift2[(n*3)]-angle);
    pwm.setPWM(S5B, 0, 442-lift2[1+(n*3)]);
    pwm.setPWM(S5C, 0, 640-lift2[2+(n*3)]);
    pwm.setPWM(S6A, 0, 442-walk1[(n*3)]);
    S6B.write(90-walk6[(n*2)]);
    S6C.write(180-walk6[1+(n*2)]);
    delay(200);
  }
  n = 0;

//  pwm.setPWM(S1A, 0, 198+walk1[23*3-(n*3)]);
//  pwm.setPWM(S3A, 0, 198+walk3[23*3-(n*3)]);
//  pwm.setPWM(S5A, 0 , 442-lift2[(n*3)]);

  for (n = 0; n <= 11; n ++) {  
    pwm.setPWM(S1A, 0, 198+walk1[(n*3)]);
    pwm.setPWM(S1B, 0, 198+walk1[1+(n*3)]);
    pwm.setPWM(S1C, 0, walk1[2+(n*3)]);
    pwm.setPWM(S2A, 0, 198+lift2[(n*3)]+angle);
    pwm.setPWM(S2B, 0, 198+lift2[1+(n*3)]);
    pwm.setPWM(S2C, 0, lift2[2+(n*3)]);
    pwm.setPWM(S3A, 0, 198+walk3[(n*3)]);
    pwm.setPWM(S3B, 0, 198+walk3[1+(n*3)]);
    pwm.setPWM(S3C, 0, walk3[2+(n*3)]);

    pwm.setPWM(S4A, 0, 442-walk3[23*3-(n*3)]+angle);
    pwm.setPWM(S4B, 0, 442-lift3[1+(n*3)]);
    pwm.setPWM(S4C, 0, 640-lift3[2+(n*3)]);
    pwm.setPWM(S5A, 0 , 442-walk2[(n*3)]);
    pwm.setPWM(S5B, 0, 442-walk2[1+(n*3)]);
    pwm.setPWM(S5C, 0, 640-walk2[2+(n*3)]);
    pwm.setPWM(S6A, 0, 442-walk1[23*3-(n*3)]+angle);
    S6B.write(90-lift6[(n*2)]);
    S6C.write(180-lift6[1+(n*2)]);
    
    delay(200);
  }
  for (n = 12; n <= 23; n ++) {  
    pwm.setPWM(S1A, 0, 198+walk1[(n*3)]-angle);
    pwm.setPWM(S1B, 0, 198+walk1[1+(n*3)]);
    pwm.setPWM(S1C, 0, walk1[2+(n*3)]);
    pwm.setPWM(S2A, 0, 198+lift2[(n*3)]);
    pwm.setPWM(S2B, 0, 198+lift2[1+(n*3)]);
    pwm.setPWM(S2C, 0, lift2[2+(n*3)]);
    pwm.setPWM(S3A, 0, 198+walk3[(n*3)]-angle);
    pwm.setPWM(S3B, 0, 198+walk3[1+(n*3)]);
    pwm.setPWM(S3C, 0, walk3[2+(n*3)]);

    pwm.setPWM(S4A, 0, 442-walk3[23*3-(n*3)]);
    pwm.setPWM(S4B, 0, 442-lift3[1+(n*3)]);
    pwm.setPWM(S4C, 0, 640-lift3[2+(n*3)]);
    pwm.setPWM(S5A, 0 , 442-walk2[(n*3)]-angle);
    pwm.setPWM(S5B, 0, 442-walk2[1+(n*3)]);
    pwm.setPWM(S5C, 0, 640-walk2[2+(n*3)]);
    pwm.setPWM(S6A, 0, 442-walk1[23*3-(n*3)]);
    S6B.write(90-lift6[(n*2)]);
    S6C.write(180-lift6[1+(n*2)]);
    
    delay(200);
  }
  n = 0;
}

void loop() {
  // Each function is two steps, one of each set of legs
  Walk();
  Turn(33); // Positive should be left // 33 is 15 degrees in PWM
  Turn(-33); // Negative should be right
  
}
