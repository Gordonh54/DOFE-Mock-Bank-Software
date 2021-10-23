#ifndef FILE_HANDLING_H
#define FILE_HANDLING_H

#include "pch.h"

void createNewFile(std::string name, std::string id, std::string dateOfBirth);

bool lookupFile(std::string id);
#endif
