// DOFE Mock Bank Software.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "io.h"
#include "menu.h"
#include "numbers.h"
#include "account_creation.h"
#include "accounts.h"
#include "file_handling.h"
#include "date_and_time.h"

#include <iostream>
#include <string>

//note: if error message appears that the app cannot be opened for writing, try closing the .exe in task manager

int main()
{
    
    // bug - >      std::cout << validateDateAndTime("03/20/2022 07:13:4");
    mainMenu();
}


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
