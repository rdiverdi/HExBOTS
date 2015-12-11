
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>


/*
 * rosserial Publisher Example
 * Prints "hello world!"
 */

#include <ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Int8MultiArray.h>
#include <Servo.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

byte S1A = 0;
byte S1B = 1;
byte S1C = 2;
byte S2A = 3;
byte S2B = 4;
byte S2C = 5;
byte S3A = 6;
byte S3B = 7;
byte S3C = 8;
byte S4A = 9;
byte S4B = 10;
byte S4C = 11;
byte S5A = 12;
byte S5B = 13;
byte S5C = 14;
byte S6A = 15;
Servo S6B;
Servo S6C;

int8_t* a;

// our servo # counter
uint8_t servonum = 0;
//int pulselen;

///////// Not copied

ros::NodeHandle  nh;

// Do we need this? v
//char hello[13] = "hello world!";

/////////

std_msgs::String str_msg;
ros::Publisher err("errors", &str_msg);

void angles(const std_msgs::Int8MultiArray& msg) {
    str_msg.data = "recieved";
    err.publish( &str_msg );
    nh.spinOnce();
    a = msg.data;
    pwm.setPWM(S1A, 0, 320+(2.2*a[0]));
    pwm.setPWM(S1B, 0, 320+(2.2*a[1]));
    pwm.setPWM(S1C, 0, 122+(2.2*a[2]));
    
    pwm.setPWM(S2A, 0, 320+(2.2*a[3]));
    pwm.setPWM(S2B, 0, 320+(2.2*a[4]));
    pwm.setPWM(S2C, 0, 122+(2.2*a[5]));
    
    pwm.setPWM(S3A, 0, 320+(2.2*a[6]));
    pwm.setPWM(S3B, 0, 320+(2.2*a[7]));
    pwm.setPWM(S3C, 0, 122+(2.2*a[8]));

    pwm.setPWM(S4A, 0, 320-(2.2*a[9]));
    pwm.setPWM(S4B, 0, 320-(2.2*a[10]));
    pwm.setPWM(S4C, 0, 518-(2.2*a[11]));
    
    pwm.setPWM(S5A, 0, 320-(2.2*a[12]));
    pwm.setPWM(S5B, 0, 320-(2.2*a[13]));
    pwm.setPWM(S5C, 0, 518-(2.2*a[14]));
    
    pwm.setPWM(S6A, 0, 320-(2.2*a[15]));
    S6B.write(90-a[16]);
    S6C.write(180-a[17]);
    
}

ros::Subscriber<std_msgs::Int8MultiArray> sub("data_array", &angles);

void setup()
{
  S6B.attach(9);
  S6C.attach(10);

  pwm.begin();
  
  pwm.setPWMFreq(60);
  
  nh.initNode();
  nh.advertise(err); // Is this still "chatter"?
  nh.subscribe(sub);

  str_msg.data = "working";
}

void loop()
{
  err.publish( &str_msg );
  nh.spinOnce();
  delay(1000);
}
