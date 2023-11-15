
#pragma once

#include <string>

using namespace std;

/**
	Handles time related things. Used for storing and modifying time
*/
class Time
{
public:

	Time() = default;
	Time(int _hour, int _minute, int _second)
		: hour(_hour)
		, minute(_minute)
		, second(_second)
	{}
	~Time() = default;

	const bool operator==(const Time& other) const;
	const bool operator!=(const Time& other) const;

	void set_hour(int new_hour);
	void set_minute(int new_minute);
	void set_second(int new_second);

	int get_hour() const;
	int get_minute() const;
	int get_second() const;

	virtual const string to_string() const;

protected:

	//Since we store data as integers, information from the sheet is lost. For example 09 becomes 9. So, this function re-adds the 0
	const string to_string_fill_space(int num, int min) const;

private:

	int hour;
	int minute;
	int second;
};