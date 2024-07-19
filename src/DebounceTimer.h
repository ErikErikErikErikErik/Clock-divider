#ifndef DEBOUNCETIMER_H
#define DEBOUNCETIMER_H

#include <Arduino.h>

class DebounceTimer {
   public:
    DebounceTimer() = default;

    uint32_t getTimeStamp();
    bool getTimerState();

    void setTimeStamp();
    void writeTimerState(const bool state);

   private:
    uint32_t m_timeStamp;
    bool m_timerState;
};

#endif