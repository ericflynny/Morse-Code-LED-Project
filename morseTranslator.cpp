#include <string>
#include <iostream>
#include <chrono>
#include <thread>
#include "morseTranslator.hpp"

void MorseTranslator::process()
{
    std::string phraseToTranslate {""};
    std::string translatedPhrase {""};
    
    // Continuously try to grab phrase to translate from user or quit on Ctrl+Z
    std::cout << "Enter a phrase to translate to morse code or press Ctrl+Z to stop..." << std::endl;
    while (std::getline(std::cin, phraseToTranslate))
    {
        // Translate phrase and display
        translate(phraseToTranslate, translatedPhrase);
        display(translatedPhrase);

        // Prompt for another phrase
        std::cout << "Enter a phrase to translate to morse code or press Ctrl+Z to stop..." << std::endl;
    }
}

void MorseTranslator::translate(const std::string EnglishPhrase, std::string &output)
{    
    // Clear output
    output = "";
    bool previousWasLetter {false};

    std::cout << "Phrase to translate: " << EnglishPhrase << std::endl;
    for (char c : EnglishPhrase)
    {
        // Handle word separators first
        if (c == ' ')
        {
            if (previousWasLetter)
            {
                output += InterWordGap;
                previousWasLetter = false;
            }
            continue;
        }

        c = static_cast<char>(std::toupper(static_cast<unsigned char>(c))); // Safely cast to upper
        if (LetterToCode.find(c) == LetterToCode.end())
        {
            std::cout << "Invalid character entered: " << c << std::endl;
            continue;
        }

        // Add character gap between letters before appending the next symbol
        if (previousWasLetter)
        {
            output += InterCharGap;
        }

        // Append morse code to output
        output += LetterToCode.at(c);
        previousWasLetter = true;
    }
}

void MorseTranslator::display(const std::string MorseCodePhrase)
{
    // Iterate through each letter and either play the dot or dash
    for (char c: MorseCodePhrase)
    {
        switch (c)
        {
            case Dot:
                playDot();
                break;
            case Dash:
                playDash();
                break;
            case ' ':
                playLetterGap();
                break;
            case '/':
                playWordGap();
                break;
            default:
                std::cout << "Invalid character, unable to display: " << c << std::endl;
                break;
        }
    }
    std::cout << std::endl;
}

void MorseTranslator::sleep(const std::chrono::milliseconds TimeToSleepFor)
{
    std::this_thread::sleep_for(TimeToSleepFor);
}

void MorseTranslator::setLed(const bool State)
{
    // std::cout << "Turning LED " << (State ? "ON" : "OFF") << "..." << std::endl;

    // todo: Connect hardware
}

void MorseTranslator::playDot()
{
    std::cout << Dot << std::flush;
    setLed(true);
    sleep(TimeUnit_ms * DotDuration);
    setLed(false);
    sleep(TimeUnit_ms * IntraCharGapDuration);
}

void MorseTranslator::playDash()
{
    std::cout << Dash << std::flush;
    setLed(true);
    sleep(TimeUnit_ms * DashDuration);
    setLed(false);
    sleep(TimeUnit_ms * IntraCharGapDuration);
}

void MorseTranslator::playLetterGap()
{
    std::cout << ' ' << std::flush;
    setLed(false);
    sleep(TimeUnit_ms * InterCharGapDuration);
}

void MorseTranslator::playWordGap()
{
    std::cout << "  " << std::flush;
    setLed(false);
    sleep(TimeUnit_ms * InterWordGapDuration);
}