#ifndef MENU_H
#define MENU_H

#include "pch.h"
#include "accounts.h"

void mainMenu();

void accountMenu(std::string userLoginId);

void accountInformationMenu(baseAccount& userAccount);

void manageAccountMenu();

void accountLoginMenu();

void createMenuOptions(std::string option1 = "", std::string option2 = "", std::string option3 = "");

#endif

