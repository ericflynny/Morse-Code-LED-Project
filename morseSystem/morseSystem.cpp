#include "morseSystem.hpp"


const char* MorseSystem::getMorseCode(const char C)
{
    // Return morse code conversion of english character or nullptr if invalid
    switch (C)
    {
        case 'A':return ".-";
        case 'B': return "-...";
        case 'C': return "-.-.";
        case 'D': return "-..";
        case 'E': return ".";
        case 'F': return "..-.";
        case 'G': return "--.";
        case 'H': return "....";
        case 'I': return "..";
        case 'J': return ".---";
        case 'K': return "-.-";
        case 'L': return ".-..";
        case 'M': return "--";
        case 'N': return "-.";
        case 'O': return "---";
        case 'P': return ".--.";
        case 'Q': return "--.-";
        case 'R': return ".-.";
        case 'S': return "...";
        case 'T': return "-";
        case 'U': return "..-";
        case 'V': return "...-";
        case 'W': return ".--";
        case 'X': return "-..-";
        case 'Y': return "-.--";
        case 'Z': return "--..";
        default:  return nullptr;
    }
}

void MorseSystem::init()
{
    // Set LED to output mode and off
    pinMode(LedPin, OUTPUT);
    setLed(false);
}

void MorseSystem::process()
{
    // Continuously try to grab phrase to translate from user or quit on Ctrl+Z/exit
    while (true)
    {
        // Wait for user input
        Serial.println("\nEnter a phrase to translate (Send Ctrl+Z or 'exit' to stop):");
        while (Serial.available() == 0) { }
        String phraseToTranslate = Serial.readStringUntil('\n');
        phraseToTranslate.trim();

        // Verify input is valid
        if (phraseToTranslate.length() == 0)
        {
            continue; // Empty input
        }
        // todo: Ctrl-Z or exit
        else if ((phraseToTranslate.indexOf((char)26) != -1) ||
                 phraseToTranslate.equalsIgnoreCase("^Z") ||
                 phraseToTranslate.equalsIgnoreCase("Ctrl-Z") ||
                 phraseToTranslate.equalsIgnoreCase("Ctrl+Z") ||
                 phraseToTranslate.equalsIgnoreCase("exit"))
        {
            Serial.println("\nExiting now...");
            break;
        }

        // Translate from English to Morse code
        Serial.print("Phrase to translate: ");
        Serial.println(phraseToTranslate);
        String translatedPhrase {""};
        translate(phraseToTranslate, translatedPhrase);

        // Show converted morse code in terminal and on LEDs
        displayMorse(translatedPhrase);
    }
}

void MorseSystem::translate(const String &EnglishPhrase, String &output)
{
    output = ""; // Clear output string
    bool previousWasLetter {false};

    for (unsigned int i = 0; i < EnglishPhrase.length(); ++i)
    {
        char c {EnglishPhrase[i]};

        // Handle spaces between words
        if (c == ' ')
        {
            if (previousWasLetter)
            {
                output += InterWordGapMorse;
                previousWasLetter = false;
            }
            continue;
        }

        // Look up english character and convert to Morse code
        c = toupper(c);
        const char * const Morse {getMorseCode(c)};

        // Verify character is valid
        if (Morse == nullptr)
        {
            Serial.print("Invalid character skipped: ");
            Serial.println(c);
            continue;
        }

        // Add valid character gap between letters
        if (previousWasLetter)
        {
            output += InterCharGapMorse;
        }

        // Append morse code to output
        output += Morse;
        previousWasLetter = true;
    }
}

void MorseSystem::displayMorse(const String &MorseCodePhrase)
{
    // Iterate through morse code phrase and handle each character
    for (unsigned int i = 0; i < MorseCodePhrase.length(); ++i)
    {
        char c = MorseCodePhrase[i];
        switch (c)
        {
            case DotMorse:
                dotMorseHandler();
                break;
            case DashMorse:
                dashMorseHandler();
                break;
            case InterCharGapMorse:
                interCharGapMorseHandler();
                break;
            case InterWordGapMorse:
                interWordGapMorseHandler();
                break;
            default:
                Serial.print("Invalid character, unable to display: ");
                Serial.println(c);
                break;
        }
    }
    Serial.println();
}

void MorseSystem::setLed(const bool State)
{
    digitalWrite(LedPin, State ? HIGH : LOW);
}

void MorseSystem::dotMorseHandler()
{
    // Output dot to serial and turn LED on for dot amount of time
    Serial.print(DotMorse);
    setLed(true);
    dotDelay();
    setLed(false);
    intraCharDelay();
}

void MorseSystem::dashMorseHandler()
{
    // Output dash to serial and turn LED on for dash amount of time
    Serial.print(DashMorse);
    setLed(true);
    dashDelay();
    setLed(false);
    intraCharDelay();
}

void MorseSystem::interCharGapMorseHandler()
{
    // Output inter character gap to serial and turn LED off for inter character amount of time
    Serial.print(InterCharGapMorse);
    setLed(false);
    interCharDelay();
}

void MorseSystem::interWordGapMorseHandler()
{
    // Output inter word gap to serial and turn LED off for inter word amount of time
    Serial.print(InterWordGapEnglish_str);
    setLed(false);
    interWordDelay();
}