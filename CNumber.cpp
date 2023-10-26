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

int CNumber::countLeadingZeroes(int value[], int length) 
{
	int count = 0;
	for (int i = 0; i < length; i++)
	{
		if (value[i] == 0) count++;
		else return count;
	}
	return count;
}

//Constructors:
CNumber::CNumber() 
{//default constructor - stores number zero
	length = 1;
	listOfInts = new int[1];
	listOfInts[0] = 0;
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

//Operators:

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

void CNumber::operator-(const CNumber& otherInstance)
{
	// 1. determine which number is bigger:
	//check length, if equal, check each digit from the left, if all are equal, zero the array and return
	//save result in bool
	// 
	// 2. check signs
	//two positive numbers: substract normally (result will keep sign - will be positive)
	//two negative numbers: substract normally, (result will keep sign - will be negative)
	//one number is positive, the other is negative: add numbers, then flip the sign at the end
	// 
	// 3. for loop: (results in result array, substract from smaller number)
	//if (substract normally):
	//substract number by number starting from the last.
	//if result is negative, add 10 to the current number and substract 1 from the next number (set bool)
	// 
	//else if (do addition):
	// add number by number starting from the last.
	// if result is greater than 9, substract 10 from the current number and add 1 to the next number (set bool)
	// if carryOver is set after loop is done, copy array to new array with length + 1, set first number to 1
	// 
	// 4. if "this" number was smaller, flip the sign

	bool thisIsBigger = false;
	bool doAddition = false;
	bool flipSign = false;

	// 1. determine which number is bigger:
	if (length > otherInstance.length) thisIsBigger = true;
	else if (length < otherInstance.length) thisIsBigger = false;
	else for (int i = 0; i < length; i++) //lengths are equal, check each digit from the left
	{
		if (listOfInts[i] > otherInstance.listOfInts[i])
		{
			thisIsBigger = true;
			i = length; //break out of the loop without using break
		}
		else if (listOfInts[i] < otherInstance.listOfInts[i])
		{
			thisIsBigger = false;
			i = length; //break out of the loop without using break
		}
		else if (i == length - 1) // numbers are same but could have different signs
		{  
			if (isPositive == otherInstance.isPositive) { //all digits are equal, substracting the sume number always results in a zero
				length = 1;
				delete[] listOfInts;
				listOfInts = new int[1];
				listOfInts[0] = 0;
				return;
			}
		}
	}
	

	// 2. check signs:
	if (isPositive != otherInstance.isPositive) { doAddition = true; } //one number is positive, the other is negative: add numbers, then flip the sign at the end


	//3. main for loop:
	int resultLength = max(length, otherInstance.length) + 1;
	int* result = new int[resultLength]; //+1 in case we need to add a carry over in addition
	result[0] = 0; // zero the leading digit to easily check if it was modified
	int carryOver = 0;
	
	if (!doAddition)
	{
		if (thisIsBigger) 
		{
			for (int i = otherInstance.length-1, j = length-1; i >= 0; i--, j--)
			{
				result[j + 1] = listOfInts[j] - otherInstance.listOfInts[i] - carryOver;
				if (result[j + 1] < 0)
				{
					result[j + 1] += 10;
					carryOver = 1;
				}
				else carryOver = 0;
				if (i == 0 && j > 0)
				{
					result[j] = listOfInts[j] - carryOver;
					j--;
					//Copy rest of listOfInts to result
					while (j>=0)
					{
						result[j] = listOfInts[j];
						j--;
					}
			    }
			}
			
		}
		else
		{
			//substract from the other number
			
		}
		
	}
	else 
	{
		//do addition
	}

	// copy result to listOfInts:
	delete[] listOfInts;
	int newResultLength = resultLength - countLeadingZeroes(result, resultLength);
	listOfInts = new int[newResultLength];
	for (int i = newResultLength-1, j = resultLength -1; i >= 0 && j >= 0; i--,j--)
	{
		listOfInts[i] = result[j];
	}
	length = newResultLength;
	delete[] result;




}
//Non operator methods:
string CNumber::ToString()
{
	string result = "";
	if (!isPositive) result += negative_sign;
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
