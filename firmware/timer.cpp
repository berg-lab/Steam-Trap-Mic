#include "timer.h"

RTCZero rtc;
volatile bool alarm_flag;

CTimer::CTimer(void) {
    alarm_flag = false;
    rtc.begin();
    setupInterrupt();
}

void CTimer::resetAlarm(void) {
    alarm_flag = false;
}

bool CTimer::timerExpired(void) {
    return alarm_flag;
}

void CTimer::setTimer(byte seconds) {
    rtc.setTime(0, 0, 0);
    rtc.setDate(1, 1, 1);
    rtc.setAlarmTime(0, 0, seconds);
    rtc.enableAlarm(rtc.MATCH_HHMMSS);
}

void CTimer::setupInterrupt(void) {
    rtc.attachInterrupt(CTimer::alarmMatch);
}

void CTimer::alarmMatch(void) {
    alarm_flag = true;
}
