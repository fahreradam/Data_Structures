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
		void remove(unsigned int index);
		int find(std::string search_value, int start_index = 0);


	};
}