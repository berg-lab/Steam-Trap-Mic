#include "timer.h"

volatile bool alarmFlag;

CTimer::CTimer(void) {
    alarmFlag = false; // Set initial state (false=Awake)
    rtc.begin();
    setupInterrupt();
}

void CTimer::clearFlag(void) {
    alarmFlag = false;
}

bool CTimer::timerExpired(void) {
    return alarmFlag;
}

void CTimer::setTimer(byte seconds, byte minutes, byte hours) 
{
    rtc.setTime(0, 0, 0);
    rtc.setDate(1, 1, 1);
    rtc.setAlarmTime(hours, minutes, seconds);
    rtc.enableAlarm(rtc.MATCH_HHMMSS);
}

void CTimer::setupInterrupt(void) {
    rtc.attachInterrupt(CTimer::alarmMatch);
}

void CTimer::alarmMatch(void) {
    alarmFlag = true;
}

void CTimer::goSleep(void) {
    rtc.standbyMode();
}