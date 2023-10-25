#ifndef Cnumber
#define Cnumber
#include <string>
using namespace std;

const string printing = "Stored number: ";
const string deleting = "Deleting instance of a number of length: ";
const string empty_instance = "Empty instance - no numerical value";
const string negative_sign = "-";
const string positive_sign = "+";
const string newline = "\n";

class CNumber
{

private:
	int length;
	int* listOfInts;
	bool isPositive;

	static int countDigits(int value);


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
