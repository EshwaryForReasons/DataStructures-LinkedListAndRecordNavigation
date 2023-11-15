
#pragma once

#include <string>
#include <vector>

using namespace std;

/**
	Base menu class, simply displays menu
*/
class Menu
{
public:

	Menu() {};
	Menu(string _name)
		: name(_name)
	{}
	~Menu() = default;

	void set_name(const string& new_name);

	void add_option(const string& option);

	const int display_menu() const;

	const vector<string>& get_options() const {return options;}

private:

	string name;
	vector<string> options;
};
