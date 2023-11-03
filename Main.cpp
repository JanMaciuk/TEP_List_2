#include "CNumber.h"
#include <iostream>

int main()
{
    CNumber dividend = 2147483647;
    CNumber divisor = 2007483647;
    dividend *= 5;
    divisor *= 2;
    dividend.PrintNumber();
    divisor.PrintNumber();
    CNumber result = dividend / divisor;
    result.PrintNumber();

    return 0;
}

