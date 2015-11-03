/* Sweep
 by BARRAGAN <http://barraganstudio.com> 
 This example code is in the public domain.

 modified 8 Nov 2013
 by Scott Fitzgerald
 http://www.arduino.cc/en/Tutorial/Sweep
*/ 

#include <Servo.h> 
#include <math.h>
 
Servo myservo1A;
Servo myservo1B;
Servo myservo1C;
Servo myservo2A;
Servo myservo2B;
Servo myservo2C;
 
//float psi1 = 0;    
//float phi1 = 0;
//float tha1 = 0;
//
//float L;
//float d;
//float gamma;
//float L1 = 5.5;
//float L2 = 4;

// These are the final positions that we want the thing to be at
// These don't matter
//int xpos = 3; // This should actually be zero
//int ypos = 5;
//int zpos = 2; // This should definitely be zero

float walk2[141] = {
   29.8989,   52.5099,   44.0474,
   28.8108,   52.5991,   43.4643,
   27.6995,   52.6796,   42.9028,
   26.5651,   52.7515,   42.3634,
   25.4077,   52.8153,   41.8467,
   24.2277,   52.8714,   41.3530,
   23.0255,   52.9203,   40.8828,
   21.8014,   52.9624,   40.4365,
   20.5560,   52.9983,   40.0146,
   19.2900,   53.0284,   39.6176,
   18.0042,   53.0533,   39.2459,
   16.6992,   53.0735,   38.8998,
   15.3763,   53.0896,   38.5799,
   14.0362,   53.1021,   38.2863,
   12.6804,   53.1115,   38.0196,
   11.3099,   53.1184,   37.7800,
    9.9262,   53.1232,   37.5679,
    8.5308,   53.1263,   37.3835,
    7.1250,   53.1283,   37.2270,
    5.7106,   53.1293,   37.0987,
    4.2892,   53.1299,   36.9987,
    2.8624,   53.1301,   36.9272,
    1.4321,   53.1301,   36.8842,
   -0.0000,   53.1301,   36.8699,
   -1.4321,   53.1301,   36.8842,
   -2.8624,   53.1301,   36.9272,
   -4.2892,   53.1299,   36.9987,
   -5.7106,   53.1293,   37.0987,
   -7.1250,   53.1283,   37.2270,
   -8.5308,   53.1263,   37.3835,
   -9.9262,   53.1232,   37.5679,
  -11.3099,   53.1184,   37.7800,
  -12.6804,   53.1115,   38.0196,
  -14.0362,   53.1021,   38.2863,
  -15.3763,   53.0896,   38.5799,
  -16.6992,   53.0735,   38.8998,
  -18.0042,   53.0533,   39.2459,
  -19.2900,   53.0284,   39.6176,
  -20.5560,   52.9983,   40.0146,
  -21.8014,   52.9624,   40.4365,
  -23.0255,   52.9203,   40.8828,
  -24.2277,   52.8714,   41.3530,
  -25.4077,   52.8153,   41.8467,
  -26.5651,   52.7515,   42.3634,
  -27.6995,   52.6796,   42.9028,
  -28.8108,   52.5991,   43.4643,
  -29.8989,   52.5099,   44.0474
};

float walk1[141] = {
   -7.0425,   45.0000,   69.8914,
   -7.5686,   45.4047,   68.8003,
   -8.1076,   45.7989,   67.7245,
   -8.6598,   46.1825,   66.6638,
   -9.2257,   46.5556,   65.6183,
   -9.8056,   46.9182,   64.5878,
  -10.3999,   47.2702,   63.5723,
  -11.0091,   47.6117,   62.5718,
  -11.6335,   47.9425,   61.5865,
  -12.2737,   48.2627,   60.6162,
  -12.9300,   48.5722,   59.6612,
  -13.6028,   48.8710,   58.7214,
  -14.2927,   49.1591,   57.7970,
  -15.0000,   49.4364,   56.8882,
  -15.7252,   49.7029,   55.9951,
  -16.4688,   49.9586,   55.1179,
  -17.2312,   50.2034,   54.2567,
  -18.0128,   50.4374,   53.4119,
  -18.8141,   50.6605,   52.5836,
  -19.6355,   50.8727,   51.7721,
  -20.4774,   51.0741,   50.9777,
  -21.3402,   51.2647,   50.2007,
  -22.2243,   51.4445,   49.4414,
  -23.1301,   51.6137,   48.7001,
  -24.0579,   51.7723,   47.9772,
  -25.0080,   51.9204,   47.2731,
  -25.9807,   52.0582,   46.5881,
  -26.9761,   52.1858,   45.9226,
  -27.9946,   52.3035,   45.2770,
  -29.0362,   52.4114,   44.6518,
  -30.1011,   52.5099,   44.0474,
  -31.1892,   52.5991,   43.4643,
  -32.3005,   52.6796,   42.9028,
  -33.4349,   52.7515,   42.3634,
  -34.5923,   52.8153,   41.8467,
  -35.7723,   52.8714,   41.3530,
  -36.9745,   52.9203,   40.8828,
  -38.1986,   52.9624,   40.4365,
  -39.4440,   52.9983,   40.0146,
  -40.7100,   53.0284,   39.6176,
  -41.9958,   53.0533,   39.2459,
  -43.3008,   53.0735,   38.8998,
  -44.6237,   53.0896,   38.5799,
  -45.9638,   53.1021,   38.2863,
  -47.3196,   53.1115,   38.0196,
  -48.6901,   53.1184,   37.7800,
  -50.0738,   53.1232,   37.5679
};

float lift1[141] = {
  -50.0738,   53.1232,   37.5679,
  -48.3191,   53.9685,   36.1489,
  -46.4665,   54.8221,   34.7807,
  -44.5115,   55.6878,   33.4662,
  -42.4504,   56.5696,   32.2092,
  -40.2802,   57.4720,   31.0133,
  -37.9986,   58.3998,   29.8829,
  -35.6047,   59.3576,   28.8223,
  -33.0989,   60.3501,   27.8365,
  -30.4835,   61.3813,   26.9304,
  -27.7626,   62.4543,   26.1092,
  -24.9429,   63.5707,   25.3782,
  -22.0330,   64.7299,   24.7425,
  -19.0445,   65.9290,   24.2073,
  -15.9908,   67.1618,   23.7769,
  -12.8876,   68.4192,   23.4555,
   -9.7523,   69.6885,   23.2462,
   -6.6033,   70.9545,   23.1514,
   -3.4595,   72.2000,   23.1723,
   -0.3398,   73.4067,   23.3089,
    2.7380,   74.5568,   23.5602,
    5.7575,   75.6335,   23.9239,
    8.7039,   76.6225,   24.3969,
   11.5651,   77.5124,   24.9751,
    9.9653,   75.6193,   26.5952,
    8.4945,   73.8299,   28.2573,
    7.1394,   72.1286,   29.9574,
    5.8881,   70.5021,   31.6923,
    4.7304,   68.9391,   33.4595,
    3.6568,   67.4300,   35.2569,
    2.6593,   65.9664,   37.0828,
    1.7305,   64.5415,   38.9360,
    0.8641,   63.1490,   40.8155,
    0.0543,   61.7839,   42.7207,
   -0.7039,   60.4416,   44.6510,
   -1.4152,   59.1182,   46.6065,
   -2.0834,   57.8100,   48.5869,
   -2.7123,   56.5140,   50.5925,
   -3.3051,   55.2273,   52.6238,
   -3.8647,   53.9475,   54.6811,
   -4.3936,   52.6722,   56.7652,
   -4.8944,   51.3992,   58.8769,
   -5.3690,   50.1265,   61.0172,
   -5.8195,   48.8520,   63.1874,
   -6.2475,   47.5740,   65.3888,
   -6.6547,   46.2906,   67.6228,
   -7.0425,   45.0000,   69.8914
};

float lift2[141] = {
  -29.8989,   52.5099,   44.0474,
  -29.6199,   53.5235,   41.9713,
  -29.3198,   54.5274,   39.9108,
  -28.9960,   55.5217,   37.8651,
  -28.6456,   56.5065,   35.8336,
  -28.2652,   57.4819,   33.8155,
  -27.8510,   58.4478,   31.8103,
  -27.3982,   59.4040,   29.8175,
  -26.9011,   60.3501,   27.8365,
  -26.3531,   61.2857,   25.8671,
  -25.7461,   62.2101,   23.9091,
  -25.0700,   63.1225,   21.9624,
  -24.3128,   64.0214,   20.0270,
  -23.4590,   64.9053,   18.1033,
  -22.4896,   65.7719,   16.1918,
  -21.3798,   66.6182,   14.2934,
  -20.0980,   67.4402,   12.4096,
  -18.6025,   68.2323,   10.5423,
  -16.8375,   68.9869,    8.6946,
  -14.7274,   69.6929,    6.8707,
  -12.1681,   70.3346,    5.0772,
   -9.0132,   70.8884,    3.3234,
   -5.0553,   71.3178,    1.6236,
         0,   71.3178,         0,
    5.0553,   71.3178,    1.6236,
    9.0132,   70.8884,    3.3234,
   12.1681,   70.3346,    5.0772,
   14.7274,   69.6929,    6.8707,
   16.8375,   68.9869,    8.6946,
   18.6025,   68.2323,   10.5423,
   20.0980,   67.4402,   12.4096,
   21.3798,   66.6182,   14.2934,
   22.4896,   65.7719,   16.1918,
   23.4590,   64.9053,   18.1033,
   24.3128,   64.0214,   20.0270,
   25.0700,   63.1225,   21.9624,
   25.7461,   62.2101,   23.9091,
   26.3531,   61.2857,   25.8671,
   26.9011,   60.3501,   27.8365,
   27.3982,   59.4040,   29.8175,
   27.8510,   58.4478,   31.8103,
   28.2652,   57.4819,   33.8155,
   28.6456,   56.5065,   35.8336,
   28.9960,   55.5217,   37.8651,
   29.3198,   54.5274,   39.9108,
   29.6199,   53.5235,   41.9713,
   29.8989,   52.5099,   44.0474
};

// These are just for incrementationing
int n = 1;
int j = 1;
 
void setup() 
{ 
  myservo1A.attach(6);
  myservo1B.attach(8);
  myservo1C.attach(7);
  myservo2A.attach(9);
  myservo2B.attach(10);
  myservo2C.attach(11);// attaches the servo on pin 9 to the servo object 
  Serial.begin(9600);
//  Serial.print("hi there");
} 
 
void loop() { 
  // Note: I got no clue if this is right, so consider it sudo code...
  for (n = 1; n <= 47; n += 1) {
    int mul = n-1;
    myservo1A.write(lift1[1+(mul*3)]);
    myservo1B.write(lift1[2+(mul*3)]);
    myservo1C.write(lift1[3+(mul*3)]);
    myservo2A.write(walk2[1+(mul*3)]);
    myservo2B.write(walk2[2+(mul*3)]);
    myservo2C.write(walk2[3+(mul*3)]);
    delay(500);
  }
  n = 1;
  /// Return Functions
  for (j = 1; j<= 47; j += 1) {
    int mul = j-1;
    myservo1A.write(walk1[1+(mul*3)]);
    myservo1B.write(walk1[2+(mul*3)]);
    myservo1C.write(walk1[3+(mul*3)]);
    myservo2A.write(lift2[1+(mul*3)]);
    myservo2B.write(lift2[2+(mul*3)]);
    myservo2C.write(lift2[3+(mul*3)]);
    delay(500);
  }
  j = 1;
}

