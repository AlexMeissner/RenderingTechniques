#pragma once

#include <Windows.h>
#include <iostream>
#include <string>

#define info info()
#define success success()
#define warning warning()
#define error error()
#define critical critical()

namespace print
{
    namespace internals
    {
        struct ConsoleColor
        {
            ConsoleColor(int iWinColor)
            {
                m_iWinColor = iWinColor;
            }

            int m_iWinColor = 0;
        };

        static ConsoleColor ColorBlackBlue = ConsoleColor(9);
        static ConsoleColor ColorBlackWhite = ConsoleColor(07);
        static ConsoleColor ColorBlackGreen = ConsoleColor(10);
        static ConsoleColor ColorBlackRed = ConsoleColor(12);
        static ConsoleColor ColorBlackYellow = ConsoleColor(14);
        static ConsoleColor ColorRedYellow = ConsoleColor(206);
        static ConsoleColor ColorYellowRed = ConsoleColor(236);

        void SetConsoleColor(ConsoleColor sColor);

        struct Info
        {
            template<typename T>
            Info& operator << (T&& x)
            {
                std::cout << x;
                return *this;
            }
        }; 

        struct Success
        {
            template<typename T>
            Success& operator << (T&& x)
            {
                SetConsoleColor(ColorBlackGreen);
                std::cout << x;
                SetConsoleColor(ColorBlackWhite);
                return *this;
            }
        };

        struct Warning
        {
            template<typename T>
            Warning& operator << (T&& x)
            {
                SetConsoleColor(ColorBlackYellow);
                std::cout << x;
                SetConsoleColor(ColorBlackWhite);
                return *this;
            }
        };

        struct Error
        {
            template<typename T>
            Error& operator << (T&& x)
            {
                SetConsoleColor(ColorBlackRed);
                std::cout << x;
                SetConsoleColor(ColorBlackWhite);
                return *this;
            };
        };

        struct Critical
        {
            template<typename T>
            Critical& operator << (T&& x)
            {
                SetConsoleColor(ColorYellowRed);
                std::cout << x;
                SetConsoleColor(ColorBlackWhite);
                return *this;
            };
        };
    };

    internals::Info info;
    internals::Success success;
    internals::Warning warning;
    internals::Error error;
    internals::Critical critical;

    static const std::string endl = "\n";
};