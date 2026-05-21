#pragma once

#include <iostream>
#include <string>

class Log {

public:
    enum Loglevel {
        App = 1,
        Prompt,
        Help,
        Error,
        Warning
    };

    struct Color {
        static constexpr const char* Reset = "\033[0m";
        static constexpr const char* Red = "\033[31m";
        static constexpr const char* Green = "\033[32m";
        static constexpr const char* Yellow = "\033[33m";
        static constexpr const char* Blue = "\033[34m";
        static constexpr const char* Cyan = "\033[36m";
    };

    void Println(const char* text);

    void Print(const char* text);

public:
    Log();

    Log(const char* message);

    ~Log();

public:
    void enumerate(int n, const char* item);

    void heading(const char* title);

    void message(const char* message, Loglevel type);

    void help();
};
