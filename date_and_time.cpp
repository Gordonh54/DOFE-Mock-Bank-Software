#include "pch.h"
#include <time.h>
#include "date_and_time.h"
#include "io.h"
#include "account_creation.h"

#define __STDC_WANT_LIB_EXT1__ 1
//localtime_s formatting: https://en.cppreference.com/w/c/chrono/localtime 
// https://stackoverflow.com/questions/35258285/how-to-use-localtime-s-with-a-pointer-in-c
// 
//format retrieved from: https://www.tutorialspoint.com/cplusplus/cpp_date_time.htm 


std::string giveDateAndTime() 
{
	struct std::tm localt;
	std::time_t t{ std::time(0) };
	localtime_s(&localt, &t);

	//create the strings from scratch from its different parts from struct and put it together through custom format due to previous DoB methods
	int year = localt.tm_year + 1900;
	std::string yearStr = std::to_string(year);
	int month = localt.tm_mon + 1;
	std::string monthStr = addLeadingZero(month);
	int day = localt.tm_mday;
	std::string dayStr = addLeadingZero(day);
	int hour = localt.tm_hour;
	std::string hourStr = addLeadingZero(hour);
	int minute = localt.tm_min;
	std::string minuteStr = addLeadingZero(minute);
	int second = localt.tm_sec;
	std::string secondStr = addLeadingZero(second);

	std::string timeString{ monthStr + "/" + dayStr + "/" + yearStr + " " + 
	hourStr + ":" + minuteStr + ":" + secondStr };
	
	return timeString;
}

std::string addLeadingZero(int num) 
{
	if (num < 10)
	{
		return ("0" + std::to_string(num));
	}
	else
		return std::to_string(num);
}

//check on the date and time part of the transaction history
bool validateDateAndTime(std::string dateAndTimeString) 
{
	//validate date string and time string
	std::string dateString{ dateAndTimeString.substr(0,10) };
	std::string timeString{ dateAndTimeString.substr(11, 8) }; //separate the transaction message into parts
	if (filterDateOfBirth(dateString) && validateTime(timeString))
	{
		return true;
	}
	else
		return false;
}

//check only the time part of the transaction message
bool validateTime(std::string timeString) 
{
	int hours{};
	int minutes{};
	int seconds{};
	try 
	{
		hours = stringToInt2(timeString.substr(0, 2));
		minutes = stringToInt2(timeString.substr(3, 2));
		seconds = stringToInt2(timeString.substr(6, 2));
		//BUG: have not adjusted for trailing 0s. Currently, the seconds section can be missing a trailing 0 and this would still pass true. 
		//However, for the transaction history message only, it would not change much as it would pick up the error later.
	}
	catch (std::out_of_range message)
	{
		return false;
	}
	catch (std::invalid_argument)
	{
		return false;
	}//if somehow the conversion does not go correctly

	if (hours < 0 || hours > 24 || minutes < 0 || minutes > 60 || seconds < 0 || seconds > 60 || timeString[2] != ':' || timeString[5] != ':') //if incorrect number format
	{
		return false;
	}

	return true;
}
