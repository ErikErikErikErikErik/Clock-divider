#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Arduino.h>

constexpr uint8_t numberOfOutputs{8};
constexpr uint8_t numberOfButtons{2};

// Pin numbers
constexpr uint8_t clock{2};
constexpr uint8_t reset{3};
constexpr uint8_t outputPins[numberOfOutputs]{4, 5, 6, 7, 8, 9, 10, 11};

#endif