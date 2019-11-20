// this example require NewPing library, install under Tools > Manage Libraries
// this demonstates how to get MIDI data from the ultrasonic sensors, select MIDI as USB Type to test

#include <NewPing.h>

#define SONAR_NUM 2      // Number of ultrasonic sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(3, 4, MAX_DISTANCE), // Each sensor's trigger pin, echo pin, and max distance to ping. 
  NewPing(5, 6, MAX_DISTANCE), 
};

void setup() {
}

void loop() { 
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    usbMIDI.sendControlChange (i + 81, constrain(map(sonar[i].ping_cm(), 0, 200, 0, 127), 0, 127), 1);
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  }
}
