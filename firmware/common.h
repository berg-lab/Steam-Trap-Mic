#ifndef _COMMON_H_

#define _COMMON_H_
#include <stdint.h>

// Define the current serial port
#if defined (MOTEINO_M0) && defined(SERIAL_PORT_USBVIRTUAL)
  #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif


// // Set to 1 for compiling on systems with very limited hardware
// #define NO_HW 0

// // system mode
// enum mode_t : uint8_t
// {
//     MANUAL_MODE   = 0,
//     MENU_MODE     = 1,
//     SETPOINT_MODE = 2
// };

// // servo calibration mode
// enum servocal_t : uint8_t
// {
//     NOTCAL = 0,
//     CAL = 1,
//     DONTCAL = 2
// };

// // radio packet type
// enum packet_type_t  : uint8_t
// {
//     CONFIG_PACKET       = 0,
//     TELEMETRY_PACKET    = 1,
//     RESPONSE_PACKET     = 2
// };

// Misc. global variables ------------------------------------------
#define SERIAL_BAUD               115200
#define HISTORY_THRESHOLD         128
#define AMPLITUDE_THRESHOLD       0.35f
#define VOLTAGE_REF               3.3f

// I2C Addresses ---------------------------------------------------

// #if NO_HW
//   #define CURRENT_SENSE_ADDRESS   0x40
//   #define TEMP_SENSE_ADDRESS      0x44
//   #define LED_MATRIX_ADDRESS      0x74
// #else
//   #define CURRENT_SENSE_ADDRESS   0x41  
//   #define TEMP_SENSE_ADDRESS      0x45  
//   #define LED_MATRIX_ADDRESS      0x74
// #endif


// Pin mapping -----------------------------------------------------
#define MIC                       A4
#define BLUE_PIN                  10
#define GREEN_PIN                 11
#define RED_PIN                   12
#define POWER_PIN                 13

// Define error code bits ------------------------------------------
// #define BATT_ERR                  (1 << 0)   // battery low/bad voltage
// #define TEMP_SENSE_ERR            (1 << 1)   // temp sensor not working
// #define LED_DRV_ERR               (1 << 2)   // LED driver not working
// #define CURRENT_SENSE_ERR         (1 << 3)   // current sensor not working
// #define SERVO_POWER_ERR           (1 << 4)   // servo voltage not correct
// #define FLASH_ERR                 (1 << 5)   // SPI flash error
// #define RADIO_ERR                 (1 << 6)   // Radio error
// #define SERVO_ERR                 (1 << 7)   // servo error (didn't move)

#endif
