
#include "DiscussionList.h"
#include "Discussion.h"

#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>

static const string DISCUSSIONS_DATA = "discussions.dat";

InfoTypes DiscussionList::CurrentComparisionField = INFO_NONE;

static LinkedList<Discussion>* sorted_discussions = nullptr;

void DiscussionList::init_discussions()
{
	clear();

	ifstream in_file(DISCUSSIONS_DATA);

	if (in_file.fail())
		cout << "Failed to open " << "discussions.dat" << " file!" << endl;

	Person person;
	string title;
	DateTime date_and_time;
	string content;

	//We use a rolling integer to keep track of which data we are collecting; 0 - name, 1 - title, 2 - date and time, 3 content
	int current_data_collected = 0;

	//Construct a Discussion and put it in the discussion_list for every discussion in the file
	string read_data;
	while (getline(in_file, read_data))
	{
		//Read next data type
		bool b_continue_to_next = true;
		switch (current_data_collected)
		{
		case 0:
		{
			stringstream name_stream(read_data);
			vector<string> name;
			string name_portion;
			while (getline(name_stream, name_portion, ' '))
				name.push_back(name_portion);
			//If vector has three things then we have a middle name
			person = Person(name[0], name.size() == 3 ? name[1] : "", name[name.size() == 3 ? 2 : 1]);
			break;
		}
		case 1:
		{
			title = read_data;
			break;
		}
		case 2:
		{
			date_and_time = DateTime(read_data);
			break;
		}
		case 3:
		{
			//If field contains \ then we continue reading the next line
			if (read_data.find("\\") != string::npos)
			{
				//Remove the slash
				read_data.erase(read_data.size() - 1);
				b_continue_to_next = false;
			}
			
			content += read_data;

			if (b_continue_to_next)
			{
				insert(new Discussion(person, title, date_and_time, content));
				content = "";
			}

			break;
		}
		}

		if(b_continue_to_next)
			current_data_collected = ++current_data_collected % 4;
	}

	in_file.close();
}

void DiscussionList::update_discussions_file()
{
	fstream file(DISCUSSIONS_DATA, ios::out);

	if (file.fail())
		cout << "Failed to open " << "discussions.dat" << " file!" << endl;

	for(Node<Discussion> node : *this)
		file << node.data->get_person().to_string() << "\n" << node.data->get_title() << "\n" << node.data->get_date_and_time().to_string() << "\n" << node.data->get_content() << endl;

	file.close();
}

void DiscussionList::print_list(InfoTypes _CurrentComparisionField, bool b_ascending)
{
	DiscussionList::CurrentComparisionField = _CurrentComparisionField;

	LinkedList<Discussion> sorted_discussions(*this);
	sorted_discussions.sort_list(b_ascending);

	//Print header
	cout << left;
	cout << setw(MEDIUM_COLUMN_WIDTH) << "First Name";
	cout << setw(SHORT_COLUMN_WIDTH) << "M";
	cout << setw(MEDIUM_COLUMN_WIDTH) << "Last Name";
	cout << setw(LONG_COLUMN_WIDTH) << "Date and Time";
	cout << setw(SUPER_LONG_COLUMN_WIDTH) << "Title";
	cout << endl << endl;

	for(Node<Discussion> node : sorted_discussions)
		cout << node.data->to_column_string() << "\n";

	cout << endl;
}

void DiscussionList::view_discussion_details(const string& first_name)
{
	cout << find_discussion(first_name)->to_labeled_string() << endl;
}

void DiscussionList::add_discussion(Discussion* new_discussion)
{
	insert(new_discussion);
	update_discussions_file();
}

void DiscussionList::edit_discussion(const string& first_name, const Discussion& edited_discussion)
{
	*find_discussion(first_name) = edited_discussion;
	update_discussions_file();
}

void DiscussionList::remove_discussion(const string& first_name)
{
	remove(find_discussion(first_name));
	update_discussions_file();
}

Discussion* DiscussionList::find_discussion(const string& first_name)
{
	DiscussionList::CurrentComparisionField = INFO_FIRST_NAME;
	sorted_discussions = new LinkedList<Discussion>((*this));
	sorted_discussions->sort_list(true);

	int low = 0;
	int high = sorted_discussions->num_elements - 1;

	// Perform binary search
	int i = -1;
	while (low <= high)
	{
		const int mid = ((high - low) / 2) + low;

		if(compare_strings((*sorted_discussions)[mid]->data->get_person().get_first_name(), first_name) == 2)
			high = mid - 1;
		else if ((*sorted_discussions)[mid]->data->get_person().get_first_name() == first_name)
		{
			i = mid;
			break;
		}
		else
			low = mid + 1;
	}

	return (*sorted_discussions)[i]->data;
}