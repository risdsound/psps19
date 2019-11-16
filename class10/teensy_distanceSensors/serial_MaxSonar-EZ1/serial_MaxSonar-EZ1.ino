/*
  Maxbotix simple test
  AN is analog pin A0
*/
#include "Maxbotix.h"

Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV);

void setup()
{
  Serial.begin(9600);
}

void loop()
{
  unsigned long start;
  
  // analog
  start = millis();
  Serial.print("distance: ");
  Serial.print(rangeSensorAD.getRange());
  Serial.print(" ");
  Serial.println(" ");
  delay(50);
}
