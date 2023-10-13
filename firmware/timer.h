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
        // Set how often alarm goes off here
        const byte alarmSeconds = 3;
        const byte alarmMinutes = 0;
        const byte alarmHours = 0;
        // Set initial state (false=Awake)
        volatile bool alarmFlag;
        RTCZero rtc;
};

#endif
//=========================================================================================================

