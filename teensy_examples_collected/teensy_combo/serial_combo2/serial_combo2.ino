/*

  For Teensy LC basic serial communition to Pure Data
  Code adapted from Adafruit, Alexandros Drymonits, Yann Seznec, Frankie Chu, and PJRC

  install Adafruit_TCS34725 library, Tools > Manage Libraries
  see reference: https://learn.adafruit.com/adafruit-color-sensors/overview


  combination of sensors, see code below for what is what

*/
// accelerometer pins A0, A1, A2
// analog pins A3, A6, A7, A8, A9
// digital pins D2, D5, D6, D7, D8, D9, D10, D11, D12
// touch pins D0, D1
// ultrasonic sensor pins D3, D4
// color sensor pins D18, D19 (SDA0, SDL0)



#include <NewPing.h> // ultrasonic sensor library
#include <Wire.h>
#include "Adafruit_TCS34725.h" // rgb color sensor library

#define SONAR_NUM 1      // Number of RCWL-1601 sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

#include "ADXL335.h" // accelerometer library 
ADXL335 accelerometer;



NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(3, 4, MAX_DISTANCE), // trigger pin 3, echo pin 4, and max distance to ping.
};

// analog values array size, must be constant
const int num_of_analog_pins = 5; // total numer of analog pins
int analog_values[num_of_analog_pins];
int analog_pins[] = {
  3, 6, 7, 8, 9// list each analog pin to use
};

// digital_values array size, must be constant
const int num_of_digital_pins = 9; // total numer of digital pins
int digital_values[num_of_digital_pins];
int digital_pins [] = {
  2, 5, 6, 7, 8, 9, 10, 11, 12, // list each digital pin to use
};

// touch values array size, must be constant
const int num_of_touch_pins = 2; // total numer of touch pins
int touch_values[num_of_touch_pins];
int touch_pins[] = {
  0, 1 // list each touch pin to use
};

// RGB color sensor
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
  pinMode(2, INPUT_PULLUP);
  //  pinMode(3, INPUT_PULLUP);
  //  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
  pinMode(8, INPUT_PULLUP);
  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
  pinMode(11, INPUT_PULLUP);
  pinMode(12, INPUT_PULLUP);
  //   pinMode(13, INPUT_PULLUP);

  Serial.begin(9600);
  accelerometer.begin();
}

void loop() {
  for (int i = 0; i < num_of_analog_pins; i++) analog_values[i] = analogRead(analog_pins[i]);
  for (int i = 0; i < num_of_digital_pins; i++) digital_values[i] = !digitalRead(digital_pins[i]);

  // analog pins 3, 6, 7, 8, 9
  Serial.print("analog_values: ");
  for (int i = 0; i < (num_of_analog_pins); i++) {
    Serial.print(analog_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  // digital pins 2, 5, 6, 7, 8, 9, 10, 11, 12
  Serial.print("digital_values: ");
  for (int i = 0; i < (num_of_digital_pins); i++) {
    Serial.print(digital_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  // accelerometer pins A0, A1, A2
  float ax, ay, az;
  accelerometer.getAcceleration(&ax, &ay, &az);
  Serial.print("acceleration: ");
  Serial.print(ax);
  Serial.print(" ");
  Serial.print(ay);
  Serial.print(" ");
  Serial.print(az);
  Serial.print(" ");
  Serial.println(" ");

  // ultrasonic sensor pins 3, 4
  Serial.print("distance: "); // prefix for Pd messaging
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    Serial.print(sonar[i].ping_cm());
    Serial.print(" ");
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  }
  Serial.println(); // mark end of message

  // touch pins 0, 1

  for (int i = 0; i < num_of_touch_pins; i++) touch_values[i] = touchRead(touch_pins[i]);
  Serial.print("touch_values: ");
  for (int i = 0; i < (num_of_touch_pins); i++) {
    Serial.print(touch_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");


  // color sensor
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
