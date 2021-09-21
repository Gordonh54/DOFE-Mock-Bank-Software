#ifndef IO_H
#define IO_H

#include <string>

void print(std::string message);

int intInput(std::string prompt);

double doubleInput(std::string prompt);

std::string stringInput(std::string prompt);

std::string getInput(std::string prompt);

int charToInt(char number);

std::string intToString(int intValue);

std::string doubleToString(double doubleValue);

int intFromRange_Inclusive(int min, int max, std::string prompt);


#endif


