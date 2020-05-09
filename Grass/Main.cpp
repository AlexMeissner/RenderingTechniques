#include "stdafx.h"

int main()
{
    print::info << "Hello world!" << print::endl;
    print::success << "Hello world!" << print::endl;
    print::warning << "Hello world!" << print::endl;
    print::error << "Hello world!" << print::endl;
    print::critical << "Hello world!" << print::endl;
    return 0;
}