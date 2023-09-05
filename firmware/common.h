#ifndef _COMMON_H_
#define _COMMON_H_

// Define the current serial port ----------------------------------
#if defined (MOTEINO_M0) && defined (SERIAL_PORT_USBVIRTUAL)
  #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif

// Permanent globals -----------------------------------------------
#define FW_VERSION                1
#define TELEMETRY_VERSION         1
#define DEVICE_TYPE               2 // 1 denotes BORC, 2 denotes STM

// Global configuration constants ----------------------------------
#define SERIAL_BAUD               115200
#define MAX_VOLTAGE               5.0f
#define ACK_TIMEOUT               10

// Pin mapping -----------------------------------------------------
#define TEMP_PRE_PIN              A1
#define TEMP_POST_PIN             A2
#define POWER_PIN                 13
#define FLASH_SS                  23

// Error bits ------------------------------------------------------
#define BATT_ERR                  0   // battery low/bad voltage
#define TEMP_SENSE_ERR            1   // temp sensor not working
#define LED_DRV_ERR               2   // LED driver not working
#define CURRENT_SENSE_ERR         3   // current sensor not working
#define SERVO_POWER_ERR           4   // servo voltage not correct
#define FLASH_ERR                 5   // SPI flash error
#define RADIO_ERR                 6   // Radio error
#define SERVO_ERR                 7   // servo error (0 current or very high current)

// Macros ----------------------------------------------------------
// #define Secs_to_ms(x)             ((int) ((x) * 1000))
// #define Mins_to_ms(x)             ((int) ((x) * 1000 * 60))
#define 

#endif