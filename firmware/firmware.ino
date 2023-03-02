#include <stdint.h>
#include "common.h"
#include "globals.h"

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize pins input/output
  pinMode(MIC, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);
  analogReadResolution(12); //use 12-bit resolution for analog reading

  // initialize serial communication for debugging
  delay(5*1000);
  Serial.begin(SERIAL_BAUD);
  delay(5*1000);

  // configure device with MAC address
  // Flash.deviceSetup();

  // initialize radio communication for transmitting data
  Radio.initializeRadio();
}

// the loop function runs over and over again forever
void loop() {
  // float data[HISTORY_THRESHOLD];
  // int counter = 0;
  float read_in;
  // float min;
  // float max;
  // float amplitude_threshold = learnAmplitudeThreshold();

  while (1) {
    // get raw analog reading from mic input
    read_in = analogRead (MIC);
    Serial.println((read_in*MAX_VOLTAGE)/4095);
    // data[counter % HISTORY_THRESHOLD] = read_in;

    // // check if data array is fully populated
    // if (counter > HISTORY_THRESHOLD) {
    //     // discover min and max to calculate amplitude
    //     min = data[0];
    //     max = data[0];
    //     for (int i=0; i<HISTORY_THRESHOLD; i++) {
    //         if (data[i] < min) {
    //             min = data[i];
    //         }
    //         if (data[i] > max) {
    //             max = data[i];
    //         }
    //     }
        // determine whether valve is open or closed
        // if ((max - min) > amplitude_threshold) {
        //     // Serial.println(1);
        // }
        // else {
        //     // Serial.println(0);
        // }
    // }
    // counter++;
  }
}
