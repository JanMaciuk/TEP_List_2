#ifndef Cnumber
#define Cnumber
#include <string>
using namespace std;

const string printing = "Stored number: ";
const string deleting = "Deleting instance with a number: ";
const string negative_sign = "-";
const string newline = "\n";
const int defaultValue = 0;
const int defaultLength = 1;
const int maxDigit = 9; // highest digit in decimal system
const char zeroChar = '0'; // used for converting int to char
const int baseNumber = 10; // used for carry over in addition and substraction


class CNumber
{

private:

	int length;
	int* listOfInts;
	bool isPositive;

	static int countDigits(int value);
	static int countLeadingZeroes(int value[], int lenght);
	static bool isBigger(const CNumber& thisInstance, const CNumber& otherInstance, bool* isIdentical);
	static void copyArray(CNumber& thisInstance, int* array[], int arrayLength);
	static void substractArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList, int* resultList);
	static void addArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList, int* resultList);
	static void addArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList);
	static void multiplyArrays(int thisLength, int otherInstanceLength, int* thisList, int* otherList, int** results, int resultLength, int numberOfResults);


public:
	
	//Constructors:
	CNumber();
	CNumber(int value);

	//Operators:
	void operator=(const CNumber& otherInstance);
	void operator=(const int value);

	void operator-=(const CNumber& otherInstance);
	void operator-=(const int value);
	CNumber operator-(const CNumber& otherInstance);
	CNumber operator-(const int value);

	void operator+=(const CNumber& otherInstance);
	void operator+=(const int value);
	CNumber operator+(const CNumber& otherInstance);
	CNumber operator+(const int value);

	void operator*=(const CNumber& otherInstance);
	void operator*=(const int value);
	CNumber operator*(const CNumber& otherInstance);
	CNumber operator*(const int value);

	//Methods:
	string ToString();
	void PrintNumber();



	//Destructor:
	~CNumber();
};
#endif
