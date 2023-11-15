
#pragma once

#include "Menu.h"

enum DISCUSSION_MENU_OPTION
{
	DISCUSSION_MENU_LIST,
	DISCUSSION_MENU_NAVIGATE,
	DISCUSSION_MENU_VIEW_DETAILS,
	DISCUSSION_MENU_ADD,
	DISCUSSION_MENU_EDIT,
	DISCUSSION_MENU_DELETE,
	DISCUSSION_MENU_EXIT
};

/**
	Handles all menu functionality and interacts with DiscussionList appropriately
*/
class DiscussionMenu : public Menu
{
public:

	DiscussionMenu();
	~DiscussionMenu();

	//Starts handling user input
	void begin();

private:

	//Display all discussion sorted in preferred manner
	void list_discussions();

	//Navigate through discussions using the arrow keys
	void navigate_discussions();

	//View the details of a single discussion
	void view_discussion_details();

	void add_discussion();
	void edit_discussion();
	void delete_discussion();

	class DiscussionList* discussions;

	class Menu* sort_direction_menu;
	class Menu* sort_field_menu;
};

