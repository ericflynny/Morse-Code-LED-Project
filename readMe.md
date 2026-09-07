# Morse Code LED and CLI Translator

Eric Flynn, September 7th, 2026

EN.605.715: Software Development For Real-Time Embedded Systems, Johns Hopkins University

## About
The following project will:
1. Prompt the user for a phrase via the command line
2. Translate the given phrase from English to Morse code
3. Display the translated morse code in the terminal using dots (.) and dashes (-)
4. Display the translated morse code via the connected LEDs
5. Repeat steps 1-4 until the user enters `Ctrl+Z` or `Ctrl+C` to stop the program

## Requirements
1. Arduino connected to an LED

## Command To Build and Run with G++, C++17
`g++ -std=c++17 *.cpp -o main && ./main`