#ifndef ACCOUNTS_H
#define ACCOUNTS_H

class baseAccount
{
public: 
	baseAccount(std::string id);
	void displayAccountInfo();
	std::string giveUserId();
	void displayBankBalance();
	void displayTransactionHistory();
	void saveAccountInfo();
	std::string collectTransactionHistory();
	bool checkUserContent(std::string id, std::string name, std::string DoB, double balance, std::vector<std::string> history);
	bool checkUserId();
	void closeAccount();

protected:
	std::string userName;
	std::string userId;
	std::string dateOfBirth; //basic account information that all accounts will start with.
	std::vector<std::string> transactionHistory;
	int accountBalance;
	bool accountOpen;
};

#endif

