
#pragma once

#include <string>

using namespace std;

//Define a clear function based on OS the code is compiled for since there is no standard way to do this
void clear_console();

//Define some keycodes for navigation
#define UP_ARROW 72
#define DOWN_ARROW 80
#define LEFT_ARROW 75
#define RIGHT_ARROW 77
#define Q_KEY 113
#define R_KEY 114
#define ENTER_KEY 13

//Define some console colors to format output
#define WHITE 15
#define GREEN 2

enum InfoTypes
{
	INFO_FIRST_NAME = 0,
	INFO_MIDDLE_NAME = 1,
	INFO_LAST_NAME = 2,
	INFO_TITLE = 3,
	INFO_DATE_AND_TIME = 4,
	INFO_CONTENT = 5,
	INFO_NONE = 6
};

const int COLUMN_WIDTH = 20;
const int SUPER_LONG_COLUMN_WIDTH = 35;
const int LONG_COLUMN_WIDTH = 25;
const int MEDIUM_COLUMN_WIDTH = 16;
const int SHORT_COLUMN_WIDTH = 7;

//Prints parameter to console with provided color
void cprint(const string& message, int color);

//Returns the system time
void get_current_time(int& mo, int& d, int& yr, int& hr, int& min, int& sec);
class DateTime get_current_time();

//Compare two strings alphabetically; 0 if both are the same, 1 if first is larger, 2 if second is larger
const int compare_strings(const string& a, const string& b);