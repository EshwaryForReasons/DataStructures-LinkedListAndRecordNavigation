
#include "Discussion.h"
#include "DiscussionList.h"

#include <iomanip>
#include <sstream>

Discussion Discussion::operator=(const Discussion& other)
{
	person = other.person;
	title = other.title;
	date_and_time = other.date_and_time;
	content = other.content;
	return Discussion(person, title, date_and_time, content);
}

const bool Discussion::operator==(const Discussion& other)
{
	return (person == other.person && title == other.title && date_and_time == other.date_and_time && content == other.content);
}

const bool Discussion::operator!=(const Discussion& other)
{
	return (person != other.person || title != other.title || date_and_time != other.date_and_time || content == other.content);
}

const bool Discussion::operator<(const Discussion& other) const
{
	const std::pair<string, string> strings = retrieve_comparision_string(other);
	return compare_strings(strings.first, strings.second) == 1;
}

const bool Discussion::operator>(const Discussion& other) const
{
	const std::pair<string, string> strings = retrieve_comparision_string(other);
	return compare_strings(strings.second, strings.first) == 1;
}

const string Discussion::to_string() const
{
	return "";
}

const string Discussion::to_labeled_string() const
{
	stringstream formatted;
	formatted << left;
	formatted << person.to_labeled_string();

	formatted << setw(COLUMN_WIDTH) << "Title:" << title << endl;
	formatted << setw(COLUMN_WIDTH) << "Date and Time:" << date_and_time.to_string() << endl;
	formatted << setw(COLUMN_WIDTH) << "Content:" << content << endl;
	return formatted.str();
}

const string Discussion::to_column_string() const
{
	stringstream formatted;
	formatted << left;
	formatted << person.to_column_string();
	formatted << setw(LONG_COLUMN_WIDTH) << date_and_time.to_string();
	formatted << setw(SUPER_LONG_COLUMN_WIDTH) << title;
	return formatted.str();
}

const pair<string, string> Discussion::retrieve_comparision_string(const Discussion& other) const
{
	string our_field;
	string other_field;

	switch (DiscussionList::CurrentComparisionField)
	{
	case INFO_TITLE:
	{
		our_field = title;
		other_field = other.title;
		break;
	}
	case INFO_DATE_AND_TIME:
	{
		our_field = date_and_time.to_string();
		other_field = other.date_and_time.to_string();
		break;
	}
	case INFO_CONTENT:
	{
		our_field = content;
		other_field = other.content;
		break;
	}
	//If we are comparing a person field
	case INFO_NONE:
	case INFO_FIRST_NAME:
	case INFO_MIDDLE_NAME:
	case INFO_LAST_NAME:
	{
		return person.retrieve_comparision_string(other.person);
	}
	};

	return std::pair<string, string>(our_field, other_field);
}