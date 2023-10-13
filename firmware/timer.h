//=========================================================================================================
// timer.h - Defines an interface to control RTC Zero timer
//=========================================================================================================
#ifndef _TIMER_H_
#define _TIMER_H_
#include <RTCZero.h>

class CTimer {
    public:
        CTimer();
        void clearFlag();
        bool timerExpired();
        void setTimer(byte seconds, byte minutes, byte hours);
        void goSleep();

    private:
        void setupInterrupt();
        static void alarmMatch();
        volatile bool alarmFlag;
        RTCZero rtc;
};

#endif
//=========================================================================================================

