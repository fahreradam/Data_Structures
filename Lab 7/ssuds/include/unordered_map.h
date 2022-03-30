#pragma once

template <class K, class V>
class UnorderedMap
{
protected:
	// Definitely have these attributes
	int mSize;			// number of key-value pairs
	int mCapacity;		// number of available spots in our table

	// Decision#1: how do we store A single pair?
	// 1. std::pair<K, V>
	// 2. hidden node class
	//    class node
	//    {
	//    public:
	//        K mKey;
	//        V mValue;
	//        node(const K& kval) : mKey(kval) {}
	//    };


	// Decision#2: how do we store a TABLE of pairs? We need a way to mark a spot as "empty"
	// 1. parallel arrays: an array of keys, an array of values, an array of bools (used or not?)
	//     V* mValueTable;
	//     K* mKeyTable;
	//     bool* mUsedTable;
	// 2. make an array of pair or node POINTERS (nullptr if not used)
	//     Node** mTable;    // an array of node pointers
	mTable = new Node * [table_size];		// now it's an array of node pointers!
									   //   in the constructor
//    std::pair<K, V>** mTable;	
//           mTable = new std::pair<K, V>*[table_size];
// 3. Use an ArrayList / vector instead of an array....but be careful with the grow.

// If I had allowed you to do this, it would've been much easier
//void add(K the_key, V the_value)
//{
//
//}

// This is the way to get a value, modify a value, and add a new key-value pair
	V& operator[](const K& the_key)
	{
		// Run the_key through our hash generator to get a hash code
		// Modulo that hash_code with mCapacity to get the desired spot
		// "Circular Probe" from that starting point to either:
		//    Case1: We get to a key-value pair that matches the given key.  The user is
		//        probably trying to get / modify a value
		//    Case2: We get to an empty spot.  The user is probably trying to add a new item
		if (case == 1)
		{
			// 
			return mTable[cur_spot]->mValue;
		}
		else
		{
			// we need to make a key value pair, but...they are only giving us the key!
			// We just make a pair with the value UNINITIALIZED.  The user will hopefully
			// change it to the value of their choice
			mTable[cur_spot] = new Node(the_key);		// not setting the value!
			return mTable[cur_spot]->mValue;
		}
	}


};