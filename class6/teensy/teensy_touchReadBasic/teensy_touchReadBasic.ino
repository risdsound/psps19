// with Teensy LC just stick a wire into pins 0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23
// and they become capactive sensors, no other electronic components required

// adapted from http://little-scale.blogspot.com Sebastian Tomczak


int currentVal;
int newVal;

void setup() {
  currentVal = 1;
  newVal = 1;
}

void loop() {

  // the number after sendControlChange is the MIDI ctlin number
  // the number after touchRead is the touch sense pin on the Teensy LC

  // usbMIDI.sendControlChange(1, constrain(map(touchRead(0), 1000, 5000, 0, 127), 0, 127), 1);
  // usbMIDI.sendControlChange(2, constrain(map(touchRead(1), 1000, 5000, 0, 127), 0, 127), 1);
  // usbMIDI.sendControlChange(3, constrain(map(touchRead(3), 1000, 5000, 0, 127), 0, 127), 1);
  // usbMIDI.sendControlChange(4, constrain(map(touchRead(4), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(5, constrain(map(touchRead(15), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(6, constrain(map(touchRead(16), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(7, constrain(map(touchRead(17), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(8, constrain(map(touchRead(18), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(9, constrain(map(touchRead(19), 1000, 5000, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(10, constrain(map(touchRead(22), 1000, 5000, 0, 127), 0, 127), 1);
  // usbMIDI.sendControlChange(11, constrain(map(touchRead(23), 1000, 5000, 0, 127), 0, 127), 1);

  // plus one analog in

  newVal = analogRead(0);

  if (abs(newVal - currentVal) > 3) {
    usbMIDI.sendControlChange(1, newVal >> 3, 1);
    currentVal = newVal;
  }


  delay (20);
}
