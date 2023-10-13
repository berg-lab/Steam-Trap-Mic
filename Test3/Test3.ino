// Written by Eduardo Calix-Ortiz
// Code based on:
// - Node.ino from RFM69/Examples/Node/Node.ino
// - Struct_send.ino from RFM69/Examples/Struct_send/Struct_send.ino
// - lcdthermocouple.ino from adafruit/MAX6675-library/examples/lcdthermocouple/lcdthermocouple.ino
// Github Repos:
// - https://github.com/LowPowerLab/RFM69
// - https://github.com/RobTillaart/MAX6675

// Define the current serial port ----------------------------------
#if defined (MOTEINO_M0) && defined (SERIAL_PORT_USBVIRTUAL)
    #define Serial SERIAL_PORT_USBVIRTUAL // Required for Serial on Zero based boards
#endif

//---------Libraries---------
// #include "error.h"
#include "max6675.h"    // Thermal Couple
//#include <GyverMAX6675_SPI.h>
#include <RFM69.h>      // Radio
#include <RFM69_ATC.h>
#include <SPIFlash.h>

// Permanent globals -----------------------------------------------
#define FW_VERSION                1
#define TELEMETRY_VERSION         1
#define DEVICE_TYPE               2 // 1 denotes BORC, 2 denotes STM

//---------Radio Parameters---------
#define NODE_ID         60 // 999 = node not configured; 1000 = node currently being configured (limit: 1023)
#define NETWORK_ID      10 // 99 = configuration network, 10 = sensor network (up to 255)
#define GATEWAY_ID      1  // "central" node
#define RADIO_FREQ       RF69_915MHZ // other freqs are RF69_433MHZ, RF69_868MHZ, or FREQUENCY_EXACT (in Hz)
#define ENCRYPT_KEY     "1234123412341234"
// #define IS_RFM69HW_HCW  //uncomment only for RFM69HW/HCW! Leave out if you have RFM69W/CW!
#define NODE_TYPE       "STM" // Special for our use STM=Steam Trap Monitor

#define TEMP_PRE_PIN    A1
#define TEMP_POST_PIN   A2
#define SERIAL_BAUD     115200

// Error bits ------------------------------------------------------
#define BATT_ERR                  0   // battery low/bad voltage
#define TEMP_SENSE_ERR            1   // temp sensor not working
#define LED_DRV_ERR               2   // LED driver not working
#define CURRENT_SENSE_ERR         3   // current sensor not working
#define SERVO_POWER_ERR           4   // servo voltage not correct
#define FLASH_ERR                 5   // SPI flash error
#define RADIO_ERR                 6   // Radio error
#define SERVO_ERR                 7   // servo error (0 current or very high current)

// #define ENABLE_ATC      //comment out this line to disable AUTO TRANSMISSION CONTROL
#define ATC_RSSI        -80

int TRANSMITPERIOD = 1000; //transmit a packet to gateway so often (in ms)
byte sendSize=0;
boolean requestACK = false;
SPIFlash flash(SS_FLASHMEM, 0xEF30); //EF30 for 4mbit  Windbond chip (W25X40CL)

#ifdef ENABLE_ATC
    RFM69_ATC radio;
#else
    RFM69 radio;
#endif

// Define radio communication variables
// #define WITHRFM69

//---------Thermal Couplers Parameters---------
// specifying MAX Software SPI pins
// #define thermoDO  4
// #define thermoCS  5
// #define thermoCLK 6
// const uint8_t thermoDO = 4;
// const uint8_t thermoCS = 5;
// const uint8_t thermoCLK = 6;

// specifying MAX Hardware SPI pin
#define preSO     6
#define preCS     5
#define preSCK    4
#define vccPin    3
#define gndPin    2

// Specify size of historical array
#define n         10

#define CONFIG_PACKET    0
#define TELEMETRY_PACKET 1
#define RESPONSE_PACKET  2

// maps a structure onto a buffer named "raw"
#define map_struct(t,m) t& m=*(t*)raw

// Cursors to replace next item in array
int pre_temp_cursor = 0;
int post_temp_cursor = 0;

int transaction_id;

// Structure Definition
typedef struct
{
    uint8_t     pkt_type;
    uint8_t     version;
    uint8_t     device_type;
    uint16_t    firmware_version;
    uint8_t     uid[8];
} device_config_t;

typedef struct 
{
    uint8_t     pkt_type;
    uint8_t     version;
    int         hist_size = n;
    float       pre_temp_reading[n];
    float       post_temp_reading[n];
    bool        is_working;
    uint8_t     error_byte;
    uint8_t     transaction_id;
} Payload;

// CError Error;
Payload theData;

// Creating thermal couple instances
MAX6675 PreCouple(preSCK, preCS, preSO);
//GyverMAX6675_SPI<preCS> PreCouple;

void setup() {
    Serial.begin(SERIAL_BAUD);
    delay(3000);
    Serial.println("Serial Initialized!");
    radio.initialize(RADIO_FREQ,NODE_ID,NETWORK_ID);
    Serial.println("Radio Initialized!");

    #ifdef IS_RFM69HW_HCW
        radio.setHighPower(); //must include this only for RFM69HW/HCW!
    #endif

    #ifdef ENCRYPT_KEY
        radio.encrypt(ENCRYPT_KEY);
    #endif

    #ifdef FREQUENCY_EXACT
        radio.setFrequency(RADIO_FREQ_EXACT); //set frequency to some custom frequency
    #endif

    #ifdef ENABLE_ATC
        radio.enableAutoPower(ATC_RSSI);
    #endif
    char buff[50];
    sprintf(buff, "\nTransmitting at %d Mhz...", RADIO_FREQ==RF69_433MHZ ? 433 : RADIO_FREQ==RF69_868MHZ ? 868 : 915);
    Serial.println(buff);

    if (flash.initialize())
    {
        Serial.print("SPI Flash Init OK ... UniqueID (MAC): ");
        flash.readUniqueId();
        for (byte i=0;i<8;i++)
        {
            Serial.print(flash.UNIQUEID[i], HEX);
            Serial.print(' ');
        }
        Serial.println();
    }
    else Serial.println("SPI Flash MEM not found (is chip soldered?)...");

    #ifdef ENABLE_ATC
        Serial.println("RFM69_ATC Enabled (Auto Transmission Control)\n");
    #endif

    //****************** Sending Config packet ********************
    device_config_t device_config;
    device_config.pkt_type          = CONFIG_PACKET;
    device_config.device_type       = DEVICE_TYPE;
    device_config.version           = TELEMETRY_VERSION;
    device_config.firmware_version  = FW_VERSION;
    radio.send(GATEWAY_ID, &device_config, sizeof(device_config));

    //******************** powering the MAX chips ********************
    pinMode(vccPin, OUTPUT); digitalWrite(vccPin, HIGH);
    pinMode(gndPin, OUTPUT); digitalWrite(gndPin, LOW);
    // wait for MAX chips to stabilize
    delay(500);
    // begin thermal couple
    // PreCouple.begin(preCS);
}

void loop() {
    // Moving average
    const float mov_avg_alpha = 0.1;
    static float mov_avg = -100;
    double value;
    Blink(220);
    
    // Filling the history
    theData.pre_temp_reading[pre_temp_cursor] = PreCouple.readCelsius();
    if (mov_avg == -100) mov_avg = theData.pre_temp_reading[pre_temp_cursor];
    mov_avg = mov_avg_alpha * theData.pre_temp_reading[pre_temp_cursor] + (1-mov_avg_alpha)*mov_avg;

    //Send info
    radio.send(GATEWAY_ID, &theData, sizeof(theData));

    Serial.print(theData.pre_temp_reading[pre_temp_cursor]);
    Serial.print("\t");
    Serial.print(mov_avg);
    Serial.println();

    // Assigning the moving avg as temp
    theData.pre_temp_reading[pre_temp_cursor] = mov_avg;
    
    // Updating the cursor
    if (pre_temp_cursor == n) pre_temp_cursor = 0;
    else pre_temp_cursor++;
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

//void initializeRadio()
//{
//    #ifdef WITHRFM69
//        // if hardware permits, try radio object initialization
//        if (!radio.initialize(RADIO_FREQ, NODE_ID, NETWORK_ID))
//            Error.raise_error(RADIO_ERR);
//        else
//            Error.clear_error(RADIO_ERR);
//            Serial.println("Radio initialized!");
//
//        // if hardware permits, try setting high power
//        #ifdef IS_RFM69HW
//            radio.setHighPower(); //uncomment only for RFM69HW!
//        #endif
//    #endif
//
//    // assign encription key to radio object for later transmission
//    radio.encrypt(ENCRYPT_KEY);
//    radio.sleep();
//
//    // start the transaction id at 1
//    transaction_id = 1;
//}

//void sendConfigPacket(int no_of_attempts)
//{
//    device_config_t device_config;
//    bool success = false;
//
//    // Fill in the node config details in the telemetry packet
//    device_config.pkt_type          = CONFIG_PACKET;
//    device_config.device_type       = DEVICE_TYPE;
//    device_config.version           = TELEMETRY_VERSION;
//    device_config.firmware_version  = FW_VERSION;
//    
//    // Attempt to send a packet to the gateway 3 times and wait for response
//    for (int attempt = 0; attempt < no_of_attempts; ++attempt)
//    {
//        // send the prepared config packet
//        radio.send(GATEWAY_ID, &device_config, sizeof(device_config));
//
//        // blink slow to show packet sent
//        for (int x=0; x<10; x++) {
//            digitalWrite(LED_BUILTIN, HIGH);
//            delay(250);
//            digitalWrite(LED_BUILTIN, LOW);
//            delay(250);
//            // Serial.print("Blinkie #: ");
//            // Serial.print(attempt*10+x);
//            // Serial.print("\n");
//        }
//        Serial.println(attempt);
//    }
//}

//void sendDataPacket(long pre_temp, long post_temp, bool is_working, uint8_t error_byte)
//{
//    // bool success = false;
//    //********************* Struc_send.ino example *********************
//    Serial.print("Sending struct (");
//    Serial.print(sizeof(theData));
//    Serial.print(" bytes) ... ");
//    if (radio.sendWithRetry(GATEWAY_ID, (const void*)(&theData), sizeof(theData)))
//        Serial.print(" ok!");
//    else Serial.print(" nothing...");
//    Serial.println();
//    Blink(LED_BUILTIN,3);
//}
