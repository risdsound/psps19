/*

  For Teensy LC basic serial communition to Pure Data
  Code adapted from Alexandros Drymonits, Yann Seznec, and PJRC: public domain

*/

// analog values array size, must be constant
const int num_of_analog_pins = 3; // total numer of analog pins
int analog_values[num_of_analog_pins];
int analog_pins[] = {
  3, 4, 5 // list each analog pin to use
};

// digital_values array size, must be constant
const int num_of_digital_pins = 3; // total numer of digital pins
int digital_values[num_of_digital_pins];
int digital_pins [] = {
  0, 5, 10, // list each digital pin to use
};


void setup() {
  pinMode(0, INPUT_PULLUP);  // set pin modes individually
  //  pinMode(1, INPUT_PULLUP);
  //  pinMode(2, INPUT_PULLUP);
  //  pinMode(3, INPUT_PULLUP);
  //  pinMode(4, INPUT_PULLUP);
  pinMode(5, INPUT_PULLUP);
  //  pinMode(6, INPUT_PULLUP);
  //  pinMode(7, INPUT_PULLUP);
  //  pinMode(8, INPUT_PULLUP);
  //  pinMode(9, INPUT_PULLUP);
  pinMode(10, INPUT_PULLUP);
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

  delay(20);
}
