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
			bool invalidCharUsed{ false }; // false by default

			//for loop for decoding string input
			for (unsigned int i = 0; i < currentInput.size(); i++)
			{
				if (i > 0)
					userInput *= 10; //multiply by 10 to add upon the next digit.
				if (charToInt(currentInput[i]) == -1) // if returned -1, being the error number
				{
					invalidCharUsed = true;
					break;
				}
				else
					userInput += charToInt(currentInput[i]); //begin collecting numbers
			}

			//dealing with errors
			if (invalidCharUsed)
			{
				std::cout << "Invalid character used!\n";
			}
			else
				break; //exit the loop as no errors were detected.

		}
	}
	return userInput;
}

//this function along with intInput could require some refactoring for simplification as there is overlap between the two functions. 
double doubleInput(std::string prompt)
{
	double userInput{}; //initialize user input variable
	while (true) {
		userInput = 0.0; //reset number just in case of error
		std::string currentInput{ getInput(prompt) };
		if (currentInput.size() < 1) // if nothing in the string give error
		{
			std::cout << "Invalid Input \n"; //I remember trying to input nothing but it appears that you can't. This section may or may not be irrelevant. 
		}
		else
		{
			int decimalsUsed{ 0 }; //initialize variables
			bool invalidCharUsed{ false };
			unsigned int positionOfDecimal{ currentInput.size() };//set it to the length of the string by default. 

			//using an unsigned int because a decimal position will be positive or zero by default, and will likely not get too big.
			for (unsigned int i = 0; i < currentInput.size(); i++) 
			//Likewise, i will be unsigned for the < operator
			{
				if (currentInput[i] == '.') {
					positionOfDecimal = i + 1;
					decimalsUsed++;
					continue;
				}
				if (i > 0)
					userInput *= 10; // multiply by 10 to add the next number as it is still above the decimal

				if (charToInt(currentInput[i]) == -1) // if returned -1, being the error number
				{
					invalidCharUsed = true;
					break;
				}
					
				else
					userInput += charToInt(currentInput[i]); //begin collecting numbers
			}
			if (decimalsUsed > 1) 
			{
				std::cout << "Too many decimals used! \n";//error message
			}// continue through the loop
			else if (invalidCharUsed)
			{
				std::cout << "Invalid character used! \n";
			}// continue through the loop
			else {
				//at the end divide the number according to the decimal
				userInput *= 1 / pow(10, (currentInput.size() - positionOfDecimal));
				break; //finish creating numbers and exit the loop, finally returning the number
			}
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
		std::cout << "Invalid Input! \n"; //add more rejection code later.
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

std::string filterString(std::string prompt, int numberOfSpaces, std::string allowedCharacters)
{
	std::string unfilteredString{};
	while (true) 
	{
		int spacesUsed{ 0 };
		unfilteredString =  stringInput(prompt);
		for (unsigned int i = 0; i < unfilteredString.size(); i++) 
		{
			if (unfilteredString[i] == ' ')
				spacesUsed++;
		}

		if (hasUndesiredCharacter(unfilteredString, allowedCharacters) || spacesUsed > numberOfSpaces)
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

bool hasUndesiredCharacter(std::string string, std::string allowedCharacters) 
{
	if (string.find_first_not_of(allowedCharacters) != std::string::npos)
		return true;
	else
		return false;
} //takes in allowed list of characters and check to see if a unusuable character is included, if so it will return true. 
//Source: https://stackoverflow.com/questions/6605282/how-can-i-check-if-a-string-has-special-characters-in-c-effectively
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