#pragma once
#include <iostream>

namespace ssuds
{

	class ArrayList
	{
	protected:
		std::string* mData;
		unsigned int mSize;

	public:
		ArrayList();
		void append(std::string new_string);
		unsigned int size();
		void insert(std::string new_string, unsigned int index);
		void clear();
		std::string get(unsigned int index);
		int find(std::string search_value, int start_index = 0);
		void remove(unsigned int index);
		void remove_all(std::string search_value)

	};
}