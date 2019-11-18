/*
demonstrating use of AT42QY1010 capacitive momentary touch board
*/

// set digital pins

int const numDigPinsCC = 1; // change the number to how many digital pins you will use
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  0, // list the numbers of each pin you will use seperated by a comma
};

int digInputcc[numDigPinsCC];

// the MIDI channel number to send messages
const int channel = 1; // don't change unless you know what you are doing 

elapsedMillis msec = 0; // don't change 

void setup() {

  // This tells the digital pins how to function, comment out any unused pins

pinMode(0, INPUT_PULLUP);
//  pinMode(1, INPUT_PULLUP);
//  pinMode(2, INPUT_PULLUP);
//  pinMode(3, INPUT_PULLUP);
//  pinMode(4, INPUT_PULLUP);
//  pinMode(5, INPUT_PULLUP);
//  pinMode(6, INPUT_PULLUP);
//  pinMode(7, INPUT_PULLUP);
//  pinMode(8, INPUT_PULLUP);
//  pinMode(9, INPUT_PULLUP);
//  pinMode(10, INPUT_PULLUP);
//  pinMode(11, INPUT_PULLUP);
//  pinMode(12, INPUT_PULLUP);
//  pinMode(13, INPUT_PULLUP);
}


/*


*/

void loop() {

  // establish a speed limit

  if (msec >= 20) {
    msec = 0;

    // digital pins input sending CC messages beginning at ctlin 51 for Pd

    for (int i = 0; i < numDigPinsCC; i++) {
      if (digitalRead(digitalpincc[i]) == 0 && currentDigcc[i] == 1) {
        usbMIDI.sendControlChange(i + 51, 0, channel);
        currentDigcc[i] = 0;
      }
      if (digitalRead(digitalpincc[i]) == 1  && currentDigcc[i] == 0) {
        usbMIDI.sendControlChange(i + 51, 127, channel);
        currentDigcc[i] = 1;
      }
    }
  }

  // MIDI Controllers can discard incoming MIDI messages.
  // http://forum.pjrc.com/threads/24179-Teensy-3-Ableton-Analog-CC-causes-midi-crash

  while (usbMIDI.read()) {
    // ignore incoming messages
  }
}
