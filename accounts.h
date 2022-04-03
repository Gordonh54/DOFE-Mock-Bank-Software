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
	bool accountOpenStatus();
	bool checkUserName();
	bool checkUserBalance();
	bool checkUserDateOfBirth();
	void filterTransactionHistory(std::vector<std::string> transactionHistory);

	//managing money
	
	void depositMoney(int deposit);
	void withdrawMoney(int withdrawal);
	bool checkIfSufficientFunds(int requestedWithdrawal);
	void transferFunds(int quantity, std::string targetId);
	void createTransactionLog(int transferredFunds, std::string transactionType);

protected:
	void addFunds(int changeInQuantity);
	void subtractFunds(int changeInQuantity);

	std::string userName;
	std::string userId;
	std::string dateOfBirth; //basic account information that all accounts will start with.
	std::vector<std::string> transactionHistory;
	std::vector<std::string> printTransactionHistory; //this one is never saved as it is just a temporary vector for printing
	int accountBalance;
	bool accountOpen;
};


//general checking account information, can be moved to another file if i really want to
bool filterUserId(std::string testUserId);
bool filterUserBalance(int testUserBalance);
bool checkAccountBalance(int accountBalance);
bool checkUserContent(std::string userId);
bool checkTransactionHistory(std::string transactionHistory);

//this function is generally for accessing other accounts when already within one (a quick way to check if an account is open)
bool checkAccountOpen(std::string id);
#endif

