//=========================================================================================================
// timer.h - Defines an interface to control RTC Zero timer
//=========================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include <RTCZero.h>

class CTimer {
    public:
        CTimer();
        void resetAlarm();
        bool timerExpired();
        void setTimer(byte seconds);

    private:
        void setupInterrupt();
        static void alarmMatch();
};

#endif
//=========================================================================================================

