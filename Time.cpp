
#include "Time.h"

const bool Time::operator==(const Time& other) const
{
	return (hour == other.hour && minute == other.minute && second == other.second);
}

const bool Time::operator!=(const Time& other) const
{
	return (hour != other.hour || minute != other.minute || second != other.second);
}

void Time::set_hour(int new_hour)
{
	hour = new_hour;
}

void Time::set_minute(int new_minute)
{
	minute = new_minute;
}

void Time::set_second(int new_second)
{
	second = new_second;
}

int Time::get_hour() const
{
	return hour;
}

int Time::get_minute() const
{
	return minute;
}

int Time::get_second() const
{
	return second;
}

const string Time::to_string() const
{
	return to_string_fill_space(hour, 2) + ":" + to_string_fill_space(minute, 2) + ":" + to_string_fill_space(second, 2);
}

const string Time::to_string_fill_space(int num, int min) const
{
	string temp = std::to_string(num);
	if (temp.size() < min)
	{
		const int places_to_fill = min - (int)temp.size();
		for (int i = 0; i < places_to_fill; ++i)
			temp = "0" + temp;
	}
	return temp;
}