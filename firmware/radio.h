//=========================================================================================================
// radio.h - Defines a radio interface to the gateway
//=========================================================================================================
#ifndef _RADIO_H_
#define _RADIO_H_

#include <stdint.h>

class CRadio {
  public:
    void initializeRadio();
    void sendDataPacket(long pre_temp, uint8_t error_byte);
    void sendConfigPacket(int no_of_attempts);
    
  private:
    uint8_t transaction_id;
    void handleIncomingPacket(const unsigned char* raw);
    
    //HARDCODING FOR TESTING ONLY
    uint8_t   GATEWAY_ID = 1;
    uint16_t  NODE_ID    = 60; // 999 = node not configured; 1000 = node currently being configured (limit: 1023)
    uint8_t   NETWORK_ID = 10; // 99 = configuration network, 10 = sensor network (up to 255)

    char ENCRYPT_KEY[17] = "1234123412341234";
    char NODE_TYPE[4] = "STM";
};

#endif
//=========================================================================================================
