#include "pch.h"
#include "io.h"

std::string createRandomId() 
{
	;//create random numbers and letters? will return as a string.
}

bool checkMatchingId(std::string id)
{
	;//checks accross files to find any matching ids 
}

std::string getName() 
{
	std::cout << "What is your name?\n";
	//get string output
	//filter it with restrictions.
	// 
	;
}

class baseAccount
{	
	public: 
		baseAccount() {
			//create:
			// - new ID
			// - ask for name
			// - ask for DoB
			// - ...
			//
			;
		}
		void displayAccountInfo() 
		{
			;
		} //display basic account info
		void displayBankBalance() 
		{
			; 
		}// note that the balance will always be at 2 decimal places
	protected:
		std::string userName;
		std::string Id;
		std::string dateOfBirth; //basic account information that all accounts will start with.
	
};

//class of regular account that inherits from baseAccount
//planning on having administrator accounts that also inherit from baseAccount.