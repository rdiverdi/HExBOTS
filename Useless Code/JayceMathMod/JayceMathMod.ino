/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
#include <math.h>
 
Servo myservoA;
Servo myservoB;
Servo myservoC;// create servo object to control a servo 
                // twelve servo objects can be created on most boards
 
float psi = 0;    // variable to store the servo position 
float phi = 0;
float tha = 0;

float L;
float d;
float gamma;
float L1 = 5.5;
float L2 = 4;

// These are the final positions that we want the thing to be at
int xpos = 3; // This should actually be zero
int ypos = 5;
int zpos = 2; // This should definitely be zero
 
void setup() 
{ 
  myservoA.attach(9);
  myservoB.attach(10);
  myservoC.attach(11);// attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
  Serial.print("hi there");
} 
 
void loop() 
{ 
  tha = atan2 (ypos,xpos);
  L = sqrt(xpos*xpos + ypos*ypos);
  //Serial.print("L "); Serial.println(L);
  d = sqrt(xpos*xpos + ypos*ypos +zpos*zpos);
  //Serial.print("d "); Serial.println(d);
  gamma = atan2(zpos,L);
  //Serial.print("gamma "); Serial.println(gamma);
  float math = (d*d + L1*L1 + L2*L2)/(2*L1*L2);
  //Serial.print("math "); Serial.println(math);
  psi = 3.14-acos((-d*d + L1*L1 + L2*L2)/(2*L1*L2));
  phi = asin(L2*sin(3.14-psi)/d)-gamma;
  
  Serial.print(psi*180/3.14); Serial.print(", ");
  Serial.print(phi*180/3.14); Serial.print(", ");
  Serial.println(tha*180/3.14);
  
  myservoA.write(psi*180/3.14-30);
  myservoB.write(phi*180/3.14);
  myservoC.write(tha*180/3.14);

  /// Return Functions
  delay(500);
  myservoA.write(0);
  myservoB.write(0);
  myservoC.write(0);
  delay(500);
} 

