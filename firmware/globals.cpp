#include "globals.h"

CError   Error;
CRadio   Radio;
CTimer   Timer;
SPIFlash Flash(FLASH_SS, 0xEF30);
MAX6675 PreCouple(preSCK, TEMPERATURE_PRE_CS_PIN, preSO);