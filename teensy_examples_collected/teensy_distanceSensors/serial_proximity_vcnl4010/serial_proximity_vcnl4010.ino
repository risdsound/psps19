// reference: https://learn.adafruit.com/using-vcnl4010-proximity-sensor/

#include <Wire.h>
#include "Adafruit_VCNL4010.h" // install library, Tools > Manage Libraries

Adafruit_VCNL4010 vcnl;

void setup() {
  Serial.begin(9600);
  Serial.println("VCNL4010 test");

  if (! vcnl.begin()){
    Serial.println("Sensor not found :(");
    while (1);
  }
  Serial.println("Found VCNL4010");
}


void loop() {
   Serial.print("ambient: "); 
   Serial.print(vcnl.readAmbient());
   Serial.print(" ");
   Serial.println(" ");
   
   Serial.print("proximity: "); 
   Serial.print(vcnl.readProximity());
   Serial.print(" ");
   Serial.println(" ");
   delay(50);
}
