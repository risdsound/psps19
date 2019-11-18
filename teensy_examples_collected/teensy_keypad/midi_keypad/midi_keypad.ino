// reference: https://www.adafruit.com/product/1824
// https://playground.arduino.cc/Code/Keypad/

#include "Arduino.h"
#include "Keypad.h"

const byte ROWS = 4; //four rows
const byte COLS = 3; //three columns
char keys[ROWS][COLS] = {
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'*', '0', '#'}
};
byte colPins[COLS] = {2, 3, 4}; //connect to the column pinouts of the keypad (first 3 from left)
byte rowPins[ROWS] = {5, 6, 7, 8}; //connect to the row pinouts of the keypad (next 4 fromt left)

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS );


const int channel = 1; // midi channel

elapsedMillis msec = 0; 


void setup() {
  Serial.begin(9600);
}

void loop() {
  if (msec >= 20) {
    msec = 0;
    char key = keypad.getKey();

    if (key != NO_KEY) {
      Serial.println(key);
    }
    if (key == '1') {
      usbMIDI.sendControlChange(51, 127, channel);
    }
    if (key == '2') {
      usbMIDI.sendControlChange(52, 127, channel);
    }
    if (key == '3') {
      usbMIDI.sendControlChange(53, 127, channel);
    }
    if (key == '4') {
      usbMIDI.sendControlChange(54, 127, channel);
    }
    if (key == '5') {
      usbMIDI.sendControlChange(55, 127, channel);
    }
    if (key == '6') {
      usbMIDI.sendControlChange(56, 127, channel);
    }
    if (key == '7') {
      usbMIDI.sendControlChange(57, 127, channel);
    }
    if (key == '8') {
      usbMIDI.sendControlChange(58, 127, channel);
    }
    if (key == '9') {
      usbMIDI.sendControlChange(59, 127, channel);
    }
    if (key == '0') {
      usbMIDI.sendControlChange(60, 127, channel);
    }
    if (key == '*') {
      usbMIDI.sendControlChange(61, 127, channel);
    }
    if (key == '#') {
      usbMIDI.sendControlChange(62, 127, channel);
    }

  }
  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
