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
#define MAX_ADC                   4095
#define ACK_TIMEOUT               10

// Pin mapping -----------------------------------------------------
#define THERMISTOR_PIN_0          A0 
#define THERMISTOR_PIN_1          A1        
#define THERMISTORNOMINAL         10000    // resistance at 25 degrees C
#define TEMPERATURENOMINAL        25       // temp. for nominal resistance (almost always 25 C)
#define BCOEFFICIENT              3950     // The beta coefficient of the thermistor (usually 3000-4000)
#define SERIESRESISTOR            10000    // the value of the 'other' resistor
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



#endif