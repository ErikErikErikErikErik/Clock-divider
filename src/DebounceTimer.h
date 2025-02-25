#ifndef DEBOUNCETIMER_H
#define DEBOUNCETIMER_H

#include <Arduino.h>

class DebounceTimer {
   public:
    DebounceTimer(const uint32_t debounceTime) {
        m_timeStamp = 0;
        m_debounceTime = debounceTime;
        m_timerState = false;
    };

    bool debounceTimerIsActive();
    bool debounceTimeHasElapsed();
    void activateTimer();
    void deactivateTimer();

   private:
    uint32_t m_timeStamp;
    uint32_t m_debounceTime;
    bool m_timerState;
};

#endif