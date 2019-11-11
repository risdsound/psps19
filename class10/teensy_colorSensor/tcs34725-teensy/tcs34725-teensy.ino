#include <Wire.h>
#include "Adafruit_TCS34725.h"

/* Example code for the Adafruit TCS34725 breakout library */

/* Connect SCL    to analog 5
   Connect SDA    to analog 4
   Connect VDD    to 3.3V DC
   Connect GROUND to common ground */

/* Initialise with default values (int time = 2.4ms, gain = 1x) */
// Adafruit_TCS34725 tcs = Adafruit_TCS34725();

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_101MS, TCS34725_GAIN_1X);

int currentR = 0;
int currentG = 0;
int currentB = 0;
float red;
float green;
float blue;
float Maximum;
float Minimum;
float rd;
float gd;
float bd;


void setup(void) {
  Serial.begin(9600);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // Now we're ready to get readings!
}

void loop(void) {
  uint16_t r, g, b, c, colorTemp, lux;

  tcs.getRawData(&r, &g, &b, &c);
  colorTemp = tcs.calculateColorTemperature(r, g, b);
  lux = tcs.calculateLux(r, g, b);

  currentR = r;
  currentG = g;
  currentB = b;

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


  Serial.print("color_values: ");
  Serial.print(currentR);
  Serial.print(" ");
  Serial.print(currentG);
  Serial.print(" ");
  Serial.print(currentB);
  Serial.print(" ");
  Serial.print(c);
  Serial.print(" ");
  Serial.print(colorTemp);
  Serial.print(" ");
  Serial.print(lux);
  Serial.print(" ");
  Serial.print(h); 
  Serial.print(" ");
  Serial.print(s); 
  Serial.print(" ");
  Serial.print(l); 
  Serial.print(" ");
  Serial.println(" ");


  //    Serial.print("Color Temp: "); Serial.print(colorTemp, DEC); Serial.print(" K - ");
  //    Serial.print("Lux: "); Serial.print(lux, DEC); Serial.print(" - ");
  //    Serial.print("R: "); Serial.print(r, DEC); Serial.print(" ");
  //    Serial.print("G: "); Serial.print(g, DEC); Serial.print(" ");
  //    Serial.print("B: "); Serial.print(b, DEC); Serial.print(" ");
  //    Serial.print("C: "); Serial.print(c, DEC); Serial.print(" ");
  //    Serial.println(" ");



}
