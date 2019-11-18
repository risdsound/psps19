// with Teensy LC just stick a wire into pins 0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23
// and they become capactive sensors, no other electronic components required

// touch values array size, must be constant
const int num_of_touch_pins = 11; // total numer of analog pins
int touch_values[num_of_touch_pins];
int touch_pins[] = {
  0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23 // list each touch pin to use
};



void setup() {
  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < num_of_touch_pins; i++) touch_values[i] = touchRead(touch_pins[i]);
  Serial.print("touch_values: ");
  for (int i = 0; i < (num_of_touch_pins); i++) {
    Serial.print(touch_values[i]);
    Serial.print(" ");
  }
  Serial.println(" ");
  delay (20);
}
