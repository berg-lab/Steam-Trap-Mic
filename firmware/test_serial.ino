#include "common.h"

#if defined (MOTEINO_M0) && defined(SERIAL_PORT_USBVIRTUAL)
    #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif

// the setup function runs once when you press reset or power the board
// void setup() {
//   Serial.begin(115200);
//   pinMode(MIC, INPUT);
//   pinMode(POWER, OUTPUT);
//   digitalWrite(POWER, HIGH);
//   delay(1);
// }

// // the loop function runs over and over again forever
// void loop() {
//   float read_in = analogRead (MIC);
//   // scale the result and apply to voltage ref
//   float voltage = (read_in / 1024.0) * VOLTAGE_REF;
//   // send the true value over serial
//   Serial.println(voltage);
// }