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
    // analogReadResolution(12); //use 12-bit resolution for analog reading
    //Powering the MAX chips ------------------------------------------
    pinMode(TEMPERATURE_POWER_PIN, OUTPUT); digitalWrite(TEMPERATURE_POWER_PIN, HIGH);
    pinMode(TEMPERATURE_GND_PIN, OUTPUT); digitalWrite(TEMPERATURE_GND_PIN, LOW);
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

float read_in;
float scaled_val;
int counter;

// Arrays
long pre_temp_hist[ARRAY_LENGTH];

// Cursors to replace next item in array
int pre_temp_cursor = 0;

// temperature intinial values (hard coded for testing)
bool wrk = true;

// the loop function runs over and over again forever
void loop() {
    float value = PreCouple.readCelsius();
    Blink(220);
    Radio.sendDataPacket(value, (uint8_t) 0);
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
