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
		std::string line{};
		while (std::getline(file, line))
		{
			transactionHistory.push_back(line);
		}
		userId = transactionHistory[0];
		userName = transactionHistory[1];
		dateOfBirth = transactionHistory[2];
		accountBalance = stringToDouble(transactionHistory[3]);
		for (int i = 0; i < 4; i++) //delete first 4 items
		{
			transactionHistory.erase(transactionHistory.begin());
		}
	}
	file.close();
}
void baseAccount::displayAccountInfo()
{
	std::cout << userName << "\nID: " << userId << "\nDate of Birth: " << dateOfBirth << '\n';
} //display basic account info
void baseAccount::displayBankBalance()
{
	std::cout << "Current Balance: " << accountBalance << '\n';
}// note that the balance will always be at 2 decimal places
void baseAccount::displayTransactionHistory()
{
	if (transactionHistory[0] == "EMPTY") return;//early exit

	for (unsigned int i = 0; i < transactionHistory.size(); i++)
	{
		std::cout << transactionHistory[i] << '\n';
	}
}



//planning on having administrator accounts that also inherit from baseAccount.