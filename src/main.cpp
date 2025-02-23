#include <Arduino.h>

#include "ClockDivider.h"
#include "Constants.h"
#include "DebounceTimer.h"

volatile bool clockInterrupt{};
volatile bool resetInterrupt{};

void clockISR() {
    clockInterrupt = true;
}

void resetISR() {
    resetInterrupt = true;
}

void setup() {
    //Serial.begin(115200);

    pinMode(clock, INPUT_PULLUP);
    pinMode(reset, INPUT_PULLUP);

    for (uint8_t outputPin : outputPins) {
        pinMode(outputPin, OUTPUT);
    }

    attachInterrupt(digitalPinToInterrupt(clock), clockISR, CHANGE);
    attachInterrupt(digitalPinToInterrupt(reset), resetISR, CHANGE);
}

void processInterrupt(ClockDivider& clockDivider, void (ClockDivider::*functionPointer)(), DebounceTimer& timer, volatile bool& interrupt) {
    if (timer.debounceTimerIsActive() == false) {  
        (clockDivider.*functionPointer)();         // The clock or reset function is called
        timer.activateTimer();
    }

    else if (timer.debounceTimeHasElapsed()) {     
        interrupt = false;                     // The interrupt variable is set to FALSE in order to prepare for the next interrupt signal
        timer.deactivateTimer();  
    }
}

void loop() {
    // CONFIGURE THE MODULE HERE
    // Set clock division values here for output 1 - 8
    // A value of 1 multiplies the incoming clock signal
    static ClockDivider clockDivider(64, 64, 64, 64, 64, 64, 64, 64);

    // Set debounce time (in microseconds) here, in case input readings are noisy
    // Typically, a debounce time of 20000 - 50000 us should be enough, if at all needed
    static DebounceTimer clockDebounceTimer(0);
    static DebounceTimer resetDebounceTimer(0);

    if (clockInterrupt == true) {
        void (ClockDivider::*clockFunctionPointer)(){&ClockDivider::processIO};
        processInterrupt(clockDivider, clockFunctionPointer, clockDebounceTimer, clockInterrupt);
    }

    if (resetInterrupt == true) {
        void (ClockDivider::*resetFunctionPointer)(){&ClockDivider::processReset};
        processInterrupt(clockDivider, resetFunctionPointer, resetDebounceTimer, resetInterrupt);
    }
}
