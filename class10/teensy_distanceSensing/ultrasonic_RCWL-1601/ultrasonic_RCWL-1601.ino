#include <NewPing.h> // install this library

#define SONAR_NUM 2      // Number of RCWL-1601 sensors.
#define MAX_DISTANCE 200 // Maximum distance (in cm) to ping.

NewPing sonar[SONAR_NUM] = {   // Sensor object array.
  NewPing(3, 4, MAX_DISTANCE), // trigger pin 3, echo pin 4, and max distance to ping.
  NewPing(5, 6, MAX_DISTANCE), // trigger pin 5, echo pin 6, and max distance to ping
};

void setup() {
  Serial.begin(115200); // Open serial monitor at 115200 baud to see ping results.
}

void loop() {
  Serial.print("distance: "); // prefix for Pd messaging
  for (uint8_t i = 0; i < SONAR_NUM; i++) { // Loop through each sensor and display results.
    Serial.print(sonar[i].ping_cm());
    Serial.print(" ");
    delay(50); // Wait 50ms between pings (about 20 pings/sec). 29ms should be the shortest delay between pings.
  }
  Serial.println(); // mark end of message
}
