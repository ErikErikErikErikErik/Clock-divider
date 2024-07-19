#include <Arduino.h>

#include "Constants.h"

class Inputs {
   public:
    Inputs(const uint16_t (&clockDivisions)[numberOfOutputs])
        : m_clockDivisions{clockDivisions[0],
                           clockDivisions[1],
                           clockDivisions[2],
                           clockDivisions[3],
                           clockDivisions[4],
                           clockDivisions[5],
                           clockDivisions[6],
                           clockDivisions[7]} {
        processReset();
    }

    uint16_t getClockDivision(const uint8_t output);
    void processClock();
    void processReset();

   private:
    const uint16_t m_clockDivisions[numberOfOutputs]{};
    int16_t m_outputCounter[numberOfOutputs]{-1, -1, -1, -1, -1, -1, -1, -1};
};