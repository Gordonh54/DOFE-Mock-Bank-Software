#ifndef MENU_H
#define MENU_H

#include "pch.h"
#include "accounts.h"

void mainMenu();

void accountMenu(std::string userLoginId);

void accountInformationMenu(baseAccount& userAccount);

void manageAccountMenu(baseAccount& userAccount);

void manageBalanceMenu(baseAccount& userAccount);

void depositMenu(baseAccount& userAccount);

void withdrawMenu(baseAccount& userAccount);

void accountLoginMenu();

void createMenuOptions(std::string option1 = "", std::string option2 = "", std::string option3 = "", std::string option4 = "");

#endif

