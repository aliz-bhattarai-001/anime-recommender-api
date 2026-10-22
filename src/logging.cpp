#include "../include/logging.hpp"
#include <iostream>
#include <string>

// Defining the Logging class:

// Helper Functions:

void Log::Println(const char *text)
{
    std::cout << text << std::endl;
}

void Log::Print(const char *text)
{
    std::cout << text;
}

// Class Constuctor & Destructor

Log::Log() {}

Log::Log(const char *message)
{
    Println(message);
}

Log::~Log() {}

// Methods available in Log class

void Log::enumerate(int n, const char *item)
{
    std::cout << "(" << n << ") " << item << std::endl;
    return;
}

void Log::heading(const char *title)
{
    std::cout << "========================================" << std::endl;
    std::cout << "\t" << title << std::endl;
    std::cout << "========================================" << std::endl;
    return;
}

// void message(const char* message, Loglevel type)
//{
//     std::string prefix = "";

//    if (type == Warning)
//        prefix = "[Warning]: ";
//    else if (type == Prompt)
//        prefix = "[User]: ";
//    else if (type == Help)
//        prefix = "[Help]: ";
//    else if (type == Error)
//        prefix = "[Error]: ";
//    else
//        prefix = "[APP]: ";

//    std::string combined = prefix + message;
//    Println(combined.c_str());
//}

void Log::message(const char *message, Loglevel level)
{
    std::string prefix;
    const char *color = Color::Reset;

    switch (level)
    {
    case Loglevel::Warning:
        prefix = "[Warning]: ";
        color = Color::Yellow;
        break;
    case Loglevel::Error:
        prefix = "[Error]: ";
        color = Color::Red;
        break;
    case Loglevel::Prompt:
        prefix = "[User]: ";
        color = Color::Cyan;
        break;
    case Loglevel::Help:
        prefix = "[Help]: ";
        color = Color::Reset;
        break;
    default:
        prefix = "[Log]: ";
        color = Color::Green;
        break;
    }

    std::string output = std::string(color) + prefix + Color::Reset + message;

    Println(output.c_str());
}

// This helps in knowing methods within class:
// for that future self of mine who'll forget what is available here.

void Log::help()
{
    const char *methods[] = {
        "void enumerate(int n, const char* item) -> use within for loops \n  Usage: log.enumerate(i, element);",
        "void heading(const char* title) -> for title cards: \n  Usage: log.heading(\"Title\");",
        "void message(const char* message, int type) -> for different level messages: \n  Usage: log.message(\"System Failure\", Log::Error);",
        "void help() -> for showing this help message: \n  Usage: log.help();"};

    heading("LOG CLASS HELP");
    std::cout << "\n";

    // calculating the total elements in the array
    int count = sizeof(methods) / sizeof(methods[0]);

    for (int i = 0; i < count; i++)
    {
        enumerate(i + 1, methods[i]); // using enumearte to display the list
        std::cout << "---" << std::endl;
    }
}