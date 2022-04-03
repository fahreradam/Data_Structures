#pragma once

#include <utility>		// contains the def'n for std::pair
#include <cstring>
#include <array_list.h>

#define INITIAL_CAPACITY 10

namespace ssuds
{
	/// Used for foward and backward iteration
	enum class UnorderedMapIteratorType {forward, backwards};

	/// Templated type for the first value K and the second value V in an std::pair 
	template <class K, class V>

	/// UnorderedMap Class 
	class UnorderedMap
	{
	public:
		/// UnorderedMapIterator
		class UnorderedMapIterator
		{
		/// UnorderedMapIterator Protected Attributes
		protected:
			const UnorderedMap& mUnorderedMap;
			int mPosition;
			UnorderedMapIteratorType mType;

		/// Public Class Methods
		public:
			/// Iterator constructor 
			UnorderedMapIterator(const UnorderedMap& uom, UnorderedMapIteratorType tp, int pos) : mUnorderedMap(uom), mPosition(pos), mType(tp)
			{

			}

			/// Checks if two iterators are the same 
			bool operator==(const UnorderedMapIterator& other) const
			{
				return &mUnorderedMap == &other.mUnorderedMap && mPosition == other.mPosition;
			}

			/// Checks if two iterators are not the same 
			bool operator !=(const UnorderedMapIterator& other) const
			{
				return !(*this == other);
			}

			/// Used for incrementing through the iterator
			void operator++()
			{
				if (mType == UnorderedMapIteratorType::forward)
				{
					mPosition++;
					while (mUnorderedMap.mTable[mPosition] == nullptr && mPosition < mUnorderedMap.mCapacity)
						mPosition++;
					if (mUnorderedMap.mCapacity < mPosition)
						mPosition = mUnorderedMap.mCapacity;
				}
				else
				{
					mPosition--;
					while (mUnorderedMap.mTable[mPosition] == nullptr && mPosition > 0)
						mPosition--;
					if (0 > mPosition)
						mPosition = -1;
				}
			}

			/// Allows incremetation on either side of the iterator 
			void operator++(int dummy)
			{
				if (mType == UnorderedMapIteratorType::forward)
				{
					mPosition++;
					while (mUnorderedMap.mTable[mPosition] == nullptr && mPosition < mUnorderedMap.mCapacity)
						mPosition++;
					if (mUnorderedMap.mCapacity < mPosition)
						mPosition = mUnorderedMap.mCapacity;
				}
				else
				{
					mPosition--;
					while (mUnorderedMap.mTable[mPosition] == nullptr && mPosition > 0)
						mPosition--;
					if (0 > mPosition)
						mPosition = -1;
				}
			}

			/// Used to return a std::pair thats at the current position of the iterator  
			std::pair<K, V>* operator*()
			{
				return mUnorderedMap.mTable[mPosition];
			}
		};
	/// Protected Attributes for the UnorderedMap Class 
	protected:
		std::pair<K, V>** mTable;
		int mSize;
		int mCapacity;
		std::hash<K> hasher;

	/// Public Methods for the UnorderedMap Class 
	public:
		/// UnorderedMap Constructor
		UnorderedMap()
		{
			mTable = new std::pair<K, V>*[INITIAL_CAPACITY];
			mSize = 0;
			mCapacity = INITIAL_CAPACITY;
			memset(mTable, 0, sizeof(std::pair<K, V>*) * INITIAL_CAPACITY);
		}

		/// UnorederedMap Deconstructor
		~UnorderedMap()
		{
			for (int i = 0; i < mCapacity; i++)
			{
				delete mTable[i];
			}
			delete[] mTable; 
		}

		/// Returns a UnorderedMapIterator at the beginning of the Map 
		UnorderedMapIterator begin()
		{
			return UnorderedMapIterator(*this,UnorderedMapIteratorType::forward, 0);
		}

		/// Returns a UnorderedMapIterator one index past end of the Map 
		UnorderedMapIterator end()
		{
			return UnorderedMapIterator(*this, UnorderedMapIteratorType::forward, mCapacity);
		}

		/// Returns a UnorderedMapIterator at the end of the map for backwards iteration
		UnorderedMapIterator rbegin()
		{
			return UnorderedMapIterator(*this, UnorderedMapIteratorType::backwards, mCapacity - 1);
		}

		/// Returns a UnorderedMapIterator one before the begining of the map
		UnorderedMapIterator rend()
		{
			return UnorderedMapIterator(*this, UnorderedMapIteratorType::backwards, -1);
		}

		/// Used to create more std::pair or to change what the second value or the std::pair is
		V& operator[](const K& the_key)
		{
			// Run the_key through our hash generator to get a hash code
			if (float(mSize) / mCapacity >= 0.70)
				grow();
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


		/// Returns the current size of the Map 
		int size() const
		{
			return mSize;
		}

		/// returns the current capacity of the Map 
		int capacity() const
		{
			return mCapacity;
		}

		/// Removes an std::pair of the given key and resort a portion of the map to be put in the most "favored" spots 
		bool remove(const K& the_key)
		{
			size_t key = hasher(the_key);
			key = key % mCapacity;

			while (mTable[key] != nullptr && mTable[key]->first != the_key)
			{
				key++;
			}
			if (mTable[key]->first != the_key)
				return false;
			else
			{
				ssuds::ArrayList<std::pair<K, V>> alist;

				while (key >= 0 && mTable[key])
				{
					alist.append(*mTable[key]);
					delete mTable[key];
					mTable[key] = nullptr;
					key--;
				}
				key = (hasher(the_key) % mCapacity) + 1 ;
				
				while (key < mCapacity && mTable[key])
				{
	
					alist.append(*mTable[key]);
					delete mTable[key];
					mTable[key] = nullptr;
					key++;
				}

				for (int i = 0; i < alist.size(); i++)
				{
					if (alist[i].first != the_key)
					{
						(*this)[alist[i].first] = alist[i].second;
						mSize--;
					}
				}
			}
			delete mTable[key];
			mSize--;
			return true;
		}

		/// Returns an UnorderedMapIterator that is either at the position of the requested key or at the end of the map 
		UnorderedMapIterator find(const K the_key)
		{
			size_t key = hasher(the_key);
			key = key % mCapacity;
			while (key < mCapacity && mTable[key]->first != the_key)
			{
				key++;
			}

			if (key >= mCapacity)
				return end();
			else
				return UnorderedMapIterator(*this, UnorderedMapIteratorType::forward, key);
		}

		/// clears everything in the Map
		void clear()
		{

			for (int i = 0; i < mCapacity; i++)
			{
				delete mTable[i];
			}
			delete[] mTable;

			mTable = new std::pair<K, V>*[mCapacity];
			mSize = 0;
			memset(mTable, 0, sizeof(std::pair<K, V>*) * mCapacity);
		}

		/// Allows the use of operations like std::cout  
		friend std::ostream& operator << (std::ostream& os, const UnorderedMap<K,V>& umap)
		{
			os << "{";
			int j = 0;
			for (int i = 0; i < umap.capacity()-1; i++)
			{
				if (umap.mTable[i])
				{
					os << umap.mTable[i]->first << ":" << umap.mTable[i]->second;		
					if (j < umap.size()-1 && i < umap.capacity() - 1)
					{
						os << ", ";
						j++;
					}

				}
			}
			os << "}";
			return os;
		}

	/// Protected grow method thats used to grow the map if the size is bigger than 70% of the totable map
	/// should only be called within the class and not by the user
	protected:
		void grow()
		{
			std::pair<K, V>** temp = new std::pair<K,V>*[mCapacity];
			temp = mTable;
			int temp_size = mSize;

			mCapacity *= 2;
			mTable = new std::pair<K, V>*[mCapacity];

			memset(mTable, 0, sizeof(std::pair<K, V>*) * mCapacity);
			mSize = 0;
			for (int i = 0; i < temp_size; i++)
			{
				if (temp[i])
				{
					(*this)[temp[i]->first] = temp[i]->second;
				}
			}
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