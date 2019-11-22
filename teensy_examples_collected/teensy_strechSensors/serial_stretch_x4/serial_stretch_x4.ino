/*

  For Teensy LC basic serial communition to Pure Data
  Code adapted from Alexandros Drymonits, Yann Seznec, and PJRC: public domain

*/

// analog values array size, must be constant
const int num_of_analog_pins = 4; // total numer of analog pins
int analog_values[num_of_analog_pins];
int analog_pins[] = {
  0, 1, 2, 3// list each analog pin to use
};


void setup() {

  // analogReadResolution(12); // Teensy is 12bit ADC, you can set to 12 but this will introduce some noise, also you can set lower like 7bit for MIDI range
  analogReadAveraging(32); // Teensy can do averaging of samples in hardware, set to 4, 8, 16, 32

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < num_of_analog_pins; i++) analog_values[i] = analogRead(analog_pins[i]);


  Serial.print("analog_values: ");
  for (int i = 0; i < (num_of_analog_pins); i++) {
    Serial.print(analog_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");

  delay(20);
}
