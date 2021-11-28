#include "pch.h"
#include "io.h"
#include "numbers.h"
#include "account_creation.h"
#include "file_handling.h"

namespace charSets
{
	std::string nameChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; //all characters allowed in names. Should one include periods and dashes?
	int spacesAllowedInNames = 5; //set it to 5 for now, currently unsure
	std::string numbers = "0123456789";
	std::string dateOfBirthChars = numbers + "/";
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
		generatedId = intToString(randomIntRange(numberOfIdCharacters[0], numberOfIdCharacters[1])); //random numbers will be stacked onto this

		for (int i = 0; i < idLength-1 /*now that we initialize with the first character, we only need to add 1 less char to string*/; i++)//stacking the random numbers
		{
			generatedId += intToString(randomIntRange(numberOfIdCharacters[0], numberOfIdCharacters[1]));
		}

		if (!lookupFile(generatedId))//attempt to open a file with this id. If it cannot find a file with this id, then it is a unique id.
			break;//if found no match in database, break from loop as this is a new ID
		//if that was not true we randomly generate a new id
	} 

	return generatedId;//Should this id create random numbers and letters? will return as a string.
}

//function to create new account
bool createNewAccount() 
{
	std::string newAccountName{ getAccountName()}; //creates new name
	//the above function can be refined to make the name filtering more accurate (e.g. permitting capital letters in names)
	std::string newID{ createRandomId() };
	std::string dateOfBirth{ getDateOfBirth() };

	createNewFile(newAccountName, newID, dateOfBirth);
	if (lookupFile(newID)) //if you can open the file
	{
		std::cout << "Account Made Successfully! \n" << "Your Account ID is: " << newID << '\n';
		return true;
	}
	else
	{
		std::cout << "Account creation failed!\n";
		return false;
	}

		

	// ask for:
	// - ID
	// - name
	// - DoB

	//if nothing is cancelled mid-account creation we will store to file. 
}

std::string getAccountName() 
{
	return filterString("Please enter your name:", charSets::spacesAllowedInNames, charSets::nameChars);
}

std::string getDateOfBirth()
{
	std::string dateOfBirth{};
	while (true) 
	{
		dateOfBirth = filterString("Please enter your date of birth: \nMM/DD/YYYY", 0/*no spaces in date of birth*/, charSets::dateOfBirthChars);
		if (dateOfBirth.size() != 10)
			continue;
		if (filterDateOfBirth(dateOfBirth))
			break;
	}
	
	return dateOfBirth;
}

bool filterDateOfBirth(std::string dobInput)
{	
	std::string monthStr{ combineChars(dobInput[0], dobInput[1]) };
	std::string dayStr{ combineChars(dobInput[3], dobInput[4]) };
	std::string yearStr1{ combineChars(dobInput[6], dobInput[7]) };
	std::string yearStr2{ combineChars(dobInput[8],dobInput[9]) };
	std::string yearStr{ yearStr1 + yearStr2 };

	if (hasUndesiredCharacter(monthStr, charSets::numbers) || hasUndesiredCharacter(dayStr, charSets::numbers) || hasUndesiredCharacter(yearStr, charSets::numbers))
		return false; //if the dates themselves have /, this function will return false.
	if (dobInput[2] != '/' || dobInput[2] != dobInput[5])
		return false; //check formatting of slashes

	int monthInt{ stringToInt(monthStr) };
	int dayInt{ stringToInt(dayStr) };
	int yearInt{ stringToInt(yearStr) };

	switch (monthInt)
	{
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		if (dayInt < 1 || dayInt > 31)
			return false;
		else
			break;
	case 4:
	case 6:
	case 9:
	case 11:
		if (dayInt < 1 || dayInt > 30)
			return false;
		else 
			break;
	case 2:
		 if (dayInt < 0 || (dayInt > 28 && (yearInt%4 != 0))) // modulus 4 because all leap years are divisible by 4
			 return false;
		 if (dayInt != 29)
			 return false;
	default:
		return false;
	}

	return true;
}
