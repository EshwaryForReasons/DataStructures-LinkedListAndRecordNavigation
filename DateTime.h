
#pragma once

#include "Time.h"

#include <string>

using namespace std;

/**
	Extends the time class to handle dates as well
*/
class DateTime : public Time
{
public:

	DateTime() = default;
	DateTime(int _hour, int _minute, int _second, int _day, int _month, int _year)
		: Time(_hour, _minute, _second)
		, day(_day)
		, month(_month)
		, year(_year)
	{}
	DateTime(int _day, int _month, int _year)
		: day(_day)
		, month(_month)
		, year(_year)
	{}
	//String format mm/dd/yyyy hh:mm:ss
	DateTime(const string& string_date_time);
	~DateTime() = default;

	const bool operator==(const DateTime& other) const;
	const bool operator!=(const DateTime& other) const;

	void set_day(int new_day);
	void set_month(int new_month);
	void set_year(int new_year);

	int get_day() const;
	int get_month() const;
	int get_year() const;

	virtual const string to_string() const override;

private:

	int day;
	int month;
	int year;
};

