#include <stdint.h>
#include "common.h"
#include "globals.h"

// the setup function runs once when you press reset or power the board
void setup() {

  // initialize pins input/output
  pinMode(TEMP_PRE_PIN, INPUT);
  pinMode(TEMP_POST_PIN, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(POWER_PIN, OUTPUT);
  digitalWrite(POWER_PIN, HIGH);
  analogReadResolution(12); //use 12-bit resolution for analog reading

  // initialize serial communication for debugging
  delay(Secs_to_ms(5));
  Serial.begin(SERIAL_BAUD);
  delay(Secs_to_ms(5));

  // configure device with MAC address
  // Flash.deviceSetup();

  // initialize radio communication for transmitting data
  Radio.initializeRadio();
  Radio.sendConfigPacket(3);
}


float read_in;
float scaled_val;
int counter;

// temperature intinial values (hard coded for testing)
int postTemp = 20;
int preTemp = 16;
bool wrk = true;

// the loop function runs over and over again forever
void loop() {
  counter = 100;

  // listen for 25 seconds at every quarter second
  while (--counter >= 0) {
    // get raw analog reading from thermal couplers
    // preTemp = analogRead(TEMP_PRE_PIN);
    // postTemp = analogRead(TEMP_POST_PIN);

    // Algorithm to find out if on or not
      //  return string result
      // historicallizing it into array of n values
      // append to array[-1] and remove array
      // wrk = algorithm_output;

    // broadcast data over radio
    Radio.sendDataPacket(preTemp, postTemp, wrk, Error.get_error_byte());

    // wait 0.25 seconds
    delay(Secs_to_ms(0.25));    
  }

  

  

  delay(Secs_to_ms(1));
}
