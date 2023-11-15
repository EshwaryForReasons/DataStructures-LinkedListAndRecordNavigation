
#pragma once

#include <string>

using namespace std;

/**
    Represents basic person information, like name
*/
class Person
{
public:

    Person() = default;
    Person(string _first_name, string _middle_name, string _last_name)
        : first_name(_first_name)
        , middle_name(_middle_name)
        , last_name(_last_name)
    {}

    Person operator=(const Person& other);
    const bool operator==(const Person& other);
    const bool operator!=(const Person& other);

    //Returns a comma separated list of format firstname,middlename,lastname,role,organization
    virtual const std::string to_string() const;
    //Same as to_string, but this time each property is on a new line and labeled
    virtual const std::string to_labeled_string() const;
    //Same as to_string, but it is now split into uniform columns
    virtual const std::string to_column_string() const;

    //Setters
    void set_first_name(string new_first_name) {first_name = new_first_name;}
    void set_middle_name(string new_middle_name)  {middle_name = new_middle_name;}
    void set_last_name(string new_last_name) {last_name = new_last_name;}

    //Getters
    const string& get_first_name() const {return first_name;}
    const string& get_middle_name() const {return middle_name;}
    const string& get_last_name() const {return last_name;}

    const pair<string, string> retrieve_comparision_string(const Person& other) const;

protected:

    string first_name;
    string middle_name;
    string last_name;
};