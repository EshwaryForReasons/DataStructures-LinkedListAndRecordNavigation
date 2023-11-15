
#define _CRT_SECURE_NO_WARNINGS // supress localtime warning

#include "Utils.h"
#include "DateTime.h"

#include <fstream>
#include <ctime>
#include <sstream>
#include <iostream>

#include <windows.h>

void clear_console()
{
#ifdef _WIN32
	system("cls");
#elif __linux__
	system("clear");
#endif
}

void cprint(const string& message, int color)
{
#ifdef _WIN32
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hConsole, color);
	cout << message << endl;

	//Reset color after printing
	SetConsoleTextAttribute(hConsole, WHITE);
#elif __linux__
	cout << color != WHITE ? "* " : "" << message << endl;
#endif
}

void get_current_time(int& mo, int& d, int& yr, int& hr, int& min, int& sec)
{
	time_t t = std::time(0);
	tm* now = localtime(&t);

	mo = now->tm_mon + 1;
	d = now->tm_mday;
	yr = now->tm_year + 1900;

	hr = now->tm_hour;
	min = now->tm_min;
	sec = now->tm_sec;
}

DateTime get_current_time()
{
	int month;
	int day;
	int year;
	int hour;
	int minute;
	int second;
	get_current_time(month, day, year, hour, minute, second);
	return DateTime(hour, minute, second, day, month, year);
}

static const string lowercase(const string& s)
{
	string temp = s;
	for (auto& x : temp)
		x = tolower(x);
	return temp;
}

const int compare_strings(const string& a, const string& b)
{
	//Lowercase so the difference in ASCII for capital and lowercase do not interfere with comparison
	const string ac = lowercase(a);
	const string bc = lowercase(b);

	for (int i = 0; i < ac.size(); ++i)
	{
		//Less in ASCII means higher in alphabet
		if ((int)ac[i] < (int)bc[i])
			return 1;
		else if ((int)ac[i] > (int)bc[i])
			return 2;
	}

	return 0;
}