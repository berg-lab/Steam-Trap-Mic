#include "common.h"

#if defined (MOTEINO_M0) && defined(SERIAL_PORT_USBVIRTUAL)
    #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(MIC, INPUT);
}

// the loop function runs over and over again forever
void loop() {
  float vin = analogRead (MIC);
  Serial.println(vin);
}