#include "ClockDivider.h"

#include <Arduino.h>

void ClockDivider::processIO() {
    // For every interrupt change, the input clock state is toggled
    m_inputClockState = !m_inputClockState;

    for (uint8_t output = 0; output < numberOfOutputs; ++output) {
        // Outputs that are duplicating the incoming clock signal follows the same HIGH/LOW cycle
        if (m_clockDivisions[output] == 1) {
            digitalWrite(outputPins[output], m_inputClockState);
        }

        // Only the rising edges of the input clock signal are counted for divisions > 1
        // The output signal lasts for half the number of input clock trigs
        else if (m_clockDivisions[output] > 1 && m_inputClockState) {
            ++m_outputCounter[output];                            // Increase all counters
            m_outputCounter[output] %= m_clockDivisions[output];  // Start over if max is reached

            // Set clock outputs and LEDs HIGH
            if (m_outputCounter[output] == 0) {
                digitalWrite(outputPins[output], HIGH);
            }

            // Clock outputs and LEDs goes LOW when the max number / 2 is reached (Example: 16 steps = LED unlits on step 9)
            else if (m_outputCounter[output] == m_clockDivisions[output] >> 1) {
                digitalWrite(outputPins[output], LOW);
            }
        }
    }
}

void ClockDivider::processReset() {
    // For every interrupt change, the reset state is toggled
    m_resetState = !m_resetState;

    // Outputs are only reset when the button is pressed, not released
    if (m_resetState) {
        for (uint8_t output = 0; output < numberOfOutputs; ++output) {
            m_outputCounter[output] = -1;
            digitalWrite(outputPins[output], LOW);
        }
    }
}