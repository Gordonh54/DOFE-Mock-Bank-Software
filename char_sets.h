#pragma once

namespace charSets
{
	std::string nameChars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ "; //all characters allowed in names. Should one include periods and dashes?
	int spacesAllowedInNames = 5; //set it to 5 for now, currently unsure
	std::string numbers = "0123456789";
	std::string dateOfBirthChars = numbers + "/";
};