#include <iostream>
#include "morseSystem.hpp"

void MorseSystem::process()
{
    std::string phraseToTranslate {""};
    std::string translatedPhrase {""};
    
    // Continuously try to grab phrase to translate from user or quit on Ctrl+Z
    std::cout << "Enter a phrase to translate to morse code or press Ctrl+Z to stop..." << std::endl;
    while (std::getline(std::cin, phraseToTranslate))
    {
        // Translate phrase from english to morse code
        translate(phraseToTranslate, translatedPhrase);

        // Show converted morse code in terminal and on LEDs
        displayMorse(translatedPhrase);

        // Prompt for another phrase
        std::cout << "Enter a phrase to translate to morse code or press Ctrl+Z to stop..." << std::endl;
    }
}

void MorseSystem::translate(const std::string EnglishPhrase, std::string &output)
{
    output = ""; // Clear output string
    bool previousWasLetter {false};
    for (char c : EnglishPhrase)
    {
        // Handle spaces in english phrase first
        if (c == ' ')
        {
            if (previousWasLetter)
            {
                output += InterWordGapMorse;
                previousWasLetter = false;
            }
            continue;
        }

        // Cast to uppercase and check if character is valid
        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        if (CharToMorse.find(c) == CharToMorse.end())
        {
            std::cout << "Invalid character will be skipped: " << c  << std::endl;
            continue;
        }

        // Add character gap between letters before appending the next translation
        if (previousWasLetter)
        {
            output += InterCharGapMorse;
        }

        // Append morse code to output
        output += CharToMorse.at(c);
        previousWasLetter = true;
    }
}

void MorseSystem::displayMorse(const std::string MorseCodePhrase)
{
    // Iterate through morse code phrase and handle each character
    for (char c: MorseCodePhrase)
    {
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
                std::cout << "Invalid character, unable to displayMorse: " << c << std::endl;
                break;
        }
    }
    std::cout << std::endl;
}

void MorseSystem::setLed(const bool State)
{
    // todo: Connect hardware
}

void MorseSystem::dotMorseHandler()
{
    // Output dot to terminal and turn LED on for dot amount of time
    std::cout << DotMorse << std::flush;
    setLed(true);
    dotDelay();
    setLed(false);
    intraCharDelay();
}

void MorseSystem::dashMorseHandler()
{
    // Output dash to terminal and turn LED on for dash amount of time
    std::cout << DashMorse << std::flush;
    setLed(true);
    dashDelay();
    setLed(false);
    intraCharDelay();
}

void MorseSystem::interCharGapMorseHandler()
{
    // Output inter character gap to terminal and turn LED off for inter character amount of time
    std::cout << InterCharGapMorse << std::flush;
    setLed(false);
    interCharDelay();
}

void MorseSystem::interWordGapMorseHandler()
{
    // Output inter word gap to terminal and turn LED off for inter word amount of time
    std::cout << InterWordGapEnglish_str << std::flush;
    setLed(false);
    interWordDelay();
}