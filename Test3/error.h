#ifndef _ERROR_H_
#define _ERROR_H_

#include <stdint.h>

class CError {
    public:
        void raise_error(uint8_t err_code);
        void clear_error(uint8_t err_code);
        uint8_t get_error_byte();
    
    private:
        uint8_t error_byte;
};

#endif