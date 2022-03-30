#pragma once

#include <utility>		// contains the def'n for std::pair
#include <cstring>
#include <array_list.h>

#define INITIAL_CAPACITY 10

namespace ssuds
{
	template <class K, class V>
	class UnorderedMap
	{
		// What does a single key-value pair look like?
		// 1. std::pair<K, V>
		// 2. custom (hidden) Node class that contains a K and V attribute

		// What does your table look like?
		// 3. An array of ??? OBJECTS   (??? = std::pair or a Node)
	protected:
		std::pair<K, V>** mTable;
		int mSize;
		int mCapacity;
		std::hash<K> hasher;
	public:
		// and then in the constructor
		UnorderedMap()
		{
			mTable = new std::pair<K, V>*[INITIAL_CAPACITY];
			mSize = 0;
			mCapacity = INITIAL_CAPACITY;
			memset(mTable, 0, sizeof(std::pair<K, V>*) * INITIAL_CAPACITY);
		}
		// and then when we add

		// in the destructor
		~UnorderedMap()
		{
			for (int i = 0; i > mCapacity; i++)
			{
				delete mTable[i];
			}
			delete[] mTable;
		}

		V& operator[](const K& the_key)
		{
			// Run the_key through our hash generator to get a hash code
			size_t key = hasher(the_key);
			key = key % mCapacity;
			// Modulo that hash_code with mCapacity to get the desired spot
			// "Circular Probe" from that starting point to either:
			//    Case1: We get to a key-value pair that matches the given key.  The user is
			//        probably trying to get / modify a value
			//    Case2: We get to an empty spot.  The user is probably trying to add a new item
			while (mTable[key] != nullptr && mTable[key]->first != the_key)
			{
				key++;
			}

			if (mTable[key] == nullptr)
			{
				// we need to make a key value pair, but...they are only giving us the key!
				// We just make a pair with the value UNINITIALIZED.  The user will hopefully
				// change it to the value of their choice
				mTable[key] = new std::pair<K, V>;		// not setting the value!
				mTable[key]->first = the_key;
				mSize++;
				return mTable[key]->second;
			}
			else			
			{
				return mTable[key]->second;
			}
		}

		int size() const
		{
			return mSize;
		}

		int capacity() const
		{
			return mCapacity;
		}

		bool remove(const K& the_key)
		{
			size_t key = hasher(the_key);
			key = key % mCapacity;

			while (mTable[key] != nullptr && mTable[key]->first != the_key)
			{
				key++;
			}
			if (mTable[key]->first != the_key)
				return false

			delete mTable[key];
			return true;
		}

		friend std::ostream& operator << (std::ostream& os, const UnorderedMap<K,V>& umap)
		{
			os << "{";
			for (int i = 0; i < umap.capacity(); i++)
			{
				if (umap.mTable[i])
				{
					os << umap.mTable[i]->first << ":" << umap.mTable[i]->second;
					if (umap.mTable[i+1] && i < umap.capacity()-1)
						os << ", ";

				}
			}
			os << "}";
			return os;
		}

	};



	//// 4. An array of ??? POINTERS  
	//? ? ? **mTable;
	//// and then in the constructor
	//mTable = new ? ? ? *[initial_capacity];
	//for (int i = 0; i < initial_capacity; i++)
	//	mTable[i] = nullptr;
	//// and then when we add
	//mTable[spot] = new ? ? ? (...);
	//// in the destructor
	//delete[] mTable;
	//// 5. use vector/ArrayList
	//ssuds::ArrayList<std::pair<K, V>*> mTable;

}