#include <Arduino.h>

#include "Constants.h"

class ClockDivider {
   public:
    ClockDivider(const uint16_t clockDivision1, const uint16_t clockDivision2, const uint16_t clockDivision3, const uint16_t clockDivision4,
                 const uint16_t clockDivision5, const uint16_t clockDivision6, const uint16_t clockDivision7, const uint16_t clockDivision8)
        : m_clockDivisions{clockDivision1, clockDivision2, clockDivision3, clockDivision4, clockDivision5, clockDivision6, clockDivision7, clockDivision8} {
        resetOutputs();
    }

    void processIO();
    void resetOutputs();

   private:
    bool m_inputClockState{false};
    const uint16_t m_clockDivisions[numberOfOutputs]{};
    int16_t m_outputCounter[numberOfOutputs]{-1, -1, -1, -1, -1, -1, -1, -1};
};