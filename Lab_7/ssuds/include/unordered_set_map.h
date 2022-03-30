#pragma once
#include <utility>		// contains the def'n for std::pair

template <class K, class V>
class UnorderedMap
{
	// What does a single key-value pair look like?
	// 1. std::pair<K, V>
	// 2. custom (hidden) Node class that contains a K and V attribute

protected:
	// What does your table look like?
	// 3. An array of ??? OBJECTS   (??? = std::pair or a Node)
	std::pair<K, V>* mTable;
	bool* mUsedSpots;
public:
	UnorderedMap()
	// and then in the constructor
	mTable = new ? ? ? [initial_capacity];
	mUsedSpots = new bool[initial_capacity];
	for (int i = 0; i < initial_capacity; i++)
		mUsedSpots[i] = false;
	// and then when we add

	// in the destructor
	delete[] mTable;
	delete[] mUsedTable;

	// 4. An array of ??? POINTERS  
	? ? ? **mTable;
	// and then in the constructor
	mTable = new ? ? ? *[initial_capacity];
	for (int i = 0; i < initial_capacity; i++)
		mTable[i] = nullptr;
	// and then when we add
	mTable[spot] = new ? ? ? (...);
	// in the destructor
	delete[] mTable;
	// 5. use vector/ArrayList
	ssuds::ArrayList<std::pair<K, V>*> mTable;

};