#include <MatrixMath.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  byte anglespeeds[3]; //initialize a byte array of size 3?

  void turnspeeds(int vx, int vy, int vz, int d, int theta, int gamma, byte *speeds) //function that doesn't return anything but edits the array
  {
    int matrix[3][3] =
    {
      {1, 2, 3}
      {4, 5, 6}
      {7, 8, 9}  
    };
    Matrix.Print((float*)matrix, 3, 3, "matrix"); //just print that matrix

  }
}
