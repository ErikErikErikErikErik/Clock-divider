#include <Arduino.h>

#include "Constants.h"
#include "DebounceTimer.h"
#include "Inputs.h"

volatile bool clockInterrupt{};
volatile bool resetInterrupt{};

void clockISR() {
    clockInterrupt = true;
}

void resetISR() {
    resetInterrupt = true;
}

void setup() {
    // Debugging
    // Serial.begin(115200);

    pinMode(clock, INPUT_PULLUP);
    pinMode(reset, INPUT_PULLUP);

    for (uint8_t outputPin : outputPins) {
        pinMode(outputPin, OUTPUT);
    }

    attachInterrupt(digitalPinToInterrupt(clock), clockISR, FALLING);
    attachInterrupt(digitalPinToInterrupt(reset), resetISR, FALLING);
}

void processInterrupt(Inputs& inputs, void (Inputs::*functionPointer)(), DebounceTimer& timer, volatile bool& interrupt) {
    // 1. processInterrupt() is called as soon as the interrupt turns TRUE
    // 2. The callback function is called
    // 3. The debounce timer activates
    if (timer.getTimerState() == false) {
        (inputs.*functionPointer)();

        timer.setTimeStamp();
        timer.writeTimerState(true);
    }

    // When the debounce time has elapsed, and
    // any outputs that are set to the same clock as the input (i.e. no divisions), the debounce timer is used to unlit the LED and set the output clock low
    // Lastly, the interrupt variable is set to FALSE in order to prepare for the next interrupt signal
    else if (millis() - timer.getTimeStamp() >= debounceTime) {
        timer.writeTimerState(false);

        for (uint8_t output = 0; output < numberOfOutputs; ++output) {
            if (inputs.getClockDivision(output) == 1) {
                digitalWrite(outputPins[output], LOW);
            }
        }

        interrupt = false;

        // Debugging
        // Serial.print("debounce time elapsed = ");
        // Serial.print(millis() - timer.getTimeStamp());
        // Serial.print("   ");
        // Serial.println();
    }
}

void loop() {
    static Inputs inputs(clockDivisions);  // clockDivisions are defined in Constants.h
    static DebounceTimer clockDebounceTimer;
    static DebounceTimer resetDebounceTimer;

    if (clockInterrupt == true) {
        void (Inputs::*clockFunctionPointer)(){&Inputs::processClock};

        processInterrupt(inputs, clockFunctionPointer, clockDebounceTimer, clockInterrupt);
    }

    if (resetInterrupt == true) {
        void (Inputs::*resetFunctionPointer)(){&Inputs::processReset};

        processInterrupt(inputs, resetFunctionPointer, resetDebounceTimer, resetInterrupt);
    }
}
