#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include "common.h"
#include "radio.h"
#include "error.h"
#include "timer.h"
#include "SPIFlash.h"
#include "max6675.h"

extern CError   Error;
extern CRadio   Radio;
extern CTimer   Timer;
extern SPIFlash Flash;
extern MAX6675 PreCouple;

#endif