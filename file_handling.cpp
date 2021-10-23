#include "pch.h"
#include "file_handling.h"

void createNewFile(std::string name, std::string id, std::string dateOfBirth) //create new file to put information within
{
	std::fstream newFile; //create string object "newFile"
	newFile.open("accounts/" + id + ".txt", std::ios_base::out); //open file with output:
	//std::ios_base::out is for output
	//std::ios_base::in is for input
	//std::ios_base::app is for appending file information
	if (newFile.is_open())
	{
		newFile << name << '\n' << dateOfBirth;
		newFile.close();
		if (newFile.is_open())
			std::cout << "Stream could not close!\n";
	}
	else
		std::cout << "File could not be opened!";
}

std::string processFileInfo();

bool lookupFile(std::string id) 
{
	std::fstream file;
	file.open("accounts/" + id + ".txt", std::ios_base::in);
	if (file.is_open())
	{
		file.close();
		if (file.is_open())
			std::cout << "Stream could not close!\n";
		return true;
	}
	else 
	{
		return false;
	}

	/*
	File Format:
	- ID
	- Name
	- Date of Birth
	- any future personal information
	- Bank Balance
	- Transaction History (which can be appended)
	*/


