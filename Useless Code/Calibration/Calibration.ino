/* Sweep
 by BARRAGAN <http://barraganstudio.com>
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/

#include <Servo.h>

Servo myservo1A;
Servo myservo1B;
Servo myservo1C;
Servo myservo2A;
Servo myservo2B;
Servo myservo2C;

//int pos = 0;    // variable to store the servo position

void setup() {
  myservo1A.attach(3);
  myservo1B.attach(5);
  myservo1C.attach(6);
  myservo2A.attach(9);
  myservo2B.attach(10);
  myservo2C.attach(11);// attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
}

void loop() {
//  for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
//  for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
//    myservo.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(15);                       // waits 15ms for the servo to reach the position
//  }
  myservo1A.write(45);
  myservo1B.write(90);
  myservo1C.write(90);
  myservo2A.write(90);
  myservo2B.write(90);
  myservo2C.write(90);
}

