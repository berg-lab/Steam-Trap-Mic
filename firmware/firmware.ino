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

// the loop function runs over and over again forever
void loop() {
  counter = 100;

  // listen for 25 seconds at every quarter second
  while (--counter >= 0) {
    // get raw analog reading from mic input
    read_in = analogRead(MIC);

    // convert back to true voltage
    scaled_val = (read_in * MAX_VOLTAGE)/4095;

    // TODO: further convert to frequency

    // broadcast data over radio
    Radio.sendDataPacket(scaled_val, Error.get_error_byte());

    // wait 0.25 seconds
    delay(Secs_to_ms(0.25));    
  }

  

  

  delay(Secs_to_ms(1));
}
