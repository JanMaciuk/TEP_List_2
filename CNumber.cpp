#include "CNumber.h"
#include <string>
#include <iostream>
using namespace std;


int CNumber::countDigits(int value) 
{
	if (value == 0)  return 1; 
	int count = 0;
	while (value != 0)
	{
		value /= 10;
		count++;
	}
	return count;
}

//Constructors:
CNumber::CNumber() 
{
	length = 0; // a number with zero length is considered an empty instance
	listOfInts = new int[1];
	isPositive = true;

}


CNumber::CNumber(int value) {
	length = countDigits(value);
	if (value >= 0) isPositive = true;
	else {
		isPositive = false;
		value *= -1; // Get rid of the minus sign for array filling
	}
	listOfInts = new int[length];
	string valueAsString = to_string(value);
	//Fill array with digits
	for (int i = 0; i < length; i++)
	{
		listOfInts[i] =  valueAsString[i] - '0'; // Substract the ASCII value of 0 to get the actual digit (characters have codes after eachother)
	}
}

//Methods:

// Old implementation, replaced by a more elegant solution
//void CNumber::operator=(const int value)
//{	
//	//Avoid code repetition by using the constructor
//	//temp is allocated on the stack, so it will be destroyed after the function ends
//	CNumber temp = CNumber(value); 
//	length = temp.length;
//	isPositive = temp.isPositive;
//	delete[] listOfInts;
//	listOfInts = new int[length];
//	for (int i = 0; i < length; i++)
//	{
//		listOfInts[i] = temp.listOfInts[i];
//	}
//	
//}
void CNumber::operator=(const int value) { *this = CNumber(value); }
	//Avoid code repetition by using the constructor
	//temp is allocated on the stack, so it will be destroyed after the function ends
	//Using the overloaded operator= to copy all data from freshly created temporary instance to the instance method is run for.


void CNumber::operator=(const CNumber& otherInstance)
{
	//Implementing this method as specified in the task orginally would cause a memory leak, previous array is never deleted.
	//Even bigger issue is that it only sets the pointer of first array to point to the second array, so both instances would be pointing to the same array.
	//This would cause many problems, for exmaple if one of the instances was destroyed, the other one would be pointing to a deleted array.
	//Deleting the destructor "removes" the issue of attempting to free the same address twice, but they still point to the same array, meaning we will always modify both.
	length = otherInstance.length;
	isPositive = otherInstance.isPositive;
	delete[] listOfInts;
	listOfInts = new int[length];
	for (int i = 0; i < length; i++)
	{
		listOfInts[i] = otherInstance.listOfInts[i];
	}
	
}

string CNumber::ToString()
{
	string result = "";
	if (length == 0) return empty_instance;
	if (isPositive) result += positive_sign;
	else result += negative_sign;
	for (int i = 0; i < length; i++)
	{
		result += to_string(listOfInts[i]);
	}
	return result;
}

void CNumber::PrintNumber() { cout << printing << ToString() << newline; }


CNumber::~CNumber()
{
	cout << deleting << length << newline;
	delete[] listOfInts;
}
