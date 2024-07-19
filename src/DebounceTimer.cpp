#include "DebounceTimer.h"

#include <Arduino.h>

#include "Constants.h"

uint32_t DebounceTimer::getTimeStamp() {
    return m_timeStamp;
}

bool DebounceTimer::getTimerState() {
    return m_timerState;
}

void DebounceTimer::setTimeStamp() {
    m_timeStamp = millis();
}

void DebounceTimer::writeTimerState(const bool state) {
    m_timerState = state;
}