#include "PPMath.h"

PPMath math = PPMath();



void setup() {
  Serial.begin(9600); 
  // put your setup code here, to run once:
  math.setup();

  math.moveTo(10, 10);
  //Serial.println(atan2(14, 1.5));
}

void loop() {
  //math.moveTo(10, 10); //mm
  //math.moveTo(0, 0);
  //delay(100000);
}
