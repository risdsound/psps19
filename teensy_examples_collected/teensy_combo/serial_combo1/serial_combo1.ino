/*

  For Teensy LC basic serial communition to Pure Data
  Code adapted from Adafruit, Alexandros Drymonits, Yann Seznec, and PJRC: public domain

  install Adafruit_TCS34725 library, Tools > Manage Libraries
  see reference: https://learn.adafruit.com/adafruit-color-sensors/overview


  RGB color sensor, 5 analog inputs, 1 button

  RGB color sensor
  Connect SCL    to Teensy pin 18 / A5
  Connect SDA    to Teensy pin 19 / A4

  Analog inputs (photocells, potentiometers)
  Connect to pins A0, A1, A2, A3, A6

  Digital input (button)
  Connect to pin D0

*/


#include <Wire.h>
#include "Adafruit_TCS34725.h"

// analog values array size, must be constant
const int num_of_analog_pins = 5; // total numer of analog pins
int analog_values[num_of_analog_pins];
int analog_pins[] = {
  0, 1, 2, 3, 6// list each analog pin to use
};

// digital_values array size, must be constant
const int num_of_digital_pins = 1; // total numer of digital pins
int digital_values[num_of_digital_pins];
int digital_pins [] = {
  0, // list each digital pin to use
};


/* Initialise with default values (int time = 2.4ms, gain = 1x) */
Adafruit_TCS34725 tcs = Adafruit_TCS34725();


float red;
float green;
float blue;
float Maximum;
float Minimum;
float rd;
float gd;
float bd;

void setup() {

  // analogReadResolution(12); // Teensy is 12bit ADC, you can set to 12 but this will introduce some noise, also you can set lower like 7bit for MIDI range
  analogReadAveraging(32); // Teensy can do averaging of samples in hardware, set to 4, 8, 16, 32

  pinMode(0, INPUT_PULLUP);  // set pin modes individually
  //  pinMode(1, INPUT_PULLUP);
  //  pinMode(2, INPUT_PULLUP);
  //  pinMode(3, INPUT_PULLUP);
  //  pinMode(4, INPUT_PULLUP);
  //  pinMode(5, INPUT_PULLUP);
  //  pinMode(6, INPUT_PULLUP);
  //  pinMode(7, INPUT_PULLUP);
  //  pinMode(8, INPUT_PULLUP);
  //  pinMode(9, INPUT_PULLUP);
  //  pinMode(10, INPUT_PULLUP);
  //  pinMode(11, INPUT_PULLUP);
  //  pinMode(12, INPUT_PULLUP);
  //  pinMode(13, INPUT_PULLUP);

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < num_of_analog_pins; i++) analog_values[i] = analogRead(analog_pins[i]);
  for (int i = 0; i < num_of_digital_pins; i++) digital_values[i] = !digitalRead(digital_pins[i]);


  Serial.print("analog_values: ");
  for (int i = 0; i < (num_of_analog_pins); i++) {
    Serial.print(analog_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");


  Serial.print("digital_values: ");
  for (int i = 0; i < (num_of_digital_pins); i++) {
    Serial.print(digital_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  // colorTemp = tcs.calculateColorTemperature(r, g, b);
  colorTemp = tcs.calculateColorTemperature_dn40(r, g, b, c);
  lux = tcs.calculateLux(r, g, b);

  red = r;
  green = g;
  blue = b;

  rd = red / 255;
  gd = green / 255;
  bd = blue / 255;

  Maximum = max(rd, gd);
  Maximum = max(Maximum, bd);
  Minimum = min(rd, gd);
  Minimum = min(Minimum, bd);

  float h, s, l = (Maximum + Minimum) / 2;

  if (Maximum == Minimum) {
    h = s = 0; // achromatic
  } else {
    double d = Maximum - Minimum;
    s = l > 0.5 ? d / (2 - Maximum - Minimum) : d / (Maximum + Minimum);
    if (Maximum == rd) {
      h = (gd - bd) / d + (gd < bd ? 6 : 0);
    } else if (Maximum == gd) {
      h = (bd - rd) / d + 2;
    } else if (Maximum == bd) {
      h = (rd - gd) / d + 4;
    }
    h /= 6;
  }

  Serial.print("color_temp: ");
  Serial.print(colorTemp, DEC);
  Serial.print(" ");
  Serial.println(" ");

  Serial.print("lux: ");
  Serial.print(lux, DEC);
  Serial.println(" ");

  Serial.print("rgbc: ");
  Serial.print(r, DEC);
  Serial.print(" ");
  Serial.print(g, DEC);
  Serial.print(" ");
  Serial.print(b, DEC);
  Serial.print(" ");
  Serial.print(c, DEC);
  Serial.print(" ");
  Serial.println(" ");


  Serial.print("hsl: ");
  Serial.print(h, DEC);
  Serial.print(" ");
  Serial.print(s, DEC);
  Serial.print(" ");
  Serial.print(l, DEC);
  Serial.print(" ");
  Serial.println(" ");


  delay(20);
}
