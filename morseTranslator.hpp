#include <string>
#include <chrono>
#include <unordered_map>

class MorseTranslator
{
    public:
        MorseTranslator() {};
        void process();

    private:
        // Timing
        static constexpr unsigned int DotDuration  {1}; // One unit of time for dots
        static constexpr unsigned int DashDuration {2}; // Two units of time for dashes
        static constexpr unsigned int IntraCharGapDuration {2}; // One units of time between dots and dashes
        static constexpr unsigned int InterCharGapDuration {2}; // Two units of time between letters
        static constexpr unsigned int InterWordGapDuration {3}; // Three units of time between words
        static constexpr std::chrono::milliseconds TimeUnit_ms {132}; // Base unit, 132 ms = ~12 words per minute
        static constexpr unsigned int WordsPerMinute {12};

        // Characters, spacing/gaps
        static inline const std::string InterCharGap {" "}; // One space between letters
        static inline const std::string InterWordGap {"/"}; // '/' Character between words
        static inline const char Dot {'.'};
        static inline const char Dash {'-'};
        static inline const std::string Dot_str {"."};
        static inline const std::string Dash_str {"-"};

        // Map characters to morse code
        static inline const std::unordered_map<char, std::string> LetterToCode
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
            {' ', ""} // Handle spaces in translate()
        };

        // Functions
        void translate(const std::string EnglishPhrase, std::string &output);
        void display(const std::string MorseCodePhrase);
        void playDot();
        void playDash();
        void playLetterGap();
        void playWordGap();
        void sleep(const std::chrono::milliseconds TimeToSleepFor);
        void setLed(const bool State);
};