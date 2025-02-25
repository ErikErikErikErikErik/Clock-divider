#include <Arduino.h>

#include "Constants.h"

extern volatile bool clockInterrupt;
extern volatile bool resetInterrupt;

class ClockDivider {
   public:
    ClockDivider(const uint16_t clockDivision1, const uint16_t clockDivision2, const uint16_t clockDivision3, const uint16_t clockDivision4,
                 const uint16_t clockDivision5, const uint16_t clockDivision6, const uint16_t clockDivision7, const uint16_t clockDivision8)
        : m_clockDivisions{clockDivision1, clockDivision2, clockDivision3, clockDivision4, clockDivision5, clockDivision6, clockDivision7, clockDivision8} {
        // In order to clear outputs when powering up the module, the interrupt variables needs to be set to false when initializing the ClockDivider object
        clockInterrupt = false;
        resetInterrupt = false;
    }

    void processIO();
    void processReset();

   private:
    bool m_inputClockState{false};
    bool m_resetState{false};
    const uint16_t m_clockDivisions[numberOfOutputs]{};
    int16_t m_outputCounter[numberOfOutputs]{-1, -1, -1, -1, -1, -1, -1, -1};
};