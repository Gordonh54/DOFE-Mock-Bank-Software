#include "pch.h"
#include "char_sets.h"


namespace charSets
{
	std::string nameChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; //all characters allowed in names. Should one include periods and dashes?
	const int spacesAllowedInNames{ 5 }; //set it to 5 for now, currently unsure
	std::string numbers = "0123456789";
	std::string dateOfBirthChars = numbers + "/";
};