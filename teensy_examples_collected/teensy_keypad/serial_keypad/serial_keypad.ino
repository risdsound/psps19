#include "Arduino.h"
#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char myKeys[ROWS][COLS] = {
  {'A', 'B', 'C'},
  {'D', 'E', 'F'},
  {'H', 'I', 'J'},
  {'K', 'L', 'M'}
};
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad (first 3 from left)
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad (next 4 fromt left)

Keypad customKeypad = Keypad( makeKeymap(myKeys), rowPins, colPins, ROWS, COLS);

void setup() {
  Serial.begin(9600);
}

void loop() {
  char customKey = customKeypad.getKey();

  if (customKey) {
    Serial.print("key: ");
    Serial.print(customKey);
    Serial.println(" ");
    delay(20);
  }
}
