
#pragma once

#include <iostream>

using namespace std;

/**
	Node class for the linked list, stores reference to next and previous nodes and data
*/
template<typename T>
class Node
{
public:

	T* data = nullptr;
	Node* next = nullptr;
	Node* previous = nullptr;
};

/**
	Iterator for the linked list. Contains all appropriate iterator things
*/
template<typename LinkedList>
class Iterator
{
public:

	//Make functions easier to read
	using ValueType = typename LinkedList::ValueType;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;

	Iterator(PointerType pointer)
		: current(pointer)
	{}

	Iterator operator++() {current = current->next; return *this;}
	Iterator operator--() {current = current->previous; return *this;}
	const bool operator==(const Iterator& other) const {return current == other.current;}
	const bool operator!=(const Iterator& other) const {return current != other.current;}
	ReferenceType operator[](int index) {return current[index];}
	PointerType operator->() {return current;}
	ReferenceType operator*() {return *current;}

private:

	PointerType current;
};

/**
	Linked list class. Stores reference to first node and functions to manage list
*/
template<typename T>
class LinkedList
{
public:

	using ValueType = Node<T>;
	using Iterator = Iterator<LinkedList>;

	LinkedList() = default;
	LinkedList(const LinkedList<T>& _list);

	~LinkedList() {clear();}

	Node<T>* first = nullptr;
	int num_elements = 0;

	Node<T>* operator[](int pos) const;

	//Inserts an element to the end of the list
	void insert(T* new_element);

	//Removes element from pos index
	void remove(T* element_to_remove);

	//Removes all elements from the list
	void clear();

	//Sorts the list using quicksort
	void sort_list(bool b_ascending);

	Iterator begin();
	//If reversable is trye we create an iterator which points to a node the previous of which is the last node in the list; otherwise the iterator pointer is nullptr
	Iterator end(bool b_reversable = false);

protected:

	//Swaps the data in the provided nodes
	void swap(Node<T>* a, Node<T>* b);

	//Quicksort requires a helper function to partition the array; this function returns the picot
	Node<T>* partition(Node<T>* start, Node<T>* end, bool b_ascending);

	//Quick sorts the list. Quicksort is a recursive algorithm that follows the divide and conquer technique
	void quick_sort(Node<T>* start, Node<T>* end, bool b_ascending);
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList<T>& _list)
{
	for (Node<T>* i = _list.first; i != nullptr; i = i->next)
	{
		insert(i->data);
	}
}

template<typename T>
Node<T>* LinkedList<T>::operator[](int pos) const
{
	Node<T>* temp = first;
	int i = 0;
	while (i < pos)
	{
		temp = temp->next;
		i++;
	}
	return temp;
}

template<typename T>
void LinkedList<T>::insert(T* new_element)
{
	num_elements++;

	Node<T>* new_node = new Node<T>();
	new_node->data = new_element;

	//Made sure we have a first node
	if (!first)
	{
		first = new_node;
		return;
	}

	//Add new node to the next of the list
	Node<T>* temp = first;
	while (temp->next != nullptr)
		temp = temp->next;
	new_node->previous = temp;
	temp->next = new_node;
}

template<typename T>
void LinkedList<T>::remove(T* element_to_remove)
{
	//Get reference to node to remove based on the data in the node
	bool b_found_node = false;
	Node<T>* node_to_remove = first;
	for (; node_to_remove != nullptr; node_to_remove = node_to_remove->next)
		if (node_to_remove->data == element_to_remove)
		{
			b_found_node = true;
			break;
		}

	if(!b_found_node)
		return;

	num_elements--;

	node_to_remove->previous->next = node_to_remove->next;
	node_to_remove->next->previous = node_to_remove->previous;
	delete node_to_remove;
}

template<typename T>
void LinkedList<T>::clear()
{
	//To clear list, we can work backwards. We will get the last node and delete all backwards
	Node<T>* current_last_node = first;

	if(!current_last_node)
		return;

	while (current_last_node->next)
		current_last_node = current_last_node->next;

	//Traverse backwards deleting the nodes as we go
	while (current_last_node->previous)
	{
		current_last_node = current_last_node->previous;
		delete current_last_node->next;
	}

	delete first;
}

template<typename T>
void LinkedList<T>::swap(Node<T>* a, Node<T>* b)
{
	T x = *a->data;
	*a->data = *b->data;
	*b->data = x;
	a = a->next;
}

template<typename T>
Node<T>* LinkedList<T>::partition(Node<T>* start, Node<T>* end, bool b_ascending)
{
	T* pivot_data = end->data;
	Node<T>* i = start->previous;

	for (Node<T>* j = start; j != nullptr; j = j->next)
	{
		if (b_ascending ? *(j->data) < *pivot_data : *(j->data) > *pivot_data)
		{
			i = i == nullptr ? start : i->next;
			swap(j, i);
		}
	}

	i = i == nullptr ? start : i->next;
	swap(i, end);
	return i;
}

template<typename T>
void LinkedList<T>::quick_sort(Node<T>* start, Node<T>* end, bool b_ascending)
{
	if (end && start != end && start != end->next)
	{
		Node<T>* pivot = partition(start, end, b_ascending);
		quick_sort(start, pivot->previous, b_ascending);
		quick_sort(pivot->next, end, b_ascending);
	}
}

template<typename T>
void LinkedList<T>::sort_list(bool b_ascending)
{
	quick_sort(first, operator[](num_elements - 1), b_ascending);
}

template<typename T>
Iterator<LinkedList<T>> LinkedList<T>::begin()
{
	return Iterator(first);
}

template<typename T>
Iterator<LinkedList<T>> LinkedList<T>::end(bool b_reversable)
{
	if (b_reversable)
	{
		Node<T>* end_node = new Node<T>();
		end_node->previous = operator[](num_elements - 1);
		return Iterator(end_node);
	}
	return Iterator(nullptr);
}