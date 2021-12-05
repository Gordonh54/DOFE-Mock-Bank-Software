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

	do {
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
			manageAccountMenu();
			break;
		case 0:
			stayInMenu = false;
			break;
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

		//displayAccountInfo();
		createMenuOptions(); // no options except for [0] back
		navigationChoice = intFromRange_Inclusive(0, 0, "Enter your navigation choice: ");

		switch (navigationChoice) //very redundant right now
		{
		case 0:
			stayInMenu = false;
			break;
		}
	} while (stayInMenu);
	//exit to caller
}

void manageAccountMenu()
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
	do {
		std::cout << "Account Menu\n";
		//displayBasicAccountInfo
		createMenuOptions("Manage personal information", "Deposit/withdraw cash", "Manage transactions");
		navigationChoice = intFromRange_Inclusive(0, 3, "Enter your navigation choice: ");

		switch (navigationChoice)
		{
		case 1:
			//manageAccountInformationMenu();
			break;
		case 2:
			//manageBalanceMenu();
			break;
		case 3: 
			//manageTransactionMenu();
			break;
		case 0:
			stayInMenu = false;
			break;
		}
	} while (stayInMenu);
	//exit to caller
}

void createMenuOptions(std::string option1, std::string option2, std::string option3)
{
	//unless string option is empty we can display it as an option
	if (option1 != "")
		std::cout << "[1] " << option1 << '\n';
	if (option2 != "")
		std::cout << "[2] " << option2 << '\n';
	if (option3 != "")
		std::cout << "[3] " << option3 << '\n';

	//regardless in all menu options the [0] one must be present
	std::cout << menuBackOption;

}