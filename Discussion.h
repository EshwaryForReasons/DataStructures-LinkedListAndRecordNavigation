
#pragma once

#include "Person.h"
#include "DateTime.h"

#include <string>

using namespace std;

/**
	Represents a discussion and stores all information about it
*/
class Discussion
{
public:

	Discussion()
		: person(Person())
		, title("")
		, date_and_time(DateTime())
		, content("")
	{}
	Discussion(const Person& _person, const string& _title, const DateTime& _date_and_time, const string& _content)
		: person(_person)
		, title(_title)
		, date_and_time(_date_and_time)
		, content(_content)
	{}

	Discussion operator=(const Discussion& other);
	const bool operator==(const Discussion& other);
	const bool operator!=(const Discussion& other);
	const bool operator<(const Discussion& other) const;
	const bool operator>(const Discussion& other) const;

	//Returns a comma seperated list of format firstname,middlename,lastname,title,dateandtime,content
	virtual const string to_string() const;
	//Same as to_string, but this time each property is on a new line and labeled
	virtual const string to_labeled_string() const;
	//Same as to_string, but it is now split into uniform columns
	virtual const string to_column_string() const;

	void set_person(Person new_person) {person = new_person;}
	void set_title(string new_title) {title = new_title;}
	void set_date_and_time(DateTime new_date_and_time) {date_and_time = new_date_and_time;}
	void set_content(string new_post) {content = new_post;}

	const Person& get_person() const {return person;}
	const string& get_title() const {return title;}
	const DateTime& get_date_and_time() const {return date_and_time;}
	const string& get_content() const {return content;}

private:

	Person person;
	string title;
	DateTime date_and_time;
	string content;

	const pair<string, string> retrieve_comparision_string(const Discussion& other) const;
};

