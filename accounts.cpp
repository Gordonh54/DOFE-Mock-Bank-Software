#include "pch.h"
#include "io.h"
#include "file_handling.h"
#include "accounts.h"



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
		std::string allUserInfo{ intToString(accountOpen) + '\n' + userId + '\n' + userName + '\n' + /*include later personal information*/ doubleToString(accountBalance) + '\n' + collectTransactionHistory()};
		file << allUserInfo; 
		file.close(); 
		//collect all user info
		//output it all into the file, overwrite everything
		//close file
	}
}

/*
bool baseAccount::checkUserContent(std::string id, std::string name, std::string DoB, double balance, std::vector<std::string> history)
{
	//check id: match file id with inside id
	//check name: go through filtering
	//check date of birth: filter 
	//check money: filter and count # of decimals
	//check transaction history: for each item need to check for correct formats
}
*/

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

bool filterUserId(std::string testUserId)
{
	if (testUserId.size() != 5 /*check # of correct digits*/ || hasUndesiredCharacter(testUserId, "0123456789") || !(lookupFile(testUserId)))
		return false;
	return true;
}

//function to detect if file has incorrect information
// check to see if it has correct ID, name, DoB, money, transaction history, etc. 
// will not check if there is missing information 
// 
// lookup file function already exists
// 
//planning on having administrator accounts that also inherit from baseAccount.