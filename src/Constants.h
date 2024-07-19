#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

// Pin numbers
constexpr uint8_t clock{2};
constexpr uint8_t reset{3};
constexpr uint8_t outputPins[numberOfOutputs]{4, 5, 6, 7, 8, 9, 10, 11};

constexpr uint8_t numberOfOutputs{8};
constexpr uint8_t numberOfButtons{2};

// Adjust debounce time here if needed (ms)
constexpr uint8_t debounceTime{0};

// Set clock divisions here
// A value of 1 will simply multiply the incoming signal
constexpr uint16_t clockDivisions[numberOfOutputs]{64, 64, 64, 64, 64, 64, 64, 64};

#endif