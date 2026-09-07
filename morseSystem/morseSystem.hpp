#pragma once
#include <Arduino.h>

class MorseSystem
{
public:
    MorseSystem() = default;
    void init();
    void process();

private:
    // Arduino LED Pin
    static constexpr uint8_t LedPin {LED_BUILTIN};

    // Timing Multipliers
    static constexpr unsigned int DotDuration          {1}; // One unit of time for dots
    static constexpr unsigned int DashDuration         {3}; // Three units of time for dashes
    static constexpr unsigned int IntraCharGapDuration {1}; // One unit of time between dots and dashes
    static constexpr unsigned int InterCharGapDuration {2}; // Two units of time between letters
    static constexpr unsigned int InterWordGapDuration {6}; // Six units of time between words
    static constexpr unsigned long TimeUnit_ms         {132}; // ~12 words per min, base unit

    // Characters, spacing, and gaps
    static constexpr char DotMorse {'.'};
    static constexpr char DashMorse {'-'};
    static constexpr char InterCharGapMorse {' '};
    static constexpr char InterWordGapMorse {'/'};
    static const inline String InterWordGapEnglish_str {"  "};

    // Morse code lookup
    static const char* getMorseCode(char c);

    // Translate English string into Morse output string
    void translate(const String &EnglishPhrase, String &output);

    // Display Morse string in the Serial monitor and on the LED
    void displayMorse(const String &MorseCodePhrase);

    // Morse Code Handlers
    void dotMorseHandler();
    void dashMorseHandler();
    void interCharGapMorseHandler();
    void interWordGapMorseHandler();

    // Timing functions
    void sleep(unsigned long ms) { delay(ms); }
    void dotDelay()       { sleep(TimeUnit_ms * DotDuration); }
    void dashDelay()      { sleep(TimeUnit_ms * DashDuration); }
    void intraCharDelay() { sleep(TimeUnit_ms * IntraCharGapDuration); }
    void interCharDelay() { sleep(TimeUnit_ms * InterCharGapDuration); }
    void interWordDelay() { sleep(TimeUnit_ms * InterWordGapDuration); }

    // Hardware functions
    void setLed(const bool State);
};