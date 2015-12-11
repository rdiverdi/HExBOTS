#include <Wire.h>
#include <Servo.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

int n = 1;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
int walk2[72] = {
166,150,317,
162,151,316,
158,151,314,
155,151,313,
151,152,312,
147,152,311,
143,152,310,
140,152,309,
136,152,309,
132,152,308,
128,152,308,
124,152,308,
120,152,308,
116,152,308,
112,152,308,
108,152,309,
104,152,309,
101,152,310,
97,152,311,
93,152,312,
89,151,313,
86,151,314,
82,151,316,
78,150,317
};

int lift1[72] = {
53,154,296,
59,162,288,
66,170,280,
72,179,274,
79,187,267,
85,196,262,
92,205,257,
98,214,253,
105,222,249,
112,231,247,
118,240,245,
124,248,244,
126,246,248,
125,234,257,
123,223,267,
121,213,277,
120,202,288,
118,192,299,
117,182,311,
116,172,324,
115,162,337,
114,152,351,
113,141,366,
112,130,383
};

int lift3[72] = {
132,130,383,
131,141,366,
130,152,351,
129,162,337,
128,172,324,
127,182,311,
126,192,299,
124,202,288,
123,213,277,
121,223,267,
119,234,257,
118,246,248,
120,248,244,
126,240,245,
132,231,247,
139,222,249,
146,214,253,
152,205,257,
159,196,262,
165,187,267,
172,179,274,
178,170,280,
185,162,288,
191,154,296
};

int walk1[72] = {
128,138,360,
126,140,355,
125,142,349,
123,143,344,
122,145,339,
120,146,335,
118,147,330,
116,149,326,
114,150,322,
112,150,317,
110,151,314,
108,152,310,
106,152,306,
103,153,303,
101,153,299,
98,154,296,
95,154,293,
92,154,290,
89,154,287,
85,154,284,
82,154,282,
78,153,279,
74,153,277,
70,153,275
};

int walk3[72] = {
174,153,275,
170,153,277,
166,153,279,
162,154,282,
159,154,284,
155,154,287,
152,154,290,
149,154,293,
146,154,296,
143,153,299,
141,153,303,
138,152,306,
136,152,310,
134,151,314,
132,150,317,
130,150,322,
128,149,326,
126,147,330,
124,146,335,
122,145,339,
121,143,344,
119,142,349,
118,140,355,
116,138,360
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
7,108,
8,106,
9,103,
10,101,
10,99,
11,97,
12,95,
12,93,
13,91,
13,89,
13,87,
14,85,
14,84,
14,82,
14,81,
14,79,
14,78,
14,76,
14,75,
14,74,
14,73,
14,72,
14,71,
14,70
};

int lift6[48] = {
14,79,
18,75,
22,72,
26,69,
30,66,
34,64,
38,61,
42,59,
46,58,
50,57,
54,56,
57,55,
56,57,
51,62,
46,66,
41,71,
37,76,
32,81,
27,86,
23,92,
18,98,
14,104,
9,111,
3,119
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

void setup() {
  Serial.begin(9600);
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
  for (n = 0; n <= 23; n++) {
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
//  for (n = 12; n <= 23; n++) {
//    pwm.setPWM(S1A, 0, 198+walk1[23*3-(n*3)]-angle);
//    pwm.setPWM(S1B, 0, 198+lift1[1+(n*3)]);
//    pwm.setPWM(S1C, 0, lift1[2+(n*3)]);
//    pwm.setPWM(S2A, 0, 198+walk2[(n*3)]);
//    pwm.setPWM(S2B, 0, 198+walk2[1+(n*3)]);
//    pwm.setPWM(S2C, 0, walk2[2+(n*3)]);
//    pwm.setPWM(S3A, 0, 198+walk3[23*3-(n*3)]-angle);
//    pwm.setPWM(S3B, 0, 198+lift3[1+(n*3)]);
//    pwm.setPWM(S3C, 0, lift3[2+(n*3)]);
//
//    pwm.setPWM(S4A, 0, 442-walk3[(n*3)]);
//    pwm.setPWM(S4B, 0, 442-walk3[1+(n*3)]);
//    pwm.setPWM(S4C, 0, 640-walk3[2+(n*3)]);
//    pwm.setPWM(S5A, 0 , 442-lift2[(n*3)]-angle);
//    pwm.setPWM(S5B, 0, 442-lift2[1+(n*3)]);
//    pwm.setPWM(S5C, 0, 640-lift2[2+(n*3)]);
//    pwm.setPWM(S6A, 0, 442-walk1[(n*3)]);
//    S6B.write(90-walk6[(n*2)]);
//    S6C.write(180-walk6[1+(n*2)]);
//    delay(200);
//  }
  n = 0;

//  pwm.setPWM(S1A, 0, 198+walk1[23*3-(n*3)]);
//  pwm.setPWM(S3A, 0, 198+walk3[23*3-(n*3)]);
//  pwm.setPWM(S5A, 0 , 442-lift2[(n*3)]);

  for (n = 0; n <= 23; n ++) {  
    pwm.setPWM(S1A, 0, 198+walk1[(n*3)]+angle);
    pwm.setPWM(S1B, 0, 198+walk1[1+(n*3)]);
    pwm.setPWM(S1C, 0, walk1[2+(n*3)]);
    pwm.setPWM(S2A, 0, 198+lift2[(n*3)]);
    pwm.setPWM(S2B, 0, 198+lift2[1+(n*3)]);
    pwm.setPWM(S2C, 0, lift2[2+(n*3)]);
    pwm.setPWM(S3A, 0, 198+walk3[(n*3)]+angle);
    pwm.setPWM(S3B, 0, 198+walk3[1+(n*3)]);
    pwm.setPWM(S3C, 0, walk3[2+(n*3)]);

    pwm.setPWM(S4A, 0, 442-walk3[23*3-(n*3)]);
    pwm.setPWM(S4B, 0, 442-lift3[1+(n*3)]);
    pwm.setPWM(S4C, 0, 640-lift3[2+(n*3)]);
    pwm.setPWM(S5A, 0 , 442-walk2[(n*3)]+angle);
    pwm.setPWM(S5B, 0, 442-walk2[1+(n*3)]);
    pwm.setPWM(S5C, 0, 640-walk2[2+(n*3)]);
    pwm.setPWM(S6A, 0, 442-walk1[23*3-(n*3)]);
    S6B.write(90-lift6[(n*2)]);
    S6C.write(180-lift6[1+(n*2)]);
    
    delay(200);
  }
//  for (n = 12; n <= 23; n ++) {  
//    pwm.setPWM(S1A, 0, 198+walk1[(n*3)]-angle);
//    pwm.setPWM(S1B, 0, 198+walk1[1+(n*3)]);
//    pwm.setPWM(S1C, 0, walk1[2+(n*3)]);
//    pwm.setPWM(S2A, 0, 198+lift2[(n*3)]);
//    pwm.setPWM(S2B, 0, 198+lift2[1+(n*3)]);
//    pwm.setPWM(S2C, 0, lift2[2+(n*3)]);
//    pwm.setPWM(S3A, 0, 198+walk3[(n*3)]-angle);
//    pwm.setPWM(S3B, 0, 198+walk3[1+(n*3)]);
//    pwm.setPWM(S3C, 0, walk3[2+(n*3)]);
//
//    pwm.setPWM(S4A, 0, 442-walk3[23*3-(n*3)]);
//    pwm.setPWM(S4B, 0, 442-lift3[1+(n*3)]);
//    pwm.setPWM(S4C, 0, 640-lift3[2+(n*3)]);
//    pwm.setPWM(S5A, 0 , 442-walk2[(n*3)]-angle);
//    pwm.setPWM(S5B, 0, 442-walk2[1+(n*3)]);
//    pwm.setPWM(S5C, 0, 640-walk2[2+(n*3)]);
//    pwm.setPWM(S6A, 0, 442-walk1[23*3-(n*3)]);
//    S6B.write(90-lift6[(n*2)]);
//    S6C.write(180-lift6[1+(n*2)]);
//    
//    delay(200);
//  }
  n = 0;
}

void loop() {
  // Each function is two steps, one of each set of legs
  Walk();
  Turn(33); // Positive should be left // 33 is 15 degrees in PWM
//  Turn(-33); // Negative should be right
  Turn(33);
  Turn(33);
  Turn(33);
  Turn(33);
  
}

