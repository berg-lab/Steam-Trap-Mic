#include "error.h"

void CError::raise_error(uint8_t error_code) {
    error_byte |= (1 << error_code);
}

void CError::clear_error(uint8_t error_code) {
    error_byte &= ~(1 << error_code);
}

uint8_t CError::get_error_byte() {
    return error_byte;
}