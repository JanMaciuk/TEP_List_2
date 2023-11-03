#include "CNumber.h"
#include <string>
#include <iostream>
using namespace std;

//private statics used in methods
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
	for (int i = 0; i < length-1; i++) //length-1 because the last digit isnt a leading zero
	{
		if (value[i] == 0) count++;
		else return count;
	}
	return count;
}


bool CNumber::isBigger(const CNumber& thisInstance, const CNumber& otherInstance, bool* isIdentical) {
	// check which CNumber holds a number with a bigger absolute value
	*isIdentical = false;
	bool thisIsBigger = false;
	if (thisInstance.length > otherInstance.length) thisIsBigger = true;
	else if (thisInstance.length < otherInstance.length) thisIsBigger = false;
	else for (int i = 0; i < thisInstance.length; i++) //lengths are equal, check each digit from the left
	{
		if (thisInstance.listOfInts[i] > otherInstance.listOfInts[i])
		{
			thisIsBigger = true;
			i = thisInstance.length; //break out of the loop without using break
		}
		else if (thisInstance.listOfInts[i] < otherInstance.listOfInts[i])
		{
			thisIsBigger = false;
			i = thisInstance.length; //break out of the loop without using break
		}
		else if (i == thisInstance.length - 1) // numbers are same but could have different signs
		{ //this check will only be executed if all digits are equal, we might as well check the signs to speed up substracting identical numbers
			if (thisInstance.isPositive == otherInstance.isPositive) { //all digits and signs are equal
				*isIdentical = true;
			}
		}
	}
	return thisIsBigger;
}


void CNumber::copyArray(CNumber& thisInstance, int* array[], int arrayLength)
{ 
	delete[] thisInstance.listOfInts;
	int newArrayLength = arrayLength - countLeadingZeroes(*array, arrayLength); //get rid of leading zeroes
	thisInstance.listOfInts = new int[newArrayLength];
	for (int i = newArrayLength - 1, j = arrayLength - 1; i >= 0 && j >= 0; i--, j--)
	{
		thisInstance.listOfInts[i] = (*array)[j];
	}
	thisInstance.length = newArrayLength;
	delete * array;
}


void CNumber::substractArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList, int* resultList) 
{
	int carryOver = 0;
	for (int i = otherInstanceLength - 1, j = thisLength - 1; i >= 0; i--, j--)
	{
		resultList[j + 1] = thisList[j] - otherList[i] - carryOver;
		if (resultList[j + 1] < 0)
		{
			resultList[j + 1] += baseNumber;
			carryOver = 1;
		}
		else carryOver = 0;
		if (i == 0 && j > 0)
		{
			resultList[j] = thisList[j - 1] - carryOver;
			j--;
			//Copy rest of listOfInts to result
			while (j > 0)
			{
				resultList[j] = thisList[j - 1];
				j--;
			}
		}
	}
}


void CNumber::addArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList, int* resultList)
{
	int carryOver = 0;
	for (int i = otherInstanceLength - 1, j = thisLength - 1; i >= 0; i--, j--)
	{
		resultList[j + 1] = thisList[j] + otherList[i] + carryOver;
		if (resultList[j + 1] > maxDigit) // if greater than 9, substract 10 from the current number and add 1 to the next number
		{
			resultList[j + 1] -= baseNumber;
			carryOver = 1;
		}
		else carryOver = 0;
		if (i == 0 && j > 0)
		{
			// if carryOver is set, keep adding 1 to the next number until there is no carryOver
			// For example when adding 9999 + 1, this loop will execute many times even though we are done iterating over 1;
			while (carryOver == 1) 
			{ 
				resultList[j] = thisList[j - 1] + carryOver;
				if (resultList[j] > maxDigit) // if greater than 9, substract 10 from the current number and add 1 to the next number
				{
					resultList[j] -= baseNumber;
					carryOver = 1;
				}
				else carryOver = 0;
				j--;
				if (j == 0 && carryOver == 1) { resultList[0] = 1; carryOver = 0; }//If we are at the last digit and still have a carryOver, add 1 to the first digit of the result
			}
			//Copy rest of listOfInts to result
			while (j > 0)
			{
				resultList[j] = thisList[j - 1];
				j--;
			}
		}
	}
}

void CNumber::addArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList)
{
	// Version of addArrays that modifies the first array instead of creating a new one
	// Differs in signature, will be called if a pointer to result array is not provided
	int carryOver = 0;
	for (int i = otherInstanceLength - 1, j = thisLength - 1; i >= 0; i--, j--)
	{
		thisList[j] = thisList[j] + otherList[i] + carryOver;
		if (thisList[j] > maxDigit) // if greater than 9, substract 10 from the current number and add 1 to the next number
		{
			thisList[j] -= baseNumber;
			carryOver = 1;
		}
		else carryOver = 0;
		if (i == 0 && j > 0)
		{
			// if carryOver is set, keep adding 1 to the next number until there is no carryOver
			// For example when adding 9999 + 1, this loop will execute many times even though we are done iterating over 1;
			j--;
			while (carryOver == 1) 
			{
				thisList[j] = thisList[j] + carryOver;
				if (thisList[j] > maxDigit) // if greater than 9, substract 10 from the current number and add 1 to the next number
				{
					thisList[j] -= baseNumber;
					carryOver = 1;
				}
				else carryOver = 0;
				j--;
				if (j == 0 && carryOver == 1) { thisList[0] = 1; carryOver = 0; }//If we are at the last digit and still have a carryOver, add 1 to the first digit of the result
			}
		}
	}
}


void CNumber::multiplyArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList, int** results, int resultLength, int numberOfResults)
{
	for (int resultIndex = numberOfResults - 1, j = otherInstanceLength - 1, resultOffset = 1; resultIndex >= 0; resultIndex--, j--, resultOffset++)
	{
		int currentCarryOver = 0;
		for (int i = thisLength - 1, k = resultLength - resultOffset; i >= 0; i--, k--)
		{
			int nextCarryOver = 0;
			results[resultIndex][k] = thisList[i] * otherList[j] + currentCarryOver;
			while (results[resultIndex][k] > maxDigit)
			{ // make sure the digit is not greater than 9
				results[resultIndex][k] -= baseNumber;
				nextCarryOver++;
			}
			currentCarryOver = nextCarryOver;
		}
	}
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
		listOfInts[i] =  valueAsString[i] - zeroChar; // Substract the ASCII value of 0 to get the actual digit (characters have codes after eachother)
	}
}

CNumber::CNumber(const CNumber& otherInstance)
{ //copy constructor
	length = otherInstance.length;
	isPositive = otherInstance.isPositive;
	listOfInts = new int[length];
	for (int i = 0; i < length; i++)
	{
		listOfInts[i] = otherInstance.listOfInts[i];
	}
}



//OPERATORS:

//Assignment:

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


//Substraction:
void CNumber::operator-=(const int value) { *this -= CNumber(value); } // Simply call the operator- with a temporary instance of CNumber

void CNumber::operator-=(const CNumber& otherInstance) { *this = *this - otherInstance; } //use the operator- to get the result, then copy it to this instance

CNumber CNumber::operator-(const int value) { return *this - CNumber(value); } // Simply call the operator- with a temporary instance of CNumber

CNumber CNumber::operator-(const CNumber& otherInstance) 
{
	// 1. determine which number is bigger:
	//check length, if equal, check each digit from the left, if all are equal, zero the array and return
	//save result in bool
	// 
	// 2. check signs
	//two positive numbers: substract normally (result will keep sign - will be positive)
	//two negative numbers: substract normally, (result will keep sign - will be negative)
	//one number is positive, the other is negative: add numbers, flip sign if this number was smaller
	// 
	// 3. for loop: (results in result array, substract from smaller number)
	//if (substract normally):
	//substract number by number starting from the last.
	//if result is negative, add 10 to the current number and substract 1 from the next number (set bool)
	// 
	//else if (do addition):
	// add number by number starting from the last.
	// if result is greater than 9, substract 10 from the current number and add 1 to the next number (set bool)
	// if carryOver is set after loop is done, keep adding 1 to the next number until there is no carryOver
	// 
	// 4. if "this" number was smaller, flip the sign, copy result to final array

	bool isIdentical = false;
	CNumber resultInstance = CNumber();

	// 1. determine which number is bigger:
	bool thisIsBigger = isBigger(*this, otherInstance, &isIdentical);
	if (isIdentical) //if the numbers are identical we can simply return a zero (substracting a number from itself)
	{
		return resultInstance; //resultInstance is initialized as zero
	}

	// 2. check signs:
	bool doAddition = (isPositive != otherInstance.isPositive); //one number is positive, the other is negative: add numbers, then flip the sign at the end

	//3. main for loop:
	int resultLength = max(length, otherInstance.length) + 1;
	int* result = new int[resultLength]; //+1 in case we need to add a carry over in addition
	result[0] = 0; // zero the leading digit to easily check if it was modified
	int carryOver = 0;

	if (!doAddition) //do substraction
	{
		if (thisIsBigger) //substract from this number (its bigger)
		{
			substractArrays(length, otherInstance.length, listOfInts, otherInstance.listOfInts, result);
		}
		else //substract from the other number (its bigger)
		{
			substractArrays(otherInstance.length, length, otherInstance.listOfInts, listOfInts, result);
			isPositive = !isPositive; //flip the sign if substracted from the other number (reversed operation order)
		}
	}
	else //do addition
	{
		// which number is bigger matters for iterating over the arrays.
		if (thisIsBigger) //add to this number (its bigger)
		{
			addArrays(length, otherInstance.length, listOfInts, otherInstance.listOfInts, result);
		}
		else //add to the other number (its bigger)
		{
			addArrays(otherInstance.length, length, otherInstance.listOfInts, listOfInts, result);
		}
	}

	//4. copy result to listOfInts:
	resultInstance.isPositive = isPositive;
	copyArray(resultInstance, &result, resultLength);
	return resultInstance;
}


//Addition:
void CNumber::operator+=(const int value) { *this += CNumber(value); } // Simply call the operator+ with a temporary instance of CNumber

void CNumber::operator+=(const CNumber& otherInstance) { *this = *this + otherInstance; } //use the operator+ to get the result, then copy it to this instance

CNumber CNumber::operator+(const int value) { return *this + CNumber(value); } // Simply call the operator+ with a temporary instance of CNumber

CNumber CNumber::operator+(const CNumber& otherInstance) 
{
	//both positive: add the smaller number to the bigger number, keep sign
	//both negative: add the smaller number to the bigger number, keep sign
	//one positive, the other negative: substract the smaller number from the bigger number, keep sign of the bigger number
	bool isIdentical = false;
	bool thisIsBigger = isBigger(*this, otherInstance, &isIdentical);
	bool doSubstraction = (isPositive != otherInstance.isPositive); //one positive, the other negative: substract the smaller number from the bigger number, keep sign of the bigger number

	int resultLength = max(length, otherInstance.length) + 1;
	int* result = new int[resultLength]; //+1 in case we need to add a carry over in addition
	result[0] = 0; // zero the leading digit to easily check if it was modified
	int carryOver = 0;

	if (!doSubstraction) 
	{
		if (thisIsBigger) //add to this number (its bigger)
		{
			addArrays(length, otherInstance.length, listOfInts, otherInstance.listOfInts, result);
		}
		else //add to the other number (its bigger)
		{
			addArrays(otherInstance.length, length, otherInstance.listOfInts, listOfInts, result);
		}
	}
	else //do substraction
	{
		if (thisIsBigger) //substract from this number (its bigger)
		{
			substractArrays(length, otherInstance.length, listOfInts, otherInstance.listOfInts, result);
		}
		else //substract from the other number (its bigger)
		{
			substractArrays(otherInstance.length, length, otherInstance.listOfInts, listOfInts, result);
			isPositive = otherInstance.isPositive; //keep the sign of the bigger number
		}
	}
	CNumber resultInstance = CNumber();
	if (thisIsBigger) { resultInstance.isPositive = isPositive; }
	else { resultInstance.isPositive = otherInstance.isPositive; }
	copyArray(resultInstance, &result, resultLength);	
	return resultInstance;
}


//Multiplication:
void CNumber::operator*=(const CNumber& otherInstance) { *this = *this * otherInstance; } //use the operator* to get the result, then copy it to this instance

void CNumber::operator*=(const int value) { *this *= CNumber(value); } // Simply call the operator* with a temporary instance of CNumber

CNumber CNumber::operator*(const int value) { return *this * CNumber(value); } // Simply call the operator* with a temporary instance of CNumber

CNumber CNumber::operator*(const CNumber& otherInstance) {
	// Create a 2D array to store the result of each multiplication
	// Array will store (smaller length) numbers of length (bigger length + 1) each
	// Multilication:
	// nextCarryOver = 0
	// For last digit of the smaller number, multiply it by each digit of the bigger number, store the result in an array
	// Add currentCarryOver to the digit
	// While resulting digit is greater than 9, increase nextCarryOver by 1 and decrease the digit by 10
	// currentCarryOver = nextCarryOver
	// Move on to the next digit of the smaller number, repeat
	// 
	// After multiplying all digits of the smaller number, add all results together into finalResult array

	int finalResultLength = length + otherInstance.length; // Maximum length of the result
	int* finalResult = new int[finalResultLength];
	for (int i = 0; i < finalResultLength; i++) { finalResult[i] = 0; } // Initialize all digits to 0

	int numberOfResults= min(length, otherInstance.length);
	int resultLength = max(length, otherInstance.length) + numberOfResults;
	int** results = new int* [numberOfResults];
	for (int i = 0; i < numberOfResults; i++)
	{
		results[i] = new int[resultLength];
		for(int j = 0; j < resultLength; j++) { results[i][j] = 0; } // Initialize all digits to 0
	}
	bool thisIsLonger = (length >= otherInstance.length);

	if (thisIsLonger) { multiplyArrays(length, otherInstance.length, listOfInts, otherInstance.listOfInts, results, resultLength, numberOfResults); }
	else { multiplyArrays(otherInstance.length, length, otherInstance.listOfInts, listOfInts, results, resultLength, numberOfResults);}
	
	
	// Sum the arrays into finalResult:
	for(int i = 0; i < numberOfResults; i++)
	{
		addArrays(finalResultLength, resultLength, finalResult, results[i]);
		delete[] results[i];
	}

	// Return the result:
	CNumber resultInstance = CNumber();
	resultInstance.isPositive = (isPositive == otherInstance.isPositive); // if signs are the same, result will be positive
	copyArray(resultInstance, &finalResult, finalResultLength);
	return resultInstance;
}


//Division:
void CNumber::operator/=(const int value) { *this /= CNumber(value); } // Simply call the operator/ with a temporary instance of CNumber

void CNumber::operator/=(const CNumber& otherInstance) { *this = *this / otherInstance; } //use the operator/ to get the result, then copy it to this instance

CNumber CNumber::operator/(const int value) { return *this / CNumber(value); } // Simply call the operator/ with a temporary instance of CNumber

CNumber CNumber::operator/(const CNumber& otherInstance) 
{
	// Check edge cases:
	// if this or otherInstance is zero, return zero (assume division by zero returns zero)
	// if otherInstance is 1, return a copy of this
	// if this is smaller than otherInstance, return zero
	// if this is equal to otherInstance, return 1
	// 
	// divisor = int value of otherInstance.listOfInts
	// temp = listOfInts[0]
	// Do division: (for loop, i=0)
	// while (temp < divisor) { resultArray[i]=0; i++; temp = temp * 10 + listOfInts[i+1] }
	// resultArray[i] = temp / divisor
	// substract = divisor * resultArray[i]
	// temp = temp - substract

	// Check edge cases:
	bool isIdentical = false;
	bool thisIsBigger = isBigger(*this, otherInstance, &isIdentical);
	if (isIdentical) { return CNumber(1); }  //if the numbers are identical return 1 (dividing a number by itself)
	if (!thisIsBigger) { return CNumber(0); } //if this is smaller than otherInstance, division will result in a number smaller than 1, return 0
	// if this or otherInstance is zero, return zero
	if ((otherInstance.length == 1 && otherInstance.listOfInts[0] == 0) || (length == 1 && listOfInts[0] == 0)) { return CNumber(0); }
	// if otherInstance is 1, return a copy of this
	if (otherInstance.length == 1 && otherInstance.listOfInts[0] == 1) 
	{ 
		CNumber result = *this;
		result = *this;
		return result;
	}

	int divisor = 0;
	for(int i = 0; i < otherInstance.length; i++) { divisor = divisor * 10 + otherInstance.listOfInts[i]; }
	int temp = listOfInts[0];
	int* resultArray = new int[length];
	//Do division:
	for (int i = 0; i < length; i++)
	{
		while (temp < divisor && i < length) 
		{ 
			resultArray[i] = 0; 
			if (i < length -1) i++;
			temp = temp * 10 + listOfInts[i];
		}
		if (i < length) //else: we finished, ignore remainder and quit loop
		{
			resultArray[i] = temp / divisor;
			int substract = divisor * resultArray[i];
			temp = temp - substract;
		}
	}

	CNumber resultInstance = CNumber();
	resultInstance.isPositive = (isPositive == otherInstance.isPositive); // if signs are the same, result will be positive
	copyArray(resultInstance, &resultArray, length);
	return resultInstance;
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


CNumber::~CNumber() { delete[] listOfInts; }
