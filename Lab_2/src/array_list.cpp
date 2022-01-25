#include <array_list.h>
#include <stdexcept>

ssuds::ArrayList::ArrayList() : mSize(0), mData(nullptr)
{
	// intentionally empty
}


ssuds::ArrayList::~ArrayList()
{
	if (mData)
		delete[] mData;
}


void ssuds::ArrayList::append(std::string val)
{
	// (for now) always increase the size of the array by one
	grow();

	// Stick our new element in the last slot and (sneakily) increase our size in the process
	mData[mSize++] = val;
}


void ssuds::ArrayList::clear()
{
	if (mData)
		delete[] mData;
	mData = nullptr;
	mSize = 0;
}


int ssuds::ArrayList::find(std::string val, int start_index)
{
	if (start_index >= mSize || start_index < 0)
		throw std::out_of_range("Invalid index: " + std::to_string(start_index));

	for (int i = start_index; i < mSize; i++)
	{
		if (mData[i] == val)
			return i;
	}

	// We didn't find it
	return -1;
}


std::string ssuds::ArrayList::get(int index)
{
	if (index >= mSize || index < 0)
		throw std::out_of_range("Invalid index: " + std::to_string(index));

	return mData[index];
}


void ssuds::ArrayList::grow()
{
	// Allocate what will become the new array
	std::string* new_array = new std::string[mSize + 1];

	// Copy over data from the old array (if any)
	for (int i = 0; i < mSize; i++)
		new_array[i] = mData[i];

	// Destroy the old array
	delete[] mData;

	// Make the new array *the* array
	mData = new_array;
}


void ssuds::ArrayList::insert(std::string val, int index)
{
	if (index > mSize)
		throw std::out_of_range("Invalid index: " + std::to_string(index));

	// (for now) always increase our array size
	grow();

	// Move all the elements that come *after* index up one spot
	for (int i = mSize; i > index; i--)
		mData[i] = mData[i - 1];

	// Put our new elements in spot index and increase our size
	mData[index] = val;
	mSize++;
}


std::string ssuds::ArrayList::remove(int index)
{
	if (index >= mSize || index < 0)
		throw std::out_of_range("Invalid index: " + std::to_string(index));

	// Get the value we'll return at the end (the element removed)
	std::string result = mData[index];

	// Move all elements that come after index down one spot
	for (int i = index; i < mSize - 1; i++)
		mData[i] = mData[i + 1];

	// Re-allocate the array (the reverse of a grow operation)
	std::string* new_array = new std::string[mSize - 1];
	for (int i = 0; i < mSize - 1; i++)
		new_array[i] = mData[i];
	delete[] mData;
	mData = new_array;
	
	// Decrement our size
	mSize--;

	// Return the result
	return result;
}


int ssuds::ArrayList::remove_all(std::string val)
{
	int cur_index = 0;
	int num_removed = 0;
	while (cur_index >= 0 && cur_index < mSize)
	{
		// Find the next occurrence of val, starting at the current position
		cur_index = find(val, cur_index);
		if (cur_index >= 0)
		{
			// We found one!
			remove(cur_index);
			num_removed++;
		}
	}

	return num_removed;
}


int ssuds::ArrayList::size()
{
	return mSize;
}


