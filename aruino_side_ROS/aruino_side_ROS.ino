#include <Wire.h>

//Stuff for Serial Comms:
char current_line[50]; // allocate some space for the string
int angles[18];

void setup() {
  Serial.begin(9600);
  Serial.println("started");
}

void loop() {
  read_line(current_line);
  for (int i=0; i<18; i++){
    Serial.println(angles[i]);
  }

}
