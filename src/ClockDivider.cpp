#include "ClockDivider.h"

#include <Arduino.h>

void ClockDivider::processIO() {
    m_inputClockState = !m_inputClockState;

    // All outputs are polled to change state
    for (uint8_t output = 0; output < numberOfOutputs; ++output) {
        processOutput(output);
    }
}

void ClockDivider::processOutput(const uint8_t output) {
    // Outputs that are multiplying the incoming clock signal lasts as long as the duration of the incoming clock signal
    if (m_clockDivisions[output] == 1) {
        digitalWrite(outputPins[output], m_inputClockState);
    }

    // Only the rising edges of the input clock signal are counted for divisions > 1
    // The output signal lasts for half the number of input clock trigs
    else if (m_clockDivisions[output] > 1 && m_inputClockState) {
        ++m_outputCounter[output];                            // Increase all counters
        m_outputCounter[output] %= m_clockDivisions[output];  // Start over if max is reached

        // Set LEDs on/off
        if (m_outputCounter[output] == 0) {
            digitalWrite(outputPins[output], HIGH);
        }

        // LEDs are unlit when the max number / 2 is reached (Example: 16 steps = LED unlits on step 9)
        else if (m_outputCounter[output] == m_clockDivisions[output] >> 1) {
            digitalWrite(outputPins[output], LOW);
        }
    }
}

void ClockDivider::resetOutputs() {
    for (uint8_t output = 0; output < numberOfOutputs; ++output) {
        m_outputCounter[output] = -1;
        digitalWrite(outputPins[output], LOW);
    }
}
