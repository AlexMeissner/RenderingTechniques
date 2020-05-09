#include "print.h"

namespace print
{
    void SetConsoleColor(const WORD Color)
    {
        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), Color);
    }

    Info InfoStream;
    Success SuccessStream;
    Warning WarningStream;
    Error ErrorStream;
    Critical CriticalStream;

    Info info
    {
        return InfoStream;
    };

    Success success
    {
        return SuccessStream;
    };

    Warning warning
    {
        return WarningStream;
    };

    Error error
    {
        return ErrorStream;
    };

    Critical critical
    {
        return CriticalStream;
    };
}