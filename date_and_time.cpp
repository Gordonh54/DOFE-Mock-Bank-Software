#include "pch.h"
#include <time.h>
#include "date_and_time.h"

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


