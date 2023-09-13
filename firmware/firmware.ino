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
  // counter = 100;
  // Serial.println(counter);

  // // listen for 25 seconds at every quarter second
  // while (--counter >= 0) {
  //   // get raw analog reading from thermal couplers
  //   // preTemp = analogRead(TEMP_PRE_PIN);
  //   // postTemp = analogRead(TEMP_POST_PIN);

  //   // Algorithm to find out if on or not
  //     //  return string result
  //     // historicallizing it into array of n values
  //     // append to array[-1] and remove array
  //     // wrk = algorithm_output;

  //   // broadcast data over radio
  //   Serial.print("Before data packet");
  //   Radio.sendDataPacket(preTemp, postTemp, wrk, Error.get_error_byte());
  //   Serial.print("\nPre Temp: ");
  //   Serial.print(Radio.getPreTemp());
  //   Serial.print("\nPost Temp: ");
  //   Serial.print(Radio.getPostTemp());

  //   // wait 0.25 seconds
  //   delay(250);    
  // }
  // delay(1000);

    // Moving average
    const float mov_avg_alpha = 0.1;
    static float mov_avg = -100;
    double value;
    Blink(220);
    
    // Filling the history
    pre_temp_hist[pre_temp_cursor] = PreCouple.readCelsius();
    if (mov_avg == -100) mov_avg = pre_temp_hist[pre_temp_cursor];
    mov_avg = mov_avg_alpha * pre_temp_hist[pre_temp_cursor] + (1-mov_avg_alpha)*mov_avg;
    Serial.println("Before Radio.send");
    Radio.sendDataPacket(ARRAY_LENGTH, pre_temp_hist, (uint8_t) 0);
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
