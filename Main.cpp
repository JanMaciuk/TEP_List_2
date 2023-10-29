#include "CNumber.h"
#include <iostream>

int main()
{
    CNumber test = CNumber();
    CNumber test2 = CNumber();
    test = 125;
    test2 = 5;
    CNumber test3 = test + test2;
    test += test2;
    test.PrintNumber();
    test3.PrintNumber();
    //Substraction implementation progress:
    //Done:
    //When signs are the same
    //TODO:
    //When signs are different

}

