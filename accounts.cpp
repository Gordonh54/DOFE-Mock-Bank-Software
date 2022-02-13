#include "pch.h"
#include "io.h"
#include "file_handling.h"
#include "accounts.h"
#include "account_creation.h"
#include "char_sets.h"

//planning on having administrator accounts that also inherit from baseAccount.
baseAccount::baseAccount(std::string id)
{
	std::fstream file;
	file.open(fileName(id), std::ios_base::in);
	if (file.is_open())
	{
		/*validate information before fully loading*/
		std::string line{};
		while (std::getline(file, line))
		{
			transactionHistory.push_back(line);
		}
		int j{ 0 };
		accountOpen = stringToInt( transactionHistory[j++] );
		userId = transactionHistory[j++];
		userName = transactionHistory[j++];
		dateOfBirth = transactionHistory[j++];
		accountBalance = stringToInt(transactionHistory[j++]); //validate that the value is numeric before saving
		for (int i = 0; i < 4; i++) //delete first 4 items of vector; 
		{
			transactionHistory.erase(transactionHistory.begin());
		}
	}
	file.close();
}

void baseAccount::closeAccount()
{
	accountOpen = false;
}

void baseAccount::saveAccountInfo()
{
	std::fstream file;
	file.open(fileName(userId), std::ios_base::out);
	if (file.is_open())
	{
		std::string allUserInfo{ intToString(accountOpen) + '\n' + userId + '\n' + userName + '\n' + dateOfBirth + '\n' +/*include later personal information*/ intToString(accountBalance) + '\n' + collectTransactionHistory() };
		file << allUserInfo;
		file.close();
		//collect all user info
		//output it all into the file, overwrite everything
		//close file
	}
}

/// 
/// View account info functions
/// 
const void baseAccount::displayAccountInfo()
{
	std::cout << userName << "\nID: " << userId << "\nDate of Birth: " << dateOfBirth << '\n';
} //display basic account info

std::string baseAccount::giveUserId()
{
	return userId;
}

void baseAccount::displayBankBalance()
{
	std::cout << "Current Balance: " << accountBalance << '\n';
}// note that the balance will always be at 2 decimal places
void baseAccount::displayTransactionHistory()
{
	if (transactionHistory[0] == "EMPTY") return;//early exit
	else
		std::cout << collectTransactionHistory() << '\n';
}

std::string baseAccount::collectTransactionHistory()
{
	std::string fullTransactionHistory{transactionHistory[0]};
	if (transactionHistory.size() > 0) 
	{
		for (unsigned int i = 1; i < transactionHistory.size(); i++)
			fullTransactionHistory += ('\n' + transactionHistory[i]);
	}
	return fullTransactionHistory;
}

/// 
/// Check Account info functions
/// 


bool baseAccount::checkUserId() 
{
	if (!filterUserId(userId))
		return false; //checks if it has invalid format
	else
	{
		baseAccount testAccount(userId);
		if (testAccount.giveUserId() != userId)
			return false;
		// this method loads the same account and tries to match that contained ID with the ID 
	}

	return true;	
}

bool baseAccount::checkUserName()
{
	if (!checkString(userName, charSets::spacesAllowedInNames, charSets::nameChars))
		return false;
	else
		return true;
}

bool filterUserId(std::string testUserId)
{
	if (testUserId.size() != 5 /*check # of correct digits*/ || hasUndesiredCharacter(testUserId, "0123456789") || !(lookupFile(testUserId)))
		return false;
	return true;
}

bool baseAccount::checkAccountOpen() 
{
	return accountOpen;
}

/*
bool baseAccount::checkTransactionHistory()
{
	//check each item for correct format
	- either empty or has correct format. Cannot be empty
	//Returns true when all work. Return false if any issue arises.
}

bool filterTransactionHistory(std::vector<std::string> transactionHistory)
{
//if size is only one and says empty it is valid (also check the balance but that can be later), pass true
//otherwise filter one by one, and check format. if invalid at any point return false
//if passes through all return true
}
*/

bool baseAccount::checkUserDateOfBirth()
{
	return filterDateOfBirth(dateOfBirth);
}

bool baseAccount::checkUserBalance() //check if account balance variable is correct type or if it is not negative.
{
	int testValue{ 0 };
	if (!(typeid(testValue).name() == typeid(accountBalance).name())) //checks if it is correct data type
		return false;
	else if (accountBalance < 0)
		return false;
	else 
		return true;
}

bool checkUserContent(std::string userId)
{
	baseAccount validateAccount(userId);

	if (!(validateAccount.checkUserId() && validateAccount.checkUserName() && validateAccount.checkUserBalance()
		&& validateAccount.checkUserDateOfBirth()))
	{
		//maybe should also print error message
		//temporary:
		std::cout << "Incorrect File Information.\n";
		return false;
	}
	else
		return true;

	//check transaction history: for each item need to check for correct formats
}

///
/// Manage money account functions
/// 


//called from main menu
void baseAccount::addFunds(int changeInQuantity)
{
	accountBalance += changeInQuantity;
	saveAccountInfo();
}
void baseAccount::subtractFunds(int changeInQuantity)
{
	accountBalance -= changeInQuantity;
	saveAccountInfo();
}

void baseAccount::depositMoney(int deposit)
{
	addFunds(deposit);
	displayBankBalance();
	//displayTransactionLog();
}

void baseAccount::withdrawMoney(int withdrawal)
{
	if (checkIfSufficientFunds(withdrawal))
	{
		subtractFunds(withdrawal);
		displayBankBalance();
		//displayTransactionLog();
	}
}

bool baseAccount::checkIfSufficientFunds(int requestedWithdrawal)
{
	if (requestedWithdrawal > accountBalance)
	{
		std::cout << "You do not have enough funds.\n";
		displayBankBalance();
		return false;
	}
	else 
		return true;
}
/*
void baseAccount::transferFunds(int quantity, std::string targetId)
{
	withdrawMoney(quantity);
	baseAccount transferAccount(targetId);
	transferAccount.addFunds(quantity);
	//createTransactionLog(targetId, quantity);
}

void baseAccount::createTransactionLog()
{
	
	//append a message to transactionHistory<>
}
*/