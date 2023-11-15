
#include "Menu.h"
#include "Utils.h"

#include <thread>
#include <iostream>
#include <algorithm>

#include <conio.h>

void Menu::add_option(const string& option)
{
	options.push_back(option);
}

const int Menu::display_menu() const
{
	int current_index = 0;

	while (true)
	{
		clear_console();
		cout << "***** " << name << " *****\n" << endl;

		for (int i = 0; i < options.size(); i++)
			if (i == current_index)
				cprint(string(to_string(i + 1) + ") " + options[i]).c_str(), GREEN);
			else
				cout << (i + 1) << ") " << options[i] << endl;

		cout << "\nUser the arrow keys to navigate and Enter to select option" << endl;

		switch (int c = _getch())
		{
		case UP_ARROW:
			current_index = (current_index - 1 + (int)options.size()) % options.size();
			break;
		case DOWN_ARROW:
			current_index = (current_index + 1) % options.size();
			break;
		case ENTER_KEY:
			return current_index;
		}
	}
}

void Menu::set_name(const string& new_name)
{
	name = new_name;
}
