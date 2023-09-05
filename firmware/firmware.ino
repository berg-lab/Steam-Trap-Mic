#include <stdint.h>
#include "common.h"
#include "globals.h"
#include "max6675.h"

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
  delay(10000);
  Serial.println("Passed sendConfigPacket()");
  Serial.begin(SERIAL_BAUD);
  delay(10000);

  // configure device with MAC address
  // Flash.deviceSetup();

  // initialize radio communication for transmitting data
  Serial.println("Passed sendConfigPacket()");
  Radio.initializeRadio();
  Serial.println("Passed sendConfigPacket()");
  Radio.sendConfigPacket(3);
  Serial.println("Passed sendConfigPacket()");
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
  Serial.println(counter);

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
    Serial.print("Before data packet");
    Radio.sendDataPacket(preTemp, postTemp, wrk, Error.get_error_byte());
    Serial.print("\nPre Temp: ");
    Serial.print(Radio.getPreTemp());
    Serial.print("\nPost Temp: ");
    Serial.print(Radio.getPostTemp());

    // wait 0.25 seconds
    delay(250);    
  }

  

  

  delay(1000);
}
