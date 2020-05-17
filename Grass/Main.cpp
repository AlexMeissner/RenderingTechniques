#include "stdafx.h"
#include "Grass.h"

int main()
{
    grass application("Grass Rendering");

    if (application.initialize())
    {
        application.run();
    }

    return 0;
}