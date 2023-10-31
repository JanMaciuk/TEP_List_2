#include "CNumber.h"
#include <iostream>

int main()
{
    CNumber test = CNumber();
    CNumber test2 = CNumber();
    test = 125;
    test2 = 10;
    CNumber result = test * test2;
    result.PrintNumber();
    CNumber result2 = test / test2;
    result2.PrintNumber();

    return 0;
}

