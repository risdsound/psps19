// with Teensy LC just stick a wire into pins 0, 1, 3, 4, 15, 16, 17, 18, 19, 22, 23
// and they become capactive sensors, no other electronic components required

// adapted from http://little-scale.blogspot.com Sebastian Tomczak


int currentVal;
int newVal;

void setup() {

}

void loop() {

  // the number after sendControlChange is the MIDI ctlin number
  // the number after touchRead is the touch sense pin on the Teensy LC

  usbMIDI.sendControlChange(1, constrain(map(touchRead(0), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(2, constrain(map(touchRead(1), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(3, constrain(map(touchRead(3), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(4, constrain(map(touchRead(4), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(5, constrain(map(touchRead(15), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(6, constrain(map(touchRead(16), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(7, constrain(map(touchRead(17), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(8, constrain(map(touchRead(18), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(9, constrain(map(touchRead(19), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(10, constrain(map(touchRead(22), 700, 3300, 0, 127), 0, 127), 1);
  usbMIDI.sendControlChange(11, constrain(map(touchRead(23), 700, 3300, 0, 127), 0, 127), 1);

  delay (20);
}
