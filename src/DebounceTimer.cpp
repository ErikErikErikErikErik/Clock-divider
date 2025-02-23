#include "DebounceTimer.h"

#include <Arduino.h>

#include "Constants.h"

bool DebounceTimer::debounceTimerIsActive() {
    return m_timerState;
}

bool DebounceTimer::debounceTimeHasElapsed() {
    return micros() - m_timeStamp >= m_debounceTime;
};

void DebounceTimer::activateTimer() {
    m_timeStamp = micros();
    m_timerState = true;
}

void DebounceTimer::deactivateTimer() {
    m_timerState = false;
}