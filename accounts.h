#ifndef ACCOUNTS_H
#define ACCOUNTS_H

class baseAccount
{
public: 
	baseAccount(std::string id);
	void displayAccountInfo();
	void displayBankBalance();
	void displayTransactionHistory();
protected:
	std::string userName;
	std::string userId;
	std::string dateOfBirth; //basic account information that all accounts will start with.
	std::vector<std::string> transactionHistory;
	double accountBalance;
};

#endif

