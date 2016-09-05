// BirthDateApp.cpp : Defines the entry point for the console application.
//

#define _CRT_SECURE_NO_WARNINGS

#include "stdafx.h"
#include <iostream>
#include <string>
#include <ctime>

using namespace std;

clock_t start = clock();

time_t currentTime = time(NULL);
char* charTime = ctime(&currentTime);
tm* my_time = localtime(&currentTime);

struct tm * getBirthday() {
	time_t rawtime;
	struct tm * timeinfo;
	int year, month, day;

	// Days of the week needed to make tm_wday readable.

	cout << "Welcome to Birthday Calculator!" << endl << endl;
	cout << "Current time is: " << charTime << endl << endl;

	cout << "The Current Date is: " << my_time->tm_mon << "/" << my_time->tm_mday << "/" << 1900 + my_time->tm_year << endl;

	cout << "-----------------------------------------------" << endl;
	cout << "Please enter your birthday" << endl;
	cout << "What is the month of your birthday? ";
	cin >> month;
	cout << "What is the day of your birthday? ";
	cin >> day;
	cout << "What is the year of your birthday? ";
	cin >> year;

	/* get current timeinfo and modify it to the user's choice */
	time(&rawtime);
	timeinfo = localtime(&rawtime);
	timeinfo->tm_year = year - 1900;
	timeinfo->tm_mon = month - 1;
	timeinfo->tm_mday = day;

	/* call mktime: timeinfo->tm_wday will be set */
	mktime(timeinfo);

	return timeinfo;
}

const char * getWeekdayReadable(int dayofweek) {
	const char * weekday[] = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

	return weekday[dayofweek];
}

struct tm * getTimeInfo() {
	return getBirthday();
}

int calcTimeAlive() {
	time_t now = time(NULL);
	
	int diff = difftime(now, mktime(getTimeInfo()));

	return diff;
}

int main()
{
	struct tm * timeinfo = getTimeInfo();

	string readableDate = to_string(timeinfo->tm_mon + 1) + "/" + to_string(timeinfo->tm_mday) + "/" + to_string(timeinfo->tm_year + 1900);

	time_t now = time(NULL);
	if (difftime(now, mktime(timeinfo)) > 0 || mktime(timeinfo) == -1) { // A date is returned as -1 if it is before the epoch time (1970).
		cout << readableDate << " was a " << getWeekdayReadable(timeinfo->tm_wday) << "." << endl;
	}
	else {
		cout << readableDate << " is a " << getWeekdayReadable(timeinfo->tm_wday) << "." << endl;
	}

	double diff = calcTimeAlive();
	cout << "You have been alive for " << diff << " seconds, " << endl;
	cout << "or " << diff / 60 << " minutes," << endl;
	cout << "or " << diff / 60 / 60 << " hours," << endl;
	cout << "or " << diff / 60 / 60 / 24 << " days," << endl;
	cout << "or " << diff / 60 / 60 / 24 / 365.242<< " years." << endl;

	system("PAUSE");

	return 0;
}
