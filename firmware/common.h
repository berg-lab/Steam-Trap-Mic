#ifndef _COMMON_H_
#define _COMMON_H_

// Define the current serial port
#if defined (MOTEINO_M0) && defined (SERIAL_PORT_USBVIRTUAL)
  #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif

// Misc. global constants ------------------------------------------
#define FW_VERSION                1
#define SERIAL_BAUD               115200
#define READING_DELAY             0.05f
#define TRIAL_DELAY               60
#define HISTORY_THRESHOLD         128
#define NUM_TUNING_TRIALS         5  
#define NUM_TUNING_SAMPLES        128          
#define TMP_AMPLITUDE_THRESHOLD   0.35f
#define MAX_VOLTAGE               5.0f
#define ACK_TIMEOUT               10

// Pin mapping -----------------------------------------------------
#define MIC                       A4
#define POWER_PIN                 13
#define FLASH_SS                  23

// Error bytes -----------------------------------------------------
#define BATT_ERR                  0   // battery low/bad voltage
#define TEMP_SENSE_ERR            1   // temp sensor not working
#define LED_DRV_ERR               2   // LED driver not working
#define CURRENT_SENSE_ERR         3   // current sensor not working
#define SERVO_POWER_ERR           4   // servo voltage not correct
#define FLASH_ERR                 5   // SPI flash error
#define RADIO_ERR                 6   // Radio error
#define SERVO_ERR                 7   // servo error (0 current or very high current)

#endif
