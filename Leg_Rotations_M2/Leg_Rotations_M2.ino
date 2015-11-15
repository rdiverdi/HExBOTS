#include <Servo.h>
#include <math.h>

Servo myservo1A;
Servo myservo1B;
Servo myservo1C;
Servo myservo2A;
Servo myservo2B;
Servo myservo2C;


float walk2[72] = {
   20.9735,   50.4970,   74.6903,
   19.2900,   51.0839,   73.5849,
   17.5713,   51.6193,   72.5765,
   15.8192,   52.1027,   71.6658,
   14.0362,   52.5337,   70.8536,
   12.2251,   52.9120,   70.1407,
   10.3889,   53.2372,   69.5280,
    8.5308,   53.5088,   69.0161,
    6.6544,   53.7265,   68.6057,
    4.7636,   53.8901,   68.2973,
    2.8624,   53.9992,   68.0915,
    0.9548,   54.0539,   67.9886,
   -0.9548,   54.0539,   67.9886,
   -2.8624,   53.9992,   68.0915,
   -4.7636,   53.8901,   68.2973,
   -6.6544,   53.7265,   68.6057,
   -8.5308,   53.5088,   69.0161,
  -10.3889,   53.2372,   69.5280,
  -12.2251,   52.9120,   70.1407,
  -14.0362,   52.5337,   70.8536,
  -15.8192,   52.1027,   71.6658,
  -17.5713,   51.6193,   72.5765,
  -19.2900,   51.0839,   73.5849,
  -20.9735,   50.4970,   74.6903
};

float lift1[72] = {
  -53.3456,   53.7265,   68.6057,
  -51.2292,   55.9655,   66.2237,
  -49.0145,   58.1718,   64.0088,
  -46.7014,   60.3422,   61.9647,
  -44.2914,   62.4712,   60.0965,
  -41.7871,   64.5511,   58.4098,
  -39.1932,   66.5721,   56.9110,
  -36.5159,   68.5221,   55.6065,
  -33.7633,   70.3870,   54.5029,
  -30.9454,   72.1513,   53.6065,
  -28.0739,   73.7981,   52.9225,
  -25.1621,   75.3104,   52.4557,
  -23.3508,   74.0259,   54.1817,
  -22.7093,   70.1899,   57.9978,
  -22.1250,   66.5015,   61.9020,
  -21.5906,   62.9278,   65.9018,
  -21.1001,   59.4403,   70.0067,
  -20.6482,   56.0129,   74.2284,
  -20.2308,   52.6217,   78.5812,
  -19.8440,   49.2433,   83.0828,
  -19.4846,   45.8543,   87.7552,
  -19.1498,   42.4298,   92.6261,
  -18.8373,   38.9418,   97.7315,
  -18.5448,   35.3571,  103.1187
};

float lift3[72] = {
   18.5448,   35.3571,  103.1187,
   18.8373,   38.9418,   97.7315,
   19.1498,   42.4298,   92.6261,
   19.4846,   45.8543,   87.7552,
   19.8440,   49.2433,   83.0828,
   20.2308,   52.6217,   78.5812,
   20.6482,   56.0129,   74.2284,
   21.1001,   59.4403,   70.0067,
   21.5906,   62.9278,   65.9018,
   22.1250,   66.5015,   61.9020,
   22.7093,   70.1899,   57.9978,
   23.3508,   74.0259,   54.1817,
   25.1621,   75.3104,   52.4557,
   28.0739,   73.7981,   52.9225,
   30.9454,   72.1513,   53.6065,
   33.7633,   70.3870,   54.5029,
   36.5159,   68.5221,   55.6065,
   39.1932,   66.5721,   56.9110,
   41.7871,   64.5511,   58.4098,
   44.2914,   62.4712,   60.0965,
   46.7014,   60.3422,   61.9647,
   49.0145,   58.1718,   64.0088,
   51.2292,   55.9655,   66.2237,
   53.3456,   53.7265,   68.6057
};

float walk1[72] = {
  -18.5448,   35.3571,  103.1187,
  -19.6355,   36.7782,  100.4582,
  -20.7626,   38.1291,   97.9275,
  -21.9272,   39.4142,   95.5184,
  -23.1301,   40.6372,   93.2246,
  -24.3721,   41.8009,   91.0407,
  -25.6539,   42.9077,   88.9627,
  -26.9761,   43.9594,   86.9874,
  -28.3392,   44.9574,   85.1121,
  -29.7436,   45.9027,   83.3352,
  -31.1892,   46.7961,   81.6551,
  -32.6761,   47.6382,   80.0711,
  -34.2040,   48.4293,   78.5827,
  -35.7723,   49.1695,   77.1896,
  -37.3801,   49.8588,   75.8920,
  -39.0265,   50.4970,   74.6903,
  -40.7100,   51.0839,   73.5849,
  -42.4287,   51.6193,   72.5765,
  -44.1808,   52.1027,   71.6658,
  -45.9638,   52.5337,   70.8536,
  -47.7749,   52.9120,   70.1407,
  -49.6111,   53.2372,   69.5280,
  -51.4692,   53.5088,   69.0161,
  -53.3456,   53.7265,   68.6057
};

float walk3[72] = {
   53.3456,   53.7265,   68.6057,
   51.4692,   53.5088,   69.0161,
   49.6111,   53.2372,   69.5280,
   47.7749,   52.9120,   70.1407,
   45.9638,   52.5337,   70.8536,
   44.1808,   52.1027,   71.6658,
   42.4287,   51.6193,   72.5765,
   40.7100,   51.0839,   73.5849,
   39.0265,   50.4970,   74.6903,
   37.3801,   49.8588,   75.8920,
   35.7723,   49.1695,   77.1896,
   34.2040,   48.4293,   78.5827,
   32.6761,   47.6382,   80.0711,
   31.1892,   46.7961,   81.6551,
   29.7436,   45.9027,   83.3352,
   28.3392,   44.9574,   85.1121,
   26.9761,   43.9594,   86.9874,
   25.6539,   42.9077,   88.9627,
   24.3721,   41.8009,   91.0407,
   23.1301,   40.6372,   93.2246,
   21.9272,   39.4142,   95.5184,
   20.7626,   38.1291,   97.9275,
   19.6355,   36.7782,  100.4582, 
   18.5448,   35.3571,  103.1187
};

float lift2[72] = {
  -20.9735,   50.4970,   74.6903,
  -19.7989,   53.4551,   70.8502,
  -18.5360,   56.4274,   67.1421,
  -17.1759,   59.4280,   63.5591,
  -15.7086,   62.4712,   60.0965,
  -14.1232,   65.5712,   56.7518,
  -12.4074,   68.7426,   53.5245,
  -10.5481,   71.9997,   50.4165,
   -8.5308,   75.3565,   47.4315,
   -6.3402,   78.8256,   44.5758,
   -3.9603,   82.4173,   41.8584,
   -1.3748,   86.1368,   39.2908,
    1.3748,   86.1368,   39.2908,
    3.9603,   82.4173,   41.8584,
    6.3402,   78.8256,   44.5758,
    8.5308,   75.3565,   47.4315,
   10.5481,   71.9997,   50.4165,
   12.4074,   68.7426,   53.5245,
   14.1232,   65.5712,   56.7518,
   15.7086,   62.4712,   60.0965,
   17.1759,   59.4280,   63.5591,
   18.5360,   56.4274,   67.1421,
   19.7989,   53.4551,   70.8502,
   20.9735,   50.4970,   74.6903
};

// These are just for incrementationing
int n = 1;
int j = 1;

void setup()
{
  myservo1A.attach(3);
  myservo1B.attach(5);
  myservo1C.attach(6);
  myservo2A.attach(9);
  myservo2B.attach(10);
  myservo2C.attach(11);// attaches the servo on pin 9 to the servo object
  Serial.begin(9600);
  //  Serial.print("hi there");
}

void loop() {
//  myservo2B.write(48);
//  myservo1A.write(0);
//  myservo1B.write(48);
//  myservo1C.write(45);
  for (n = 0; n <= 23; n += 1) {
    myservo1A.write(lift1[(n*3)]+90);
    myservo1B.write(lift1[1+(n*3)]);
    myservo1C.write(lift1[2+(n*3)]);
    myservo2A.write(walk2[(n*3)]+90);
    myservo2B.write(walk2[1+(n*3)]);
    myservo2C.write(walk2[2+(n*3)]);
    Serial.print("walking");
    Serial.println(walk1[(n*3)]);
    delay(100);
  }
  n = 0;
  /// Return Functions
  for (j = 0; j<= 23; j += 1) {
    myservo1A.write(walk1[(j*3)]+90);
    myservo1B.write(walk1[1+(j*3)]);
    myservo1C.write(walk1[2+(j*3)]);
    myservo2A.write(lift2[(j*3)]+90);
    myservo2B.write(lift2[1+(j*3)]);
    myservo2C.write(lift2[2+(j*3)]);
    Serial.print("lifting");
    Serial.println(lift2[1+(j*3)]);
    delay(100);
  }
  j = 0;
}

