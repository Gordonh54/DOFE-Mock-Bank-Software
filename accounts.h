#ifndef ACCOUNTS_H
#define ACCOUNTS_H

class baseAccount
{
public: 
	baseAccount(std::string id);
	const void displayAccountInfo();
	std::string giveUserId();
	void displayBankBalance();
	void displayTransactionHistory();
	void saveAccountInfo();
	std::string collectTransactionHistory();
	//bool checkUserContent(std::string id, std::string name, std::string DoB, double balance, std::vector<std::string> history);
	void closeAccount();

	//vaidation of user information
	bool checkUserId();
	bool checkAccountOpen();
	bool checkUserName();
	bool checkUserBalance();
	bool checkUserDateOfBirth();

	//managing money
	
	void depositMoney(int deposit);
	void withdrawMoney(int withdrawal);
	bool checkIfSufficientFunds(int requestedWithdrawal);
	void transferFunds(int quantity, std::string targetId);

protected:
	void addFunds(int changeInQuantity);
	void subtractFunds(int changeInQuantity);

	std::string userName;
	std::string userId;
	std::string dateOfBirth; //basic account information that all accounts will start with.
	std::vector<std::string> transactionHistory;
	int accountBalance;
	bool accountOpen;
};

bool filterUserId(std::string testUserId);
bool filterUserBalance(int testUserBalance);
bool checkAccountBalance(int accountBalance);
bool checkUserContent(std::string userId);


#endif

