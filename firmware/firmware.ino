#include "common.h"

#if defined (MOTEINO_M0) && defined(SERIAL_PORT_USBVIRTUAL)
    #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(115200);
  pinMode(MIC, INPUT);
  pinMode(POWER, OUTPUT);
  digitalWrite(POWER, HIGH);
  delay(1);
}

// the loop function runs over and over again forever
void loop() {
  float data[HISTORY_THRESHOLD];
  int counter = 0;
  float read_in;
  float min;
  float max;
  while (1) {
    // get raw analog reading from mic input
    read_in = analogRead (MIC);
    data[counter % HISTORY_THRESHOLD] = read_in;

    // check if data array is fully populated
    if (counter > HISTORY_THRESHOLD) {
        // discover min and max to calculate amplitude
        min = data[0];
        max = data[0];
        for (int i; i<HISTORY_THRESHOLD; i++) {
            if (data[i] < min) {
                min = data[i];
            }
            if (data[i] > max) {
                max = data[i];
            }
        }

        // determine whether valve is open or closed
        if (max - min > AMPLITUDE_THRESHOLD) {
            Serial.println(1);
        }
        else {
            Serial.println(0);
        }
    }
    counter++;
  }
  
}