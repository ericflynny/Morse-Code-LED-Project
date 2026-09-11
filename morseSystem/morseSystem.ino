#include <Arduino.h>
#include "morseSystem.hpp"


void setup()
{
    // Setup serial port and wait for enumeration
    Serial.begin(9600);
    while (!Serial){ ; }

    // Setup and run Morse system
    MorseSystem morseSystem;
    morseSystem.init();
    morseSystem.process();

    Serial.println("System halted. Press Reset button on board to restart.");
}

void loop() { } // morseSystem.process() controls loop