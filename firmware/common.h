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
#define TEMPERATURE_PRE_CS_PIN    5 // PE CS Pin
#define TEMPERATURE_POWER_PIN     3 //temp - Software SPI
#define TEMPERATURE_GND_PIN       2 //temp - Software SPI
#define preSO                     6 //temp - Software SPI
#define preSCK                    4 //temp - Software SPI
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

// Specify size of historical array --------------------------------
#define ARRAY_LENGTH         10

#endif