#include "timer.h"

CTimer::CTimer(void) {
    alarm_flag = false; // Set initial state (false=Awake)
    rtc.begin();
    setupInterrupt();
}

void CTimer::clearFlag(void) {
    alarm_flag = false;
}

bool CTimer::timerExpired(void) {
    return alarm_flag;
}

void CTimer::setTimer(
    byte seconds = 3,
    byte minutes = 0,
    byte hours = 0) 
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
    alarm_flag = true;
}

void CTimer::goSleep(void) {
    rtc.standbyMode();
}