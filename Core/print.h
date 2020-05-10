#pragma once

#include "CommonHeaders.h"

#define info info()
#define success success()
#define warning warning()
#define error error()
#define critical critical()

namespace print
{
    void SetConsoleColor(const WORD Color);

    struct Info
    {
        template<typename T>
        Info& operator << (T&& x)
        {
            std::cout << x;
            return *this;
        }
    } info;

    struct Success
    {
        template<typename T>
        Success& operator << (T&& x)
        {
            SetConsoleColor(10);
            std::cout << x;
            SetConsoleColor(07);
            return *this;
        }
    } success;

    struct Warning
    {
        template<typename T>
        Warning& operator << (T&& x)
        {
            SetConsoleColor(14);
            std::cout << x;
            SetConsoleColor(07);
            return *this;
        }
    } warning;

    struct Error
    {
        template<typename T>
        Error& operator << (T&& x)
        {
            SetConsoleColor(12);
            std::cout << x;
            SetConsoleColor(07);
            return *this;
        };
    } error;

    struct Critical
    {
        template<typename T>
        Critical& operator << (T&& x)
        {
            SetConsoleColor(206);
            std::cout << x;
            SetConsoleColor(07);
            return *this;
        };
    } critical;

    static const std::string endl = "\n";
};