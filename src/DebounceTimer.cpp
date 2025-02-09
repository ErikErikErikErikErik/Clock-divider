#include "DebounceTimer.h"

#include <Arduino.h>

#include "Constants.h"

uint32_t DebounceTimer::getTimeStamp() {
    return m_timeStamp;
}

uint32_t DebounceTimer::getDebounceTime() {
    return m_debounceTime;
}

bool DebounceTimer::getDebounceTimerState() {
    return m_timerState;
}

void DebounceTimer::setTimeStamp() {
    m_timeStamp = micros();
}

void DebounceTimer::writeDebounceTimerState(const bool state) {
    m_timerState = state;
}