// with Teensy LC just stick a wire into pins 0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23
// and they become capactive sensors, no other electronic components required

// touch values array size, must be constant
const int num_of_touch_pins = 11; // total numer of analog pins
int touch_values[num_of_touch_pins];
int touch_pins[] = {
  0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23 // list each touch pin to use
};



void setup() {
  
}

void loop() {
  for (int i = 0; i < num_of_touch_pins; i++) touch_values[i] = constrain(map(touchRead(touch_pins[i]), 700, 3300, 0, 127), 0, 127); // map values to calibrate
  for (int i = 0; i < (num_of_touch_pins); i++) {
    usbMIDI.sendControlChange(i + 1, touch_values[i], 1);
  }
  delay (20);
}
