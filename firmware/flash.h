#ifndef _FLASH_H_
#define _FLASH_H_

#include <SPIFlash.h>

class CFlash {
    public:
        void deviceSetup();

    private:
        // SPIFlash flash(FLASH_SS, 0xEF30); //EF30 for 4mbit  Windbond chip (W25X40CL)
        // bool spy = false; //set to 'true' to sniff all packets on the same network

};

#endif