#include "pch.h"
#include "io.h"

void print(std::string message) //may or may not be redundant.  
{
	std::cout << message << '/n';
}

//Structure of input:
/*
0. Begin while true loop 
1. give prompt.
2. give input: 
 - if input is correct: pass through and return to caller
 - if input is incorrect: for now, reject input, let user know, and retry input at top of while true loop
*/

int intInput(std::string prompt)
{
	int userInput{};
	while (true)
	{
		userInput = 0; //reset number just in case
		std::string currentInput{ getInput(prompt) };

		if (currentInput.size() < 1) // if no characters in the string
			std::cout << "Invalid Input \n";
		else
		{
			userInput = stringToInt(currentInput);
			if (userInput != -1)
				break;
		}
	}
	return userInput;
}

//this function along with intInput could require some refactoring for simplification as there is overlap between the two functions. 
double doubleInput(std::string prompt)
{
	double userInput{}; //initialize user input variable
	while (true) 
	{
		userInput = 0.0; //reset number just in case of error
		std::string currentInput{ getInput(prompt) };
		userInput = stringToDouble(currentInput);
		if (userInput != -1) 
		{
			break; // if valid number then we can exit loop
		}
		
	}
	return userInput;
}

std::string stringInput(std::string prompt)
{
	return getInput(prompt);
	//for now, stringInput will remain like this
}

std::string getInput(std::string prompt) 
{
	std::string userInput{};
	std::cout << prompt << '\n';
	std::getline(std::cin >> std::ws, userInput);
	return userInput;
}

int charToInt(char number)
{
	if (number == '0')
		return 0;
	else if (number == '1')
		return 1;
	else if (number == '2')
		return 2;
	else if (number == '3')
		return 3;
	else if (number == '4')
		return 4;
	else if (number == '5')
		return 5;
	else if (number == '6')
		return 6;
	else if (number == '7')
		return 7;
	else if (number == '8')
		return 8;
	else if (number == '9')
		return 9;
	else
	{
		//add more rejection code later.
		//system of rejection is as follows:
		//Returns -1 to caller. As -1 will not be used for pretty much any form of input, it can be used.
		//The above can then read the output and then make a decision based on such. 
		//
		return -1;
	}
} 
//should find a better solution on Google for this, but since I already made it there's no shame in using it now

std::string intToString(int intValue) 
{
	std::string intString = std::to_string(intValue);
	return intString;
	//https://www.tutorialspoint.com/How-to-convert-an-int-to-string-in-Cplusplus 
}//converting an integer to string

std::string doubleToString(double doubleValue) 
{
	std::string doubleString = std::to_string(doubleValue);
	return doubleString;
}//converting a double to string

//some information on string filtering: 
//a library can be found here: https://stackoverflow.com/questions/3941548/string-filtering-on-c

int stringToInt(std::string integer) 
{
	int newInt{ 0 };
	//for loop for decoding string input
	for (unsigned int i = 0; i < integer.size(); i++)
	{
		if (i > 0)
			newInt *= 10; //multiply by 10 to add upon the next digit.
		if (charToInt(integer[i]) == -1) // if returned -1, being the error number
		{
			//std::cout << "Invalid character used!\n";
			return -1;
		}
		else
			newInt += charToInt(integer[i]); //begin collecting numbers
	}
	return newInt;
}

double stringToDouble(std::string numberString) 
{
	double finalNumber{ 0.0 };
	int decimalsUsed{ 0 }; //initialize variables
	bool invalidCharUsed{ false };
	unsigned int positionOfDecimal{ numberString.size() };//set it to the length of the string by default. 

	//using an unsigned int because a decimal position will be positive or zero by default, and will likely not get too big.
	for (unsigned int i = 0; i < numberString.size(); i++)
		//Likewise, i will be unsigned for the < operator
	{
		if (numberString[i] == '.') {
			positionOfDecimal = i + 1;
			decimalsUsed++;
			continue;
		}
		if (i > 0)
			finalNumber *= 10; // multiply by 10 to add the next number as it is still above the decimal

		if (charToInt(numberString[i]) == -1) // if returned -1, being the error number
		{
			invalidCharUsed = true;
			break;
		}

		else
			finalNumber += charToInt(numberString[i]); //begin collecting numbers
	}
	if (decimalsUsed > 1)
	{
		std::cout << "Too many decimals used! \n";//error message
		return -1;
	}
	else if (invalidCharUsed)
	{
		std::cout << "Invalid character used! \n";
		return -1; //error number
	}
	else {
		//at the end divide the number according to the decimal
		finalNumber *= 1 / pow(10, (numberString.size() - positionOfDecimal));
		return finalNumber;
	}
}

std::string filterString(std::string prompt, int numberOfSpaces, std::string allowedCharacters)
{
	std::string unfilteredString{};
	while (true) 
	{
		unfilteredString =  stringInput(prompt);
		if (checkString(unfilteredString, numberOfSpaces, allowedCharacters))
		{
			std::cout << "Your input contains an invalid character. Please try again.\n";
		}
		else
			break;//exit loop
	}
	//ask for string
	//go through string and pick up on number of spaces, any special characters, and numbers
	// if number of spaces, special characters, or numbers rules are violated, go back to beginning an ask for string again. 
	//otherwise return the string
	return unfilteredString;
}

bool checkString(std::string stringRequireCheck, int numberOfSpaces, std::string allowedCharacters) 
{
	int spacesUsed{ 0 };
	for (unsigned int i = 0; i < stringRequireCheck.size(); i++)
	{
		if (stringRequireCheck[i] == ' ')
			spacesUsed++;
	}

	if (hasUndesiredCharacter(stringRequireCheck, allowedCharacters) || spacesUsed > numberOfSpaces)
	{
		return false; //if error in text
	}
	else
		return true;
}

bool hasUndesiredCharacter(std::string string, std::string allowedCharacters) 
{
	if (string.find_first_not_of(allowedCharacters) != std::string::npos)//will return true if not found
		return true;
	else
		return false;
} //takes in allowed list of characters and check to see if a unusuable character is included, if so it will return true. 
//Source: https://stackoverflow.com/questions/6605282/how-can-i-check-if-a-string-has-special-characters-in-c-effectively

bool hasCharacter(char character, std::string allowedCharacters) //to check individual characters since the filterString function is too non-specific
{
	for (unsigned int i = 0; i < allowedCharacters.size(); i++)
	{
		if (character == allowedCharacters[i])
			return true;
	}
	return false;
}

std::string combineChars(char a, char b) 
{
	char firstChar = a;
	char secondChar = b;
	std::string combinedChars{ "" };
	combinedChars += firstChar;
	combinedChars += secondChar;
	return combinedChars;
}



int intFromRange_Inclusive(int min, int max, std::string prompt)
{
	int unfixedInt{};

	while (true) 
	{
		unfixedInt = intInput(prompt);
		if (unfixedInt < min || unfixedInt > max)
		{
			std::cout << "input out of range.\n Max: " << max << " Min: " << min << '\n'; // this line can be reused and refactored into a function
			//for 
		}
		else
			break; //exit loop
	}
	return unfixedInt;
	
}//includes min and max