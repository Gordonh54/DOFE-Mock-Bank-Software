#include "pch.h"

//currently this file only holds random number generation. 


int randomIntRange(int min, int max) 
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<> distr(min, max); // define the range
	return distr(gen);
	//https://stackoverflow.com/questions/7560114/random-number-c-in-some-range <- source
}




int stackInts(int currentInt, unsigned int resetCount) 
{
	static unsigned int intStackCount{ 0 };
	static int stackingInt{ 0 };
	if (intStackCount == 0)
		stackingInt = 0;

	stackingInt += currentInt;


	if (intStackCount > resetCount)
	{
		intStackCount = 0;
		return stackingInt;
	}
	else 
	{
		intStackCount++;
		stackingInt *= 10;
		return 0;
	}
		
} //an idea for a function to "stack" multiple integer numbers onto each other. Currently unused
