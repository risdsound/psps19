/*

RISD CTC-2001
Programming Sound: Performance Systems
Prof. Shawn Greenlee

Teensy LC starter code - PWM out

!!! remember, only use the 3.3-volt power pin. DO NOT USE 5-volt or you may fry your board!!!

Code adapted from Yann Seznec www.yannseznec.com
and pjrc (makers of Teensy). These sources are in public domain.

You must have Teensyduino installed:
https://www.pjrc.com/teensy/td_download.html

When uploading code to board remember to set: Tools > Board > Teensy LC

&

Set: Tools > USB Type > MIDI

*/

// set analog input pins
// set for none in this example

int const numPins = 0; //  set number of analog inputs to use
int currentVal[numPins];
int newVal[numPins];
int analogPins[] = {
  // set which analog pins to use
};

// set digital input pins
// set for none in this exampl

int const numDigPinsCC = 0; // number of digital pins to send CC
int currentDigcc[numDigPinsCC];
int digitalpincc[] = {
  // which digital pins to use for sending CC
};
int digInputcc[numDigPinsCC];

// the MIDI channel number to send messages
const int channel = 1;

elapsedMillis msec = 0;

void HandleCC(byte channel, byte number, byte value) {

// Note: note all digital pins can be PWM, see your Teensy LC chart for which can be set. 
// These should be D3, D4, D6, D9, D10, D16, D17, D20, D22, D23
  
  // D3 

  if (number == 63) {
    analogWrite(3, value * 2);
  }

  // D4 
  
  if (number == 64) {
    analogWrite(4, value * 2);
  }

}


void setup() {
  //  pinMode(0, INPUT_PULLUP);
  //  pinMode(1, INPUT_PULLUP);
  //  pinMode(2, INPUT_PULLUP);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  //  pinMode(5, INPUT_PULLUP);
  //  pinMode(6, INPUT_PULLUP);
  //  pinMode(7, INPUT_PULLUP);
  //  pinMode(8, INPUT_PULLUP);
  //  pinMode(9, INPUT_PULLUP);
  //  pinMode(10, INPUT_PULLUP);
  //  pinMode(11, INPUT_PULLUP);
  //  pinMode(12, INPUT_PULLUP);
  //  pinMode(13, INPUT_PULLUP);

  usbMIDI.setHandleControlChange(HandleCC);

}

void loop() {
  if (msec >= 20) {
    msec = 0;

    // digital pins sending CC

    for (int i = 0; i < numDigPinsCC; i++) {
      if (digitalRead(digitalpincc[i]) == 1 && currentDigcc[i] == 0) {
        usbMIDI.sendControlChange(i + 51, 0, channel);
        currentDigcc[i] = 1;
      }
      if (digitalRead(digitalpincc[i]) == 0  && currentDigcc[i] == 1) {
        usbMIDI.sendControlChange(i + 51, 127, channel);
        currentDigcc[i] = 0;
      }
    }

    // analog pins

    for (int i = 0; i < numPins; i++) {

      newVal[i] = analogRead(analogPins[i]);

      if (abs(newVal[i] - currentVal[i]) > 3) {
        usbMIDI.sendControlChange(i + 1, newVal[i] >> 3, channel);
        currentVal[i] = newVal[i];
      }
    }
  }

  usbMIDI.read();

}
