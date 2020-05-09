#include "print.h"

namespace print
{
    namespace internals
    {
        void SetConsoleColor(ConsoleColor eColor)
        {
            HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            SetConsoleTextAttribute(hConsole, eColor.m_iWinColor);
        }
    }

    internals::Info sInfo;
    internals::Success sSuccess;
    internals::Warning sWarning;
    internals::Error sError;
    internals::Critical sCritical;

    internals::Info info
    {
        return sInfo;
    };

    internals::Success success
    {
        return sSuccess;
    };

    internals::Warning warning
    {
        return sWarning;
    };

    internals::Error error
    {
        return sError;
    };

    internals::Critical critical
    {
        return sCritical;
    };
}