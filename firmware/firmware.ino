#include <stdint.h>
#include "common.h"
#include "globals.h"

// the setup function runs once when you press reset or power the board
void setup() {
    // initialize serial communication for debugging
    Serial.begin(SERIAL_BAUD);
    delay(3000);
    Serial.println("Serial initialized!");

    // initialize pins input/output
    pinMode(LED_BUILTIN, OUTPUT);
    analogReadResolution(12); //use 12-bit resolution for analog reading
    //Powering the MAX chips ------------------------------------------
    delay(500); // wait for MAX chips to stabilize
    Serial.println("PINS initialized!");

    // configure device with MAC address
    // Flash.deviceSetup();

    // initialize radio communication for transmitting data
    Radio.initializeRadio();
    Serial.println("Radio Initialized!");
    Radio.sendConfigPacket(3);
    Serial.println("Config Packet Sent!");
}

// the loop function runs over and over again forever
void loop() {
    float pre_temp = toCelcius(analogRead(THERMISTOR_PIN_0));
    float post_temp = toCelcius(analogRead(THERMISTOR_PIN_1));
    Blink(2000);
    Radio.sendDataPacket(pre_temp, post_temp, (uint8_t) 0);
}

// Methods
void Blink(int DELAY_MS)
{
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN,HIGH);
  delay(DELAY_MS/2);
  digitalWrite(LED_BUILTIN,LOW);
  delay(DELAY_MS/2);
}

float toCelcius(float resist_value) {
    float steinhart = 0;
  // convert the value to resistance
  steinhart = 1023 / resist_value - 1;
  steinhart = SERIESRESISTOR / steinhart;

  // convert to degrees Celcius
  steinhart = steinhart / THERMISTORNOMINAL;     // (R/Ro)
  steinhart = log(steinhart);                  // ln(R/Ro)
  steinhart /= BCOEFFICIENT;                   // 1/B * ln(R/Ro)
  steinhart += 1.0 / (TEMPERATURENOMINAL + 273.15); // + (1/To)
  steinhart = 1.0 / steinhart;                 // Invert
  steinhart -= 273.15;                         // convert absolute temp to C
  return steinhart;
}