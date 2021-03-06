#include <iostream>
#include <array_list.h>
#include <fstream>
#include <stdexcept>


ssuds::ArrayList::ArrayList()
{
	mSize = 0;
	mData = nullptr;
}

ssuds::ArrayList::~ArrayList()
{
	if (mData != nullptr)
	{
		delete[] mData;
		mData = nullptr;
	}
}

void ssuds::ArrayList::append(std::string new_string)
{
	if (mData == nullptr)
	{
		mData = new std::string[1];			// an array with 1 element
		mData[0] = new_string;
	}
	else
	{
		std::string* bigger_array = new std::string[mSize + 1];
		for (int i = 0; i < mSize; i++)
			bigger_array[i] = mData[i];
		delete[] mData;
		mData = bigger_array;
		mData[mSize] = new_string;
	}

	mSize++;
}

unsigned int ssuds::ArrayList::size()
{
	return mSize;
}

//throw std::out_ofrange

void ssuds::ArrayList::insert(std::string new_string, unsigned int index)
{
	if (0 <= index && index < mSize)
	{
		if (mData == nullptr)
			ssuds::ArrayList::append(new_string);
		else
		{
			std::string* temp_array = new std::string[mSize + 1];
			for (int i = 0; i <= mSize; i++)
			{
				if (i == index)
				{
					temp_array[i] = new_string;
					temp_array[i + 1] = mData[i];
				}

				else if (i < index)
					temp_array[i] = mData[i];
				else if (i > index)
					temp_array[i] = mData[i - 1];
			}
			delete[] mData;
			mData = temp_array;
			mSize++;
		}
	}
	else
		throw std::out_of_range("index out of range");
}

void ssuds::ArrayList::clear()
{
	delete[] mData;
	mData = nullptr;
	mSize = 0;
}

std::string ssuds::ArrayList::get(unsigned int index)
{
	if (index >= mSize)
		throw std::out_of_range("index out of range");
	else
		return mData[index];
}

int ssuds::ArrayList::find(std::string search_value, int start_index)
{
	for (int i = start_index; i >= 0 && i <= mSize; i++)
	{
		if (mData[i] == search_value)
			return i;
	}
	return -1;
}
void ssuds::ArrayList::remove(unsigned int index)
{
	if (0 <= index && index <= mSize)
	{
		std::string* temp_array = new std::string[mSize];
		for (int i = 0; i < mSize; i++)
		{
			if(i < index)
				temp_array[i] = mData[i];
			if(i > index)
				temp_array[i-1] = mData[i];
		}
		delete[] mData;
		mData = temp_array;
		mSize--;
	}
	else
	{
		throw std::out_of_range("Index out of range");
	}
}

int ssuds::ArrayList::remove_all(std::string search_value)
{
	int i = 0;
	while (1)
	{
		if (mSize >= find(search_value))
		{
			remove(find(search_value));
			i++;
		}
		else
			return i;
	}
}