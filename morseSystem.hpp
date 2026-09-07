#include <string>
#include <chrono>
#include <thread>
#include <unordered_map>

class MorseSystem
{
    public:
        MorseSystem() {};
        void process();

    private:
        // Timing
        static constexpr unsigned int DotDuration  {1}; // One unit of time for dots
        static constexpr unsigned int DashDuration {2}; // Two units of time for dashes
        static constexpr unsigned int IntraCharGapDuration {2}; // One units of time between dots and dashes
        static constexpr unsigned int InterCharGapDuration {2}; // Two units of time between letters
        static constexpr unsigned int InterWordGapDuration {3}; // Three units of time between words
        static constexpr std::chrono::milliseconds TimeUnit_ms {132}; // Base unit, 132 ms = ~12 words per minute

        // Characters, spacing/gaps
        static constexpr char DotMorse {'.'};
        static constexpr char DashMorse {'-'};
        static constexpr char InterCharGapMorse {' '}; // One space between letters
        static constexpr char InterWordGapMorse {'/'}; // '/' Character between words
        static const inline std::string Dot_str {"."};
        static const inline std::string Dash_str {"-"};
        static const inline std::string IntraCharGapMorse_str {""};
        static const inline std::string InterWordGapEnglish_str {"  "};

        // Map characters to morse code
        static inline const std::unordered_map<char, std::string> CharToMorse
        {
            {'A', Dot_str + Dash_str},
            {'B', Dash_str + Dot_str + Dot_str + Dot_str},
            {'C', Dash_str + Dot_str + Dash_str + Dot_str},
            {'D', Dash_str + Dot_str + Dot_str},
            {'E', Dot_str},
            {'F', Dot_str + Dot_str + Dash_str + Dot_str},
            {'G', Dash_str + Dash_str + Dot_str},
            {'H', Dot_str + Dot_str + Dot_str + Dot_str},
            {'I', Dot_str + Dot_str},
            {'J', Dot_str + Dash_str + Dash_str + Dash_str},
            {'K', Dash_str + Dot_str + Dash_str},
            {'L', Dot_str + Dash_str + Dot_str + Dot_str},
            {'M', Dash_str + Dash_str},
            {'N', Dash_str + Dot_str},
            {'O', Dash_str + Dash_str + Dash_str},
            {'P', Dot_str + Dash_str + Dash_str + Dot_str},
            {'Q', Dash_str + Dash_str + Dot_str + Dash_str},
            {'R', Dot_str + Dash_str + Dot_str},
            {'S', Dot_str + Dot_str + Dot_str},
            {'T', Dash_str},
            {'U', Dot_str + Dot_str + Dash_str},
            {'V', Dot_str + Dot_str + Dot_str + Dash_str},
            {'W', Dot_str + Dash_str + Dash_str},
            {'X', Dash_str + Dot_str + Dot_str + Dash_str},
            {'Y', Dash_str + Dot_str + Dash_str + Dash_str},
            {'Z', Dash_str + Dash_str + Dot_str + Dot_str},
            {' ', IntraCharGapMorse_str} // Handle spaces in translate()
        };

        // Translate an english string into Morse code in the output string
        void translate(const std::string EnglishPhrase, std::string &output);

        // Display a morse code string in the terminal and hardware
        void displayMorse(const std::string MorseCodePhrase);

        // Morse Code Character Handlers
        void dotMorseHandler();
        void dashMorseHandler();
        void interCharGapMorseHandler();
        void interWordGapMorseHandler();

        // Timing Functions
        void sleep(const std::chrono::milliseconds TimeToSleepFor) {std::this_thread::sleep_for(TimeToSleepFor);}
        void dotDelay() {sleep(TimeUnit_ms * DotDuration);}
        void dashDelay() {sleep(TimeUnit_ms * DashDuration);}
        void intraCharDelay() {sleep(TimeUnit_ms * IntraCharGapDuration);}
        void interCharDelay() {sleep(TimeUnit_ms * InterCharGapDuration);}
        void interWordDelay() {sleep(TimeUnit_ms * InterWordGapDuration);}

        // Hardware Functions
        void setLed(const bool State);
};