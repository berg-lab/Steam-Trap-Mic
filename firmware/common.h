#ifndef _COMMON_H_

#define _COMMON_H_
#include <stdint.h>

// Define the current serial port
#if defined (MOTEINO_M0) && defined(SERIAL_PORT_USBVIRTUAL)
  #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif

// Misc. global variables ------------------------------------------
#define SERIAL_BAUD               115200
#define HISTORY_THRESHOLD         128
#define AMPLITUDE_THRESHOLD       0.35f
#define VOLTAGE_REF               3.3f

// Pin mapping -----------------------------------------------------
#define MIC                       A4
#define BLUE_PIN                  10
#define GREEN_PIN                 11
#define RED_PIN                   12
#define POWER_PIN                 13
#define FLASH_SS                  23

#endif
