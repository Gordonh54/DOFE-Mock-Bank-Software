#include "pch.h"
#include "io.h"
#include "file_handling.h"
#include "accounts.h"
#include "account_creation.h"
#include "char_sets.h"
#include "date_and_time.h"

//planning on having administrator accounts that also inherit from baseAccount.
//

//constructor to load all user information
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
			transactionHistory.push_back(line);//using "transactionHistory" as a temporary vector to hold all information. bad practice but it works
		}
		int j{ 0 };
		accountOpen = stringToInt( transactionHistory[j++] );
		userId = transactionHistory[j++];
		userName = transactionHistory[j++];
		dateOfBirth = transactionHistory[j++];
		accountBalance = stringToInt(transactionHistory[j++]); //validate that the value is numeric before saving
		for (int i = 0; i < 5; i++) //delete first 5 items of vector: account open status, id, name, dob, balance, and leave history behind; 
		{
			transactionHistory.erase(transactionHistory.begin());
		}
	}
	file.close();
}

//access private variable accountOpen
void baseAccount::closeAccount()
{
	accountOpen = false;
}

//overwrite everything with current class info for whenever we modify the profile (add money, transactionHistory, etc.)
void baseAccount::saveAccountInfo()
{
	//first, if the EMPTY is still shown at the front of the transaction history when there are other items, just remove it
	if (transactionHistory.size() > 1 && transactionHistory[0] == "EMPTY")
	{
		transactionHistory.erase(transactionHistory.begin());//removes first
	}

	//collect all user info
	//output it all into the file, overwrite everything
	//close file
	std::fstream file;
	file.open(fileName(userId), std::ios_base::out);
	if (file.is_open())
	{
		std::string allUserInfo{ intToString(accountOpen) + '\n' + userId + '\n' + userName + '\n' + dateOfBirth + '\n' +/*include later personal information*/ intToString(accountBalance) + '\n' + collectTransactionHistory() };
		file << allUserInfo;
		file.close();
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

//incomplete
void baseAccount::displayTransactionHistory()
{
	if (transactionHistory[0] != "EMPTY")
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

bool filterUserId(std::string testUserId) // if incorrect id, return false
{
	if (testUserId.size() != 5 /*check # of correct digits*/ || hasUndesiredCharacter(testUserId, "0123456789") || !(lookupFile(testUserId)))
		return false;
	return true;
}

bool filterUserBalance(int testUserBalance) 
{
	if (testUserBalance >= 0)
		return true;
	else
		return false;
}

bool baseAccount::accountOpenStatus() 
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
	else if (!(filterUserBalance(accountBalance)))
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


//functions are called from main menu
//note: saveAccountInfo() is used very often and is repeated especially in transferFunds(). This could slow things down later on.
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
	createTransactionLog(deposit, "deposit");
}

void baseAccount::withdrawMoney(int withdrawal)
{
	if (checkIfSufficientFunds(withdrawal))
	{
		subtractFunds(withdrawal);
		displayBankBalance();
		createTransactionLog(withdrawal, "withdraw");
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


void baseAccount::transferFunds(int quantity, std::string targetId)
{
	subtractFunds(quantity);
	displayBankBalance();
	createTransactionLog(quantity, "transfer");

	//we add money to the other account we want to transfer to
	baseAccount transferAccount(targetId);
	transferAccount.addFunds(quantity);
	transferAccount.createTransactionLog(quantity, "receive");
}

//transactionType is assumed to be either "withdraw", "deposit", "transfer", or "receive"
void baseAccount::createTransactionLog(int transferredFunds, std::string transactionType)
{

	std::string transactionMessage{giveDateAndTime() + " " + transactionType + " " + std::to_string(transferredFunds)};

	transactionHistory.push_back(transactionMessage);
	//append a message to transactionHistory<>
	saveAccountInfo();
}

bool checkAccountOpen(std::string id) 
{
	baseAccount testAccount(id);
	return testAccount.accountOpenStatus();
}