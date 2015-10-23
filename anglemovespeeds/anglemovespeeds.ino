#include <MatrixMath.h>
float speeds[3]; 

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void turnspeeds(float *movespds, int d, int theta, int gamma, float *anglespds) //function that doesn't return anything but edits the array
  {
    
    float matrix[3][3] =
    {
      {cos(gamma)*cos(theta), d*sin(gamma)*sin(theta), d*sin(gamma)*cos(theta)},
      {cos(gamma)*sin(theta), d*sin(gamma)*cos(theta), d*sin(gamma)*sin(theta)},
      {-sin(gamma), 0, -d*cos(gamma)}  
    };
    float dthetagamma[3];
    Matrix.Invert((float*)matrix, 3);
    Matrix.Multiply((float*)matrix, (float*)movespds, 1, 3, 3, (float*)dthetagamma);
    Matrix.Print((float*)matrix, 3, 3, "matrix"); //just print that now-inverted matrix
    Matrix.Print((float*)dthetagamma, 1, 3, "dthetagamma");
  }

void loop() {
  // put your main code here, to run repeatedly:
  float anglespeeds[3]; //intialize a 3x1 array to store speeds of d, theta, gamma
  float movespeeds[3] = {0, 1, 0}; //initialize a 3x1 array to store desired x, y, and z speeds
  
  turnspeeds(movespeeds, 1, 1, 1, anglespeeds);
  
}
