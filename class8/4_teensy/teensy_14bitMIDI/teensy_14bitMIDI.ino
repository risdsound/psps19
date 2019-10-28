//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////
 /*
 *  USB-MIDI high resolution (14-bit) faders
 *  

 *  Code by Rodrigo Constanzo, http://www.rodrigoconstanzo.com 
 *  Discussion here: https://llllllll.co/t/programming-arduino-teensy/24817
 *  
 *  Some small changes by Shawn Greenlee, adapting from 1 to 4 faders http://shawngreenlee.com 
 * 
 *  
 *  coded for
 *     TT Electronics PS45G-C1LBR10KN fader: https://www.digikey.com/product-detail/en/tt-electronics-bi/PS45G-C1LBR10KN/987-1402-ND/2620671
 *     TeensyLC: https://www.pjrc.com/teensy/teensyLC.html
 *     Adafruit ADS1115: https://www.adafruit.com/product/1085
 *  
 *  EXPLANATION
 *  -----------
 *  The code takes analog readings from the ADS1115 external ADC and scales, smooths, and
 *  constrains the output before sending it as high resolution MIDI CCs (using two CCs to
 *  MSB and LSB). The code includes a calibration routine that takes the minimum and maximum
 *  readings of the fader used and stores them in the internal EEPROM. To use the calibration
 *  routine, you must send Program Change message 13 followed by 69, both on channel 11. The
 *  initial state of the device can be reset by sending Program Change message 10 followed by 
 *  110.
 *  (example Max/MSP code below)
 *
 */
//////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////

// required libraries
#include <Wire.h>
#include <Adafruit_ADS1015.h>
#include <ResponsiveAnalogRead.h>
#include <EEPROM.h>


// declared variables

// define MIDI channel
const int channel = 11;

// define CC for the first CC (MSB)
const int cc_msb0 = 4;
const int cc_msb1 = 3;
const int cc_msb2 = 2;
const int cc_msb3 = 1;

// define CC for the second CC (LSB)
// **this should be 32 higher than the MSB if you want it to work properly in apps that accept 14-bit MIDI**
const int cc_lsb0 = 36;
const int cc_lsb1 = 35;
const int cc_lsb2 = 34;
const int cc_lsb3 = 33;



// internal LED for calibration/reset status
// const int led = 13;

// declare the available sensor range
// using a TeensyLC and ADS1115 gives you 80% of 4.096v (3.3v is 80%) so that makes 26400 80% of 32768
const int sensor_range = 26400;

// set output range (14-bit = 16383)
const int output_range = 16383;

// ints for filtering repeats
int current_value0 = 0;
int previous_value0 = 0;
int current_value1 = 0;
int previous_value1 = 0;
int current_value2 = 0;
int previous_value2 = 0;
int current_value3 = 0;
int previous_value3 = 0;


// flag to check if in calibration mode
int calibrate_flag = 0;

// flag to check if in reset mode
int reset_flag = 0;

// store whether device has ever been calibrated in order to allow default settings
int has_been_calibrated = EEPROM.read(10);

// by default leave 5% slop at the top end and 2.5% slop at the bottom
int calibrate_min = 0 + (sensor_range / 40);
int calibrate_max = sensor_range - (sensor_range / 20);

// instantiate adafruit library
Adafruit_ADS1115 ads;

// variable to store sensor reading
int16_t adc0;
int16_t adc1;
int16_t adc2;
int16_t adc3;


// initialize sensor reading
ResponsiveAnalogRead analog0(0, true);
ResponsiveAnalogRead analog1(1, true);
ResponsiveAnalogRead analog2(2, true);
ResponsiveAnalogRead analog3(3, true);






/////////////////////////// SETUP ///////////////////////////

void setup(void) 
{

  // Serial.begin(9600);

  // look for program change messages (for calibration routine)
  usbMIDI.setHandleProgramChange(OnProgramChange);

  // if the device has been calibrated, use the stored settings instead of default settings
  if (has_been_calibrated == 1) {
    calibrate_min = constrain((BitShiftCombine(EEPROM.read(0), EEPROM.read(1))), 0, sensor_range);
    calibrate_max = constrain((BitShiftCombine(EEPROM.read(2), EEPROM.read(3))), 0, sensor_range);
  }

  /*
  Serial.print("The initial calibrate_min value is");
  Serial.print(" ");
  Serial.println(calibrate_min);

  Serial.print("The initial calibrate_max value is");
  Serial.print(" ");
  Serial.println(calibrate_max);
  */

  // initialize ADS1115 library
  ads.begin();

  // set ADS1115 gain to 1x, to get the maximum possible range with the 3.3v Teensy
  ads.setGain(GAIN_ONE);        // 1x gain   +/- 4.096V  1 bit = 2mV      0.125mV

  // set smoothing resolution
  analog0.setAnalogResolution(sensor_range);
  analog1.setAnalogResolution(sensor_range);
  analog2.setAnalogResolution(sensor_range);
  analog3.setAnalogResolution(sensor_range);


  // reset sketch to initial state
  // EEPROM.write(10,255);

}


/////////////////////////// LOOP ///////////////////////////

void loop(void) {

  // read analog pin 0 from ADS1115
  adc0 = ads.readADC_SingleEnded(0);
  analog0.update(adc0);

  // scale the available reading range to the available output range (typically 14-bit MIDI)
  current_value0 = map(analog0.getValue(), calibrate_min, calibrate_max, 0, output_range); 

  // constrain value after scaling to avoid exceeding the available range
  current_value0 = (constrain(current_value0, 0, output_range));

  // filter repeats
  if (current_value0 != previous_value0) {
      if (current_value0 >> 7 != previous_value0 >> 7) {
        usbMIDI.sendControlChange(cc_msb0, current_value0 >> 7, channel);
      }
      usbMIDI.sendControlChange(cc_lsb0, current_value0 & 127, channel); 
      previous_value0 = current_value0;
  }



 // read analog pin 1 from ADS1115
  adc1 = ads.readADC_SingleEnded(1);
  analog1.update(adc1);

  // scale the available reading range to the available output range (typically 14-bit MIDI)
  current_value1 = map(analog1.getValue(), calibrate_min, calibrate_max, 0, output_range); 

  // constrain value after scaling to avoid exceeding the available range
  current_value1 = (constrain(current_value1, 0, output_range));

  // filter repeats
  if (current_value1 != previous_value1) {
      if (current_value1 >> 7 != previous_value1 >> 7) {
        usbMIDI.sendControlChange(cc_msb1, current_value1 >> 7, channel);
      }
      usbMIDI.sendControlChange(cc_lsb1, current_value1 & 127, channel); 
      previous_value1 = current_value1;
  }

  // read analog pin 2 from ADS1115
  adc2 = ads.readADC_SingleEnded(2);
  analog2.update(adc2);

  // scale the available reading range to the available output range (typically 14-bit MIDI)
  current_value2 = map(analog2.getValue(), calibrate_min, calibrate_max, 0, output_range); 

  // constrain value after scaling to avoid exceeding the available range
  current_value2 = (constrain(current_value2, 0, output_range));

  // filter repeats
  if (current_value2 != previous_value2) {
      if (current_value2 >> 7 != previous_value2 >> 7) {
        usbMIDI.sendControlChange(cc_msb2, current_value2 >> 7, channel);
      }
      usbMIDI.sendControlChange(cc_lsb2, current_value2 & 127, channel); 
      previous_value2 = current_value2;
  }

    // read analog pin 3 from ADS1115
  adc3 = ads.readADC_SingleEnded(3);
  analog3.update(adc3);

  // scale the available reading range to the available output range (typically 14-bit MIDI)
  current_value3 = map(analog3.getValue(), calibrate_min, calibrate_max, 0, output_range); 

  // constrain value after scaling to avoid exceeding the available range
  current_value3 = (constrain(current_value3, 0, output_range));

  // filter repeats
  if (current_value3 != previous_value3) {
      if (current_value3 >> 7 != previous_value3 >> 7) {
        usbMIDI.sendControlChange(cc_msb3, current_value3 >> 7, channel);
      }
      usbMIDI.sendControlChange(cc_lsb3, current_value3 & 127, channel); 
      previous_value3 = current_value3;
  }
 
 
  // update MIDI
  usbMIDI.read();
  
}

// currently all fader ranges based on calibration of adc0 sensor (seems OK if sensors are identical)

/////////////////////////// FUNCTIONS ///////////////////////////

// create a single 16-bit int from two 8-bit ints
int BitShiftCombine(unsigned char x_high, unsigned char x_low) {
  int combined; 
  combined = x_high;              //send x_high to rightmost 8 bits
  combined = combined<<8;         //shift x_high over to leftmost 8 bits
  combined |= x_low;                 //logical OR keeps x_high intact in combined and fills in                                                             //rightmost 8 bits
  return combined;
}

// calibration and reset routines to run when receiving program change messages on channel 11
void OnProgramChange(byte channel, byte program) {
  // offset midi program channel message since they count from 1 instead of 0
  program++;
  if (channel == 11) {
    if (program == 13) {
      calibrate_flag = 1;
      } else if (calibrate_flag == 1) {
         if (program == 69) {

          // enable LED notification of status
          // digitalWrite(led, HIGH);
          // Serial.println("calibrating!");
          
          while (calibrate_flag == 1) {
            
            // actual calibration function 
            calibrateSensor();

            // terminate while loop
            calibrate_flag = 0;      
          }

          // turn off notification LED
          // digitalWrite(led, LOW);

          // add a little buffer at each extreme to ensure the values can achieve the full range
          calibrate_min += 1;
          calibrate_max -= 5;
            
          // clamp and slightly limit reading values and write new min/max values to EEPROM
          EEPROM.write(0, (constrain(calibrate_min, 0, sensor_range / 5) + 10) >> 8);
          EEPROM.write(1, (constrain(calibrate_min, 0, sensor_range / 5) + 10) & 255);
          EEPROM.write(2, (constrain(calibrate_max, sensor_range - sensor_range / 5, sensor_range) - 10) >> 8);
          EEPROM.write(3, (constrain(calibrate_max, sensor_range - sensor_range / 5, sensor_range) - 10) & 255);
          
          // write the fact that device has been calibrated to EEPROM
          EEPROM.write(10, 1);

          /*
          Serial.println("done calibrating!");
          Serial.println(calibrate_min);
          Serial.println(calibrate_max);
          */

         } else {
          calibrate_flag = 0;
         }
    }
  }
    // reset initial state
    if (channel == 11) {
      if (program == 10) {
        reset_flag = 1;
        } else if (reset_flag == 1) {
          if (program == 110) {

          // digitalWrite(led, HIGH);
          delay(100);
         
          // write the fact that device has been reset to EEPROM
          EEPROM.write(10, 255);

          // reset minimum and maximum to initial values
          calibrate_min = 0 + (sensor_range / 40);
          calibrate_max = sensor_range - (sensor_range / 20);

          // Serial.println("values reset!");
          
          // turn off notification LED
          // digitalWrite(led, LOW);

          } else {
            reset_flag = 0;
          }
    }
  }
}

void calibrateSensor() {
  // declare variables to use in calibration routine
  bool calib_bool = true;
  bool schmitt = false;
  int schmitt_count = 0;

  // set minimum and maximum to absurd values
  calibrate_min = 1000000;
  calibrate_max = -100;
  
  while(calib_bool) {
    adc0 = ads.readADC_SingleEnded(0);
    analog0.update(adc0);
    int reading = analog0.getValue();

    // update the minimum and maximum values
    if (reading < calibrate_min) {
      calibrate_min = reading;
    }
    if(reading > calibrate_max) {
      calibrate_max = reading;
    }

    // use a schmitt trigger to count how many times the full range of the fader has been moved
    if (reading > sensor_range - (sensor_range / 4) && schmitt == false) {
      schmitt = true;
    }
    if (reading < sensor_range / 4 && schmitt == true) {
      schmitt = false;
      schmitt_count++;
    }

    // stop calibration routine after 4 passes have been made
    if(schmitt_count >= 4) {
      calib_bool = false;
    }
  }
}
