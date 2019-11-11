#define RESISTOR 10000 //This should be the same value of the used resistor  
#define RUBBERCORDPIN A0  //This is the pin where the cord is connected tp
void setup(void) {
  Serial.begin(9600);
}


void loop(void) {
  int value;
  int raw = 0;          // Raw input value
  int vin = 5;          // Store input voltage, this should be 5
  float vout = 0;        // Store output voltage
  float refresistor1 = 10;  // Variable to store the R1 value
  float refresistor2 = 0;  //  Value is determined by the voltage
  //that falls across after it has been measured.
  float buffer = 0;      // Buffer variable for calculation
  value = analogRead(RUBBERCORDPIN);     //Read the value
  //Just like we did earlier
  vout = (3.2 / 1023.0) * value;         // Calculates the voltage
  buffer = (vin / vout) - 1;
  refresistor2 = refresistor1 / buffer;
  Serial.print("Voltage: ");
  Serial.println(vout);                  // Outputs the information
  Serial.print("Resistance: ");
  Serial.println(refresistor2);
  delay(20);
}
