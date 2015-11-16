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
    159,225,302,
    156,225,301,
    153,226,299,
    150,227,298,
    146,228,297,
    143,228,296,
    140,229,295,
    137,229,294,
    133,229,293,
    130,230,293,
    127,230,293,
    124,230,293,
    120,230,293,
    117,230,293,
    114,230,293,
    111,229,293,
    107,229,294,
    104,229,295,
    101,228,296,
    98,228,297,
    94,227,298,
    91,226,299,
    88,225,301,
    85,225,302
};

int lift1[72] = {
    34,222,307,
    38,226,303,
    43,230,299,
    47,234,295,
    51,238,292,
    56,241,289,
    61,244,287,
    65,248,284,
    70,251,283,
    75,254,281,
    80,256,280,
    85,259,279,
    88,256,283,
    88,249,292,
    87,242,300,
    87,235,309,
    87,228,318,
    87,221,328,
    87,213,338,
    87,206,348,
    87,199,359,
    87,191,371,
    87,182,384,
    87,174,398
};

int lift3[72] = {
    157,174,398,
    157,182,384,
    157,191,371,
    157,199,359,
    157,206,348,
    157,213,338,
    157,221,328,
    157,228,318,
    157,235,309,
    157,242,300,
    156,249,292,
    156,256,283,
    159,259,279,
    164,256,280,
    169,254,281,
    174,251,283,
    179,248,284,
    183,244,287,
    188,241,289,
    193,238,292,
    197,234,295,
    201,230,299,
    206,226,303,
    210,222,307
};

int walk1[72] = {
    87,174,398,
    85,177,391,
    83,180,385,
    82,183,379,
    80,186,374,
    78,189,369,
    76,192,364,
    74,194,359,
    72,197,355,
    70,199,350,
    67,201,346,
    65,203,342,
    63,205,338,
    61,207,335,
    58,209,331,
    56,211,328,
    53,213,325,
    51,214,322,
    48,216,319,
    45,217,316,
    43,218,314,
    40,220,311,
    37,221,309,
    34,222,307
};

int walk3[72] = {
    210,222,307,
    207,221,309,
    204,220,311,
    201,218,314,
    199,217,316,
    196,216,319,
    193,214,322,
    191,213,325,
    188,211,328,
    186,209,331,
    183,207,335,
    181,205,338,
    179,203,342,
    177,201,346,
    174,199,350,
    172,197,355,
    170,194,359,
    168,192,364,
    166,189,369,
    164,186,374,
    162,183,379,
    161,180,385,
    159,177,391,
    157,174,398
};

int lift2[72] = {
    85,225,302,
    87,231,294,
    90,237,286,
    92,243,279,
    95,249,272,
    97,255,265,
    101,262,258,
    104,268,251,
    107,275,245,
    111,281,239,
    115,288,233,
    120,295,227,
    124,295,227,
    129,288,233,
    133,281,239,
    137,275,245,
    140,268,251,
    143,262,258,
    147,255,265,
    149,249,272,
    152,243,279,
    154,237,286,
    157,231,294,
    159,225,302
};

int walk6[48] = {
    23,125,
    25,122,
    27,120,
    28,117,
    29,115,
    31,112,
    32,110,
    33,108,
    34,106,
    35,104,
    36,102,
    37,100,
    38,98,
    39,97,
    40,95,
    40,94,
    41,92,
    42,91,
    43,90,
    43,88,
    44,87,
    44,86,
    45,85,
    45,84
};

int lift6[48] = {
    45,84,
    47,82,
    49,80,
    51,79,
    53,77,
    54,76,
    56,75,
    57,74,
    58,73,
    60,72,
    61,72,
    62,72,
    61,73,
    58,77,
    54,81,
    51,85,
    48,89,
    45,94,
    42,98,
    38,103,
    35,108,
    31,113,
    27,119,
    23,125
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

  pwm.begin();
  
  pwm.setPWMFreq(60);  // Analog servos run at ~60 Hz updates

}


void loop() {
  for (n = 0; n <= 23; n++) {
    pwm.setPWM(S1A, 0, walk1[23*3-(n*3)]+188);
    pwm.setPWM(S1B, 0, lift1[1+(n*3)]);
    pwm.setPWM(S1C, 0, lift1[2+(n*3)]);
    pwm.setPWM(S2A, 0, walk2[(n*3)]+94);
    pwm.setPWM(S2B, 0, walk2[1+(n*3)]);
    pwm.setPWM(S2C, 0, walk2[2+(n*3)]);
    pwm.setPWM(S3A, 0, walk3[23*3-(n*3)]);
    pwm.setPWM(S3B, 0, lift3[1+(n*3)]);
    pwm.setPWM(S3C, 0, lift3[2+(n*3)]);

    pwm.setPWM(S4A, 0, walk3[23*3-(n*3)]);
    pwm.setPWM(S4B, 0, walk3[1+(n*3)]);
    pwm.setPWM(S4C, 0, walk3[2+(n*3)]);
    pwm.setPWM(S5A, 0, lift2[23*3-(n*3)]+94);
    pwm.setPWM(S5B, 0, lift2[1+(n*3)]);
    pwm.setPWM(S5C, 0, lift2[2+(n*3)]);
    pwm.setPWM(S6A, 0, walk1[23*3-(n*3)]);
//    S6B.write(walk6[(n*2)];
//    S6C.write(walk6[1+(n*2)];

    
    
    delay(100);
  }
  n = 0;
  for (n = 0; n <= 23; n += 1) {  
    pwm.setPWM(S1A, 0, walk1[(n*3)]+188);
    pwm.setPWM(S1B, 0, walk1[1+(n*3)]);
    pwm.setPWM(S1C, 0, walk1[2+(n*3)]);
    pwm.setPWM(S2A, 0, lift2[(n*3)]+94);
    pwm.setPWM(S2B, 0, lift2[1+(n*3)]);
    pwm.setPWM(S2C, 0, lift2[2+(n*3)]);
    pwm.setPWM(S3A, 0, walk3[(n*3)]);
    pwm.setPWM(S3B, 0, walk3[1+(n*3)]);
    pwm.setPWM(S3C, 0, walk3[2+(n*3)]);

    pwm.setPWM(S4A, 0, walk1[(n*3)]+188);
    pwm.setPWM(S4B, 0, lift3[1+(n*3)]);
    pwm.setPWM(S4C, 0, lift3[2+(n*3)]);
    pwm.setPWM(S5A, 0, walk2[23*3-(n*3)]+94);
    pwm.setPWM(S5B, 0, walk2[1+(n*3)]);
    pwm.setPWM(S5C, 0, walk2[2+(n*3)]);
    pwm.setPWM(S6A, 0, walk3[(n*3)]);
//    S6B.write(lift6[(n*2)];
//    S6C.write(lift6[1+(n*2)];
    
    delay(100);
  }
  n = 0;
}
