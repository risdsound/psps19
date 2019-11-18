
// This example for I2C pins on Teensy LC for serial connection with Pure Data

// install Adafruit LIS3DH library (Tools > Manage Libraries)
// install Adafruit Sensor library (Tools > Manage Libraries)
// sensor reference at https://learn.adafruit.com/adafruit-lis3dh-triple-axis-accelerometer-breakout/overview
// connect: 
// Vin to 3v on Teensy
// Ground to ground on Teensy
// SDA to pin #6 on Teensy
// SCL to pin #7 on Teensy

 
#include <Wire.h>
#include <Adafruit_LIS3DH.h>
#include <Adafruit_Sensor.h>

Adafruit_LIS3DH lis = Adafruit_LIS3DH();

void setup(void) {
  Serial.begin(9600);
  Serial.println("LIS3DH test!");

  if (! lis.begin(0x18)) {   
    Serial.println("Couldnt start");
    while (1) yield();
  }
  Serial.println("LIS3DH found!");

  lis.setRange(LIS3DH_RANGE_4_G);   // 2, 4, 8 or 16 G!

  Serial.print("Range = "); 
  Serial.print(2 << lis.getRange());
  Serial.println("G");
}

void loop() {
//  Serial.print("raw: ");
//  lis.read();      // get X Y and Z data at once
//  // Then print out the raw data
//  Serial.print(lis.x);
//  Serial.print(" ");
//  Serial.print(lis.y);
//  Serial.print(" ");
//  Serial.print(lis.z);
//  Serial.print(" ");

 Serial.print("acceleration: ");

  /* get a new sensor event, normalized */
  sensors_event_t event;
  lis.getEvent(&event);

  /* Display the results (acceleration is measured in m/s^2) */
 
  Serial.print(event.acceleration.x);
  Serial.print(" ");
  Serial.print(event.acceleration.y);
  Serial.print(" ");
  Serial.print(event.acceleration.z);
  Serial.print(" ");
  Serial.println();
  delay(50);
}
