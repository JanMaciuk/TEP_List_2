#include "CNumber.h"


#include <iostream>

int main()
{
    CNumber test = CNumber();
    CNumber test2 = CNumber();
    test = 103;
    test2 = 100;
    test - test2;
    test.PrintNumber();
    //Substraction implementation progress:
    //Done:
    //When first number is bigger than second and signs are the same
    //TODO:
    //When first number is smaller than second
    //When signs are the same

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
