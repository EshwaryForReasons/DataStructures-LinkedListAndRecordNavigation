
#include "DiscussionMenu.h"
#include "DiscussionList.h"
#include "Menu.h"
#include "Utils.h"

#include <thread>
#include <iostream>
#include <conio.h>

static void block_and_go_back()
{
	cout << "Press q to go back." << endl;

	int input = _getch();

	if (input != Q_KEY)
		block_and_go_back();
	else
		cout << "Going back..." << endl;
}

DiscussionMenu::DiscussionMenu()
{
	set_name("Discussion Menu");
	add_option("List Discussions");
	add_option("Navigate Discussions");
	add_option("View a Discussion");
	add_option("Add Discussion");
	add_option("Edit Discussion");
	add_option("Delete Discussion");
	add_option("Exit");

	discussions = new DiscussionList();
	discussions->init_discussions();

	sort_direction_menu = new Menu();
	sort_direction_menu->set_name("Select Direction To Sort");
	sort_direction_menu->add_option("Ascending");
	sort_direction_menu->add_option("Descending");
	
	sort_field_menu = new Menu();
	sort_field_menu->set_name("Select Field To Sort By");
	sort_field_menu->add_option("First Name");
	sort_field_menu->add_option("Middle Name");
	sort_field_menu->add_option("Last Name");
	sort_field_menu->add_option("Title");
	sort_field_menu->add_option("Date and Time");
	sort_field_menu->add_option("Content");
}

DiscussionMenu::~DiscussionMenu()
{
	delete sort_field_menu;
	delete sort_direction_menu;
	delete discussions;
}

void DiscussionMenu::begin()
{
	bool b_exit = false;

	while (!b_exit)
	{
		clear_console();
		int selected_option = display_menu();
		clear_console();

		if (selected_option == DISCUSSION_MENU_LIST)
		{
			list_discussions();
			block_and_go_back();
		}
		else if (selected_option == DISCUSSION_MENU_NAVIGATE)
		{
			navigate_discussions();
		}
		else if (selected_option == DISCUSSION_MENU_VIEW_DETAILS)
		{
			view_discussion_details();
		}
		else if (selected_option == DISCUSSION_MENU_ADD)
		{
			add_discussion();
			block_and_go_back();
		}
		else if (selected_option == DISCUSSION_MENU_EDIT)
		{
			edit_discussion();
			block_and_go_back();
		}
		else if (selected_option == DISCUSSION_MENU_DELETE)
		{
			delete_discussion();
			block_and_go_back();
		}
		else if (selected_option == DISCUSSION_MENU_EXIT)
		{
			cout << "Goodbye!" << endl;
			b_exit = true;
		}

		this_thread::sleep_for(1s);
	}
}

void DiscussionMenu::list_discussions()
{
	const int direction_option = sort_direction_menu->display_menu();
	clear_console();

	const int field_option = sort_field_menu->display_menu();
	clear_console();

	discussions->print_list(InfoTypes(field_option), direction_option == 0);
}

void DiscussionMenu::navigate_discussions()
{
	const int direction_option = sort_direction_menu->display_menu();
	const int field_option = sort_field_menu->display_menu();
	clear_console();

	DiscussionList::CurrentComparisionField = InfoTypes(field_option);

	LinkedList<Discussion> sorted_discussions(*discussions);
	sorted_discussions.sort_list(direction_option == 0);

	LinkedList<Discussion>::Iterator it = sorted_discussions.begin();

	//Perform navigation
	bool b_continue_navigation = true;
	while (b_continue_navigation)
	{
		clear_console();

		cout << "****************************************\n"
			 << "Up Arrow - First Element\n"
			 << "Down Arrow - Last Element\n"
			 << "Left Arrow - Previous Element\n"
			 << "Right Arrow - Next Element\n"
			 << "q - Go Back\n"
			 << "r - Resort\n"
			 << "****************************************\n"
			 << endl;

		cout << it->data->to_labeled_string() << endl;

		switch (_getch())
		{
		case UP_ARROW:
			it = sorted_discussions.begin();
			break;
		case DOWN_ARROW:
			it = --sorted_discussions.end(true);
			break;
		case LEFT_ARROW:
		{
			if(it != sorted_discussions.begin())
				--it;
			break;
		}
		case RIGHT_ARROW:
		{
			if (it->next)
				++it;
			break;
		}
		case R_KEY:
			navigate_discussions();
		case Q_KEY:
			b_continue_navigation = false;
			break;
		}
	}
}

void DiscussionMenu::view_discussion_details()
{
	clear_console();
	cout << "***** View Disucssion Details *****\n" << endl;

	discussions->print_list(INFO_FIRST_NAME, true);

	string first_name;
	cout << "Enter discussion author's first name: ";
	getline(cin, first_name);

	clear_console();

	cout << "***** View Disucssion Details *****\n"
		 << "r - View another discussion\n"
		 << "q - Go back to menu\n"
		 << "***********************************\n"
		 << endl;
	discussions->view_discussion_details(first_name);

	//Read user input for r and q
	while (int c = _getch())
	{
		if (c == R_KEY)
		{
			view_discussion_details();
			break;
		}
		else if (c == Q_KEY)
			break;
	}
}

void DiscussionMenu::add_discussion()
{
	cout << "***** Add Discussion *****\n" << endl;

	string first_name;
	string middle_name;
	string last_name;
	string title;
	string date;
	string time;
	string content;

	//Lambda to get input from user and strip newline character
	auto get_input = [](const string& message, string& output)
	{
		cout << message;
		getline(cin, output);

		//Strip the input of the newline character to prevent problems with formatting later
		if (output.find("\r") != string::npos || output.find("\n") != string::npos)
			output.erase(output.size() - 1);
	};

	get_input("First Name: ", first_name);
	get_input("Middle Name: ", middle_name);
	get_input("Last Name: ", last_name);
	get_input("Title: ", title);
	get_input("Date (mm/dd/yyyy): ", date);
	get_input("Time (hh:mm:ss): ", time);
	get_input("Content: ", content);

	discussions->add_discussion(new Discussion(Person(first_name, middle_name, last_name), title, DateTime(date + " " + time), content));

	cout << "Discussion Added Successfully!" << endl;
}

void DiscussionMenu::edit_discussion()
{
	cout << "***** Edit Discussion *****\n" << endl;

	discussions->print_list(INFO_FIRST_NAME, true);

	string original_first_name;
	cout << "Enter discussion author's first name: ";
	getline(cin, original_first_name);

	Discussion const* discussion = discussions->find_discussion(original_first_name);

	clear_console();

	string first_name = discussion->get_person().get_first_name();
	string middle_name = discussion->get_person().get_middle_name();
	string last_name = discussion->get_person().get_last_name();
	string title = discussion->get_title();
	string date_and_time = discussion->get_date_and_time().to_string();
	string content = discussion->get_content();

	//Lambda to get input from user and strip newline character
	auto get_input = [](const string& message, string& output)
	{
		cout << message;
		string temp;
		getline(cin, temp);

		//Strip the input of the newline character to prevent problems with formatting later
		if (output.find("\r") != string::npos || output.find("\n") != string::npos)
			output.erase(output.size() - 1);

		//Only update if user actually entered new information
		if(temp != "")
			output = temp;
	};

	get_input("First Name (" + first_name + "): ", first_name);
	get_input("Middle Name (" + middle_name + "): ", middle_name);
	get_input("Last Name (" + last_name + "): ", last_name);
	get_input("Title (" + title + "): ", title);
	get_input("Date and Time (" + date_and_time + "): ", date_and_time);
	get_input("Content (" + content + "): ", content);

	discussions->edit_discussion(original_first_name, Discussion(Person(first_name, middle_name, last_name), title, DateTime(date_and_time), content));

	cout << "Discussion Edited Successfully!" << endl;
}

void DiscussionMenu::delete_discussion()
{
	cout << "***** Delete Discussion *****\n" << endl;

	discussions->print_list(INFO_FIRST_NAME, true);

	string first_name;
	cout << "Enter discussion author's first name: ";
	getline(cin, first_name);

	discussions->remove_discussion(first_name);

	cout << "Discussion Deleted Successfully!" << endl;
}