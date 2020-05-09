#include "print.h"

namespace print
{
    void SetConsoleColor(const WORD Color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
    }

    Info sInfo;
    Success sSuccess;
    Warning sWarning;
    Error sError;
    Critical sCritical;

    Info info
    {
        return sInfo;
    };

    Success success
    {
        return sSuccess;
    };

    Warning warning
    {
        return sWarning;
    };

    Error error
    {
        return sError;
    };

    Critical critical
    {
        return sCritical;
    };
}