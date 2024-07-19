#include "Inputs.h"

#include <Arduino.h>

uint16_t Inputs::getClockDivision(const uint8_t output) {
    return m_clockDivisions[output];
}

void Inputs::processClock() {
    for (uint8_t output = 0; output < numberOfOutputs; ++output) {
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

    // Debugging
    // Serial.print("output counters = ");

    // for (int16_t output : m_outputCounter) {
    //     Serial.print(output);
    //     Serial.print(" ");
    // }

    // Serial.print("  ");
    // Serial.print("clock divisions = ");

    // for (int16_t output : m_clockDivisions) {
    //     Serial.print(output);
    //     Serial.print(" ");
    // }

    // Serial.println();
}

void Inputs::processReset() {
    for (uint8_t output = 0; output < numberOfOutputs; ++output) {
        m_outputCounter[output] = -1;
        digitalWrite(outputPins[output], LOW);
    }

    // Debugging
    // Serial.print("reset interrupt = true");
    // Serial.print("   ");
    // Serial.print("output counters = ");

    // for (int16_t output : m_outputCounter) {
    //     Serial.print(output);
    //     Serial.print(" ");
    // }

    // Serial.println();
}