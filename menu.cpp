#include "pch.h"
#include "menu.h"
#include "io.h"
#include "account_creation.h"
#include "accounts.h"

/*
MENU FORMAT

while true loop
{

display menu options

collect user input within valid range

if entering further into the menu, call that menu function

if exiting this menu and going out to parent menu, break loop, thus going back to caller.
}
*/

const std::string menuBackOption{ "\n\n[0] Back\n" };

void mainMenu() 
{
	//messages for main menu
	/*
	
	Main Menu
	[1] Access account (or maybe go straight to login)
	[2] Create new account

	[0] Exit

	collect input for navigation
	*/
	bool stayInMenu{ true };
	int navigationChoice{};
	do {
		std::cout << "Main Menu \n";
		createMenuOptions("Access account", "Create new account"); 
		navigationChoice = intFromRange_Inclusive(0, 2, "Enter your navigation choice: ");
		switch (navigationChoice) //this switch case is relatively redundant for main menu currently, but I'll leave it as is for a future change.
		{
		case 1:
			accountLoginMenu();
			break;
		case 2:
			createNewAccount();
			break;
		case 0:
			stayInMenu = false;
			break;
		}
	} while (stayInMenu);
	//return to caller
}

void accountLoginMenu() 
{
	std::cout << "Login Menu\n";
	std::string userLoginInput{};
	while (true)
	{
		userLoginInput = stringInput("Login with ID" + menuBackOption);
		if (filterUserId(userLoginInput))
		{
			//check account details here before loading, if it works then pass. If not, then we should flag it as bad
			if (!(checkUserContent(userLoginInput)))
			{
				break;
			}
			accountMenu(userLoginInput);
			break; //exit to main menu
		}
		else if (stringToInt(userLoginInput) == 0)
		{
			break;
		}
		else
		{
			std::cout << "Account not found\n\n";
		}

	}
	//look for ID, if found, enter account menu
	//if it is zero, exit

}

void accountMenu(std::string userLoginId)
{
	//load account information by creating class object.
	/* 
	displayBasicAccountInfo();
	Features:
	* Account Name: abc
	* ID: 01234

	[1] View information
	[2] Manage accounts

	[0] Back



	collect input for navigation
	*/
	bool stayInMenu{ true }; // for the loop
	int navigationChoice{}; //avoid re-initialization, so put outside of loop
	baseAccount userAccount(userLoginId); //load account
	//load account info and check for inconsistencies
	do {
		// 2 menus: open and closed
		
		//closed account menu
		if (!userAccount.accountOpenStatus())
		{
			std::cout << "Account is Closed\n";
			accountInformationMenu(userAccount); //take to user information menu as there is nothing here to do
			stayInMenu = false; //immediately exit
			break;
		}

		// opened account menu
		else if (userAccount.accountOpenStatus()) 
		{
			std::cout << "Account Menu\n";
			//displayBasicAccountInfo();
			createMenuOptions("View information", "Manage accounts");
			navigationChoice = intFromRange_Inclusive(0, 2, "Enter your navigation choice: ");

			switch (navigationChoice)
			{
			case 1:
				accountInformationMenu(userAccount);
				break;
			case 2:
				manageAccountMenu(userAccount);
				if (!userAccount.accountOpenStatus()) //if account was closed during account management
					stayInMenu = false;
				break;
			case 0:
				stayInMenu = false;
				break;
			}
		}
	} while (stayInMenu);
	//exit to caller
}

void accountInformationMenu (baseAccount& userAccount) //read only, in a later time make it const baseAccount& userAccount
{
	//account info should still be saved
	/*
	displayAccountInfo(); // the function for all accout info that shows account personal information, balance, and history
	Display name  
	Display ID
	Display other personal information

	[0] Back
	*/
	bool stayInMenu{ true }; // for the loop
	int navigationChoice{}; //avoid re-initialization, so put outside of loop
	do {
		std::cout << "Account Information Menu\n";
		userAccount.displayAccountInfo();
		userAccount.displayBankBalance();

		createMenuOptions("View transaction history"); // no options except for [0] back
		navigationChoice = intFromRange_Inclusive(0, 1, "Enter your navigation choice: ");

		switch (navigationChoice)
		{
		case 1:
			userAccount.displayTransactionHistory();
			break;
		case 0:
			stayInMenu = false;
			break;
		}

	} while (stayInMenu);
	//exit to caller
}

void manageAccountMenu(baseAccount& userAccount)
{
	//account info should still be saved
	/*
	[1] Manage personal information
	[2] Deposit/withdraw cash
	[3] Manage transactions

	[0] Back
	*/
	bool stayInMenu{ true }; // for the loop
	int navigationChoice{}; //avoid re-initialization, so put outside of loop
	int closeAccountChoice{};
	do {
		std::cout << "Account Menu\n";
		createMenuOptions("Manage personal information", "Deposit/withdraw funds", "Manage transactions", "Close Account");
		navigationChoice = intFromRange_Inclusive(0, 4, "Enter your navigation choice: ");

		switch (navigationChoice)
		{
		case 1:
			//manageAccountInformationMenu();
			break;
		case 2:
			manageBalanceMenu(userAccount);
			break;
		case 3: 
			manageTransactionsMenu(userAccount);
			break;
		case 4: 
			std::cout << "Are you sure you want to close your account?\n";
			createMenuOptions("Yes", "No");
			switch (intFromRange_Inclusive(0, 2, ""))
			{
			case 1:
				userAccount.closeAccount();
				userAccount.saveAccountInfo();
				//save Accountinfo
				stayInMenu = false;
				break;

			case 0:
			case 2: //if No or Back
				break;
			}
		case 0:
			stayInMenu = false;
			break;
		}
	} while (stayInMenu);
	//exit to caller
}

void manageBalanceMenu(baseAccount& userAccount)
{
	/*
	[1] Deposit Funds
	[2] Withdraw Funds

	[0] Back
	*/
	bool stayInMenu{ true }; // for the loop
	int navigationChoice{}; //avoid re-initialization, so put outside of loop
	do {
		std::cout << "Manage Balance\n";
		createMenuOptions("Deposit Funds", "Withdraw Funds");
		navigationChoice = intFromRange_Inclusive(0, 2, "Enter your navigation choice: ");

		switch (navigationChoice)
		{
		case 1:
			depositMenu(userAccount);
			break;
		case 2:
			withdrawMenu(userAccount);
			break;
		case 0:
			stayInMenu = false;
			break;
		}
	} while (stayInMenu);
}

void depositMenu(baseAccount& userAccount) 
{
	userAccount.depositMoney(intInput("State the amount:"));
}

void withdrawMenu(baseAccount& userAccount)
{
	userAccount.withdrawMoney(intInput("State the amount:"));
}

void manageTransactionsMenu(baseAccount& userAccount)
{
	bool stayInMenu{ true }; // for the loop
	int navigationChoice{}; //avoid re-initialization, so put outside of loop
	std::string transactionId{};
	int transactionFunds{};

	std::cout << "Transaction Menu\nEnter 0 to exit\n\n";
	do {
		
		transactionId = stringInput("Enter the ID you want to enter:\n"); //check for 3 things if not ID: [1] if it is 0 or if it is the identical ID as user. 
		bool isValidId = filterUserId(transactionId);
		if (transactionId == "0")
			break;
		else if (transactionId == userAccount.giveUserId())
		{
			//probably give an error message stating why 
			continue;
		}
		else if (!isValidId)
			continue;
		else if (!checkAccountOpen(transactionId))
		{
			std::cout << "Invalid target: Account closed.\n";
			continue;
		}

		transactionFunds = intInput("Enter the quantity of funds you want to transfer to this account:\n"); //check if valid submission
		if (transactionFunds == 0)
			break;
		else if (!(filterUserBalance(transactionFunds)))
			continue; 

		userAccount.transferFunds(transactionFunds, transactionId);
	} while (stayInMenu);
}

void createMenuOptions(std::string option1, std::string option2, std::string option3, std::string option4)
{
	//unless string option is empty we can display it as an option
	if (option1 != "")
		std::cout << "[1] " << option1 << '\n';
	if (option2 != "")
		std::cout << "[2] " << option2 << '\n';
	if (option3 != "")
		std::cout << "[3] " << option3 << '\n';
	if (option4 != "")
		std::cout << "[4] " << option4 << '\n';

	//regardless in all menu options the [0] one must be present
	std::cout << menuBackOption;

} //Is there a way the function can take a list of inputs and treat it as one vector? If so this function can be made more concise.
/*
createMenuOptions(options);
navigationChoice = intFromRange_Inclusive(0, x, "Enter your navigation choice: ");

switch (navigationChoice)

In general this should be factored down into one step
*/