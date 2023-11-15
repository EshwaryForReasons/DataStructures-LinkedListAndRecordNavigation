
#include "Person.h"
#include "Discussion.h"
#include "DiscussionList.h"
#include "Utils.h"

#include <sstream>
#include <iomanip>

Person Person::operator=(const Person& other)
{
    first_name = other.get_first_name();
    middle_name = other.get_middle_name();
    last_name = other.get_last_name();
    return Person(first_name, middle_name, last_name);
}

const bool Person::operator==(const Person& other)
{
	return (first_name == other.first_name && middle_name == other.middle_name && last_name == other.last_name);
}

const bool Person::operator!=(const Person& other)
{
    return (first_name != other.first_name || middle_name != other.middle_name || last_name != other.last_name);
}

const string Person::to_string() const
{
    return get_first_name() + " " + get_middle_name() + " " + get_last_name();
}

const string Person::to_labeled_string() const
{
    stringstream formatted;
	formatted << left;
	formatted << setw(COLUMN_WIDTH) << "First Name:" << get_first_name() << endl;
	formatted << setw(COLUMN_WIDTH) << "Middle Name:" << get_middle_name() << endl;
	formatted << setw(COLUMN_WIDTH) << "Last Name:" << get_last_name() << endl;
    return formatted.str();
}

const string Person::to_column_string() const
{
    stringstream formatted;
    formatted << left;
    formatted << setw(MEDIUM_COLUMN_WIDTH) << get_first_name();
	formatted << setw(SHORT_COLUMN_WIDTH) << get_middle_name();
	formatted << setw(MEDIUM_COLUMN_WIDTH) << get_last_name();
    return formatted.str();
}

const pair<string, string> Person::retrieve_comparision_string(const Person& other) const
{
    string our_field;
    string other_field;

    switch(DiscussionList::CurrentComparisionField)
    {
    case INFO_NONE:
    case INFO_FIRST_NAME:
    {
        our_field = first_name;
        other_field = other.first_name;
        break;
    }
    case INFO_MIDDLE_NAME:
    {
        our_field = middle_name;
        other_field = other.middle_name;
        break;
    }
    case INFO_LAST_NAME:
    {
        our_field = last_name;
        other_field = other.last_name;
        break;
    }
    };

    return pair<string, string>(our_field, other_field);
}