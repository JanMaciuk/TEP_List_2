#ifndef Cnumber
#define Cnumber
#include <string>
using namespace std;

const string printing = "Stored number: ";
const string deleting = "Deleting instance of a number of length: ";
const string negative_sign = "-";
const string newline = "\n";

class CNumber
{

private:
	int length;
	int* listOfInts;
	bool isPositive;

	static int countDigits(int value);
	static int countLeadingZeroes(int value[], int lenght);
	static void substractArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList, int* resultList);


public:
	
	//Constructors:
	CNumber();
	CNumber(int value);

	//Operators:
	void operator=(const int value);
	void operator=(const CNumber& otherInstance);
	void operator-(const CNumber& otherInstance);

	//Methods:
	string ToString();
	void PrintNumber();



	//Destructor:
	~CNumber();
};
#endif
