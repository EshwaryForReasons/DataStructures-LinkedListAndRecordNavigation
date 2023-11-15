
#include "DateTime.h"

#include <sstream>

DateTime::DateTime(const string& string_date_time)
{
	string _month;
	string _day;
	string _year;
	string _hour;
	string _minute;
	string _second;

	stringstream ss(string_date_time);
	getline(ss, _month, '/');
	getline(ss, _day, '/');
	getline(ss, _year, ' ');
	getline(ss, _hour, ':');
	getline(ss, _minute, ':');
	getline(ss, _second, ' ');

	set_hour(stoi(_hour));
	set_minute(stoi(_minute));
	set_second(stoi(_second));
	day = stoi(_day);
	month = stoi(_month);
	year = stoi(_year);
}

const bool DateTime::operator==(const DateTime& other) const
{
	return (Time::operator==(other) && day == other.day && month == other.month && year == other.year);
}

const bool DateTime::operator!=(const DateTime& other) const
{
	return (Time::operator!=(other) || day != other.day || month != other.month || year != other.year);
}

void DateTime::set_day(int new_day)
{
	day = new_day;
}

void DateTime::set_month(int new_month)
{
	month = new_month;
}

void DateTime::set_year(int new_year)
{
	year = new_year;
}

int DateTime::get_day() const
{
	return day;
}

int DateTime::get_month() const
{
	return month;
}

int DateTime::get_year() const
{
	return year;
}

const string DateTime::to_string() const
{
	return to_string_fill_space(month, 2) + "/" + to_string_fill_space(day, 2) + "/" + to_string_fill_space(year, 4) + " " + Time::to_string();
}