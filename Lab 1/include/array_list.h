#pragma once
#include <iostream>

/// Making a namespace for anything that would want to access the array class
namespace ssuds
{
	/// A dynamically allocated array that can hold and give data depending
	/// on the functions that are called
	class ArrayList
	{
	/// Keeping mData and mSize private so they can't be modified outside the class
	protected:
		std::string* mData;
		unsigned int mSize;

	/// Making all the functions within the array class public
	/// and openly callable outside the class and header 
	public:
		/// The constructor of the array class
		ArrayList();
		/// The Deconstructor of the array class
		~ArrayList();
		/// A function that adds a new item  at the end of the array 
		void append(std::string new_string);
		/// Reaturns the size of the array 
		unsigned int size();
		/// Inserts a new item into the array at any point
		void insert(std::string new_string, unsigned int index);
		/// Resets the array back to it's original state
		void clear();
		/// Returns and item in the array at a specified index
		std::string get(unsigned int index);
		/// Cycles through the array and finds a given value, starts at index 0 if not specified 
		int find(std::string search_value, int start_index = 0);
		/// Removes an item in the array at a given index 
		void remove(unsigned int index);
		/// Removes all instances of a specified value
		int remove_all(std::string search_value);
		
	};
}