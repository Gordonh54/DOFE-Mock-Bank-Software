#include "pch.h"
#include "io.h"

class baseAccount
{
public:
	baseAccount() {
		//input:
		// - ID
		// - name
		// - DoB
		// - bank balance
		// - transaction history
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
protected: //inherited classes can access
	std::string userName;
	std::string Id;
	std::string dateOfBirth; //basic account information that all accounts will start with.

};


//planning on having administrator accounts that also inherit from baseAccount.