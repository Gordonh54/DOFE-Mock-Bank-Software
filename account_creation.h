#ifndef ACCOUNT_CREATION_H
#define ACCOUNT_CREATION_H

std::string createRandomId();

std::string getAccountName();

bool filterDateOfBirth(std::string dobInput);

std::string getDateOfBirth();

bool createNewAccount();

#endif
