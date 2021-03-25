#include "stdafx.h"
#include "HeightMap.h"

int main()
{
    height_map application("Height Map");

    if (application.initialize())
    {
        application.run();
    }

    return 0;
}