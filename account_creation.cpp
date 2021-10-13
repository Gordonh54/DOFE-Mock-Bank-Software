#include "pch.h"
#include "io.h"
#include "numbers.h"
#include "account_creation.h"

namespace charSets
{
	std::string nameChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; //all characters allowed in names. Should one include periods and dashes?
	int spacesAllowedInNames = 5; //set it to 5 for now, currently unsure
}; 

std::string createRandomId() 
{
	//Current constant for the number of digits an ID should have: 5 Digits 
	//therefore 100000 different current accounts if only using characters from 0-9.
	constexpr int idLength = 5;
	//The following variable outlines the digit range for current ids. It will not support letter characters as of now.
	//the range is inclusive
	constexpr int numberOfIdCharacters[2] = { 0, 9 };
	

	std::string generatedId{}; 
	while (true) {
		int idInt{ 0 }; //random numbers will be stacked onto this

		for (int i = 0; i < idLength; i++)//stacking the random numbers
		{
			if (i > 0)
				idInt *= 10; //multiply by ten to stack numbers

			idInt += randomIntRange(numberOfIdCharacters[0], numberOfIdCharacters[1]);
		}

		generatedId = intToString(idInt);

		if (checkMatchingId(generatedId))
			break;//if found no match in database, break from loop as this is a new ID
	} 


	return generatedId;//create random numbers and letters? will return as a string.
}

bool checkMatchingId(std::string id)
{
	;//checks accross files to find any matching ids 
	return true;
}

//function to create new account
void createNewAccount() 
{
	std::string newAccountName{ filterString("Please enter your name:", charSets::spacesAllowedInNames, charSets::nameChars)}; //creates new name
	//the above function can be refined to make the name filtering more accurate (e.g. permitting capital letters in names)
	std::string newID{ createRandomId() };
	std::cout << newAccountName << " " << newID;
	std::string dateOfBirth{};
	// ask for:
	// - ID
	// - name
	// - DoB

	//if nothing is cancelled mid-account creation we will store to file. 
}

