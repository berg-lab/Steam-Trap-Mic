#include <stdint.h>
#include "common.h"
#include "globals.h"

// Setup (ran once at reset)
void setup() {
  // Serial Initialization
  Serial.begin(SERIAL_BAUD);
  delay(3000);
  Serial.println("Serial initialized!");

  // initialize pins input/output
  pinMode(LED_BUILTIN, OUTPUT);
  // analogReadResolution(12); //use 12-bit resolution for analog reading
  Serial.println("PINS initialized!");

  // MAC address configuration
  // Flash.deviceSetup();

  // Radio Initialization
  Radio.initializeRadio();
  Serial.println("Radio Initialized!");
  Radio.sendConfigPacket(3);
  Serial.println("Config Packet Sent!");

  // Timer Initialization
  Timer.clearFlag();
}

uint16_t pre_temp;
uint16_t post_temp;

// Loop (runs forever)
void loop() {
  if(Timer.timerExpired()) {
    // clear interrupt flag
    Timer.clearFlag();
    // Measure temperature
    sendTemp();
  }
  // Set new 10 minute timer
  Timer.setTimer(0,10,0);
  Serial.println("Alarm set, going to sleep now.");
  Timer.goSleep();
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

void sendTemp(void) {
  pre_temp = (int)(toCelcius(analogRead(THERMISTOR_PIN_0))*100);
  post_temp = (int)(toCelcius(analogRead(THERMISTOR_PIN_1))*100);
  Blink(2000);
  Serial.println(pre_temp); Serial.println(post_temp);
  Radio.sendDataPacket(pre_temp, post_temp, (uint8_t) 0);
}