#pragma once
#include <string>
#include <utility>
#include <stdexcept>

namespace ssuds
{
	/// An ArrayList is an array-based data structure. 
	template<class T>
	class ArrayList
	{
	protected:
		/// The current size of mData (in elements, not bytes)
		int mSize;
		/// The current amount that the array can hold
		int mCapacity;
		/// The array of data we're currently holding
		T * mData;
		/// Storing the starting capacity for the clear method
		static const int start_capacity = 5;

	public:
		/// Default constructor

		ArrayList(const ArrayList& other) : mData(nullptr), mSize(other.mSize), mCapacity(other.mCapacity)
		{
			mData = new T[mCapacity];
			for (int i = 0; i < other.mSize; i++)
				mData[i] = other.mData[i];
		}

		ArrayList() : mData(nullptr), mSize(0), mCapacity(start_capacity)
		{
			mData = new T[start_capacity];
		}

		

		/// Destructor
		~ArrayList()
		{
			delete[] mData;
		}

		/// <summary>
		///  Inserts a new element at the end of the array
		/// </summary>
		/// <param name="val">the new value to add</param>
		void append(const T& new_val)
		{
			if (mSize == mCapacity)
			{
				grow();
			}
			// Note: we get a bunch of these "free" appends for one costly grow
			mData[mSize] = new_val;
			mSize++;
		}

		/// <summary>
		/// Clears the array back to its original state
		/// </summary>
		void clear()
		{
			delete[] mData;
			mCapacity = start_capacity;
			mSize = 0;
			mData = new T[mCapacity];
		}

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(T val, int start_index = 0) const
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

		/// <summary>
		/// Gets the data item at the given index.  This will throw an std::out_of_bounds exception if index is invalid (less than 0 or >= size)
		/// </summary>
		/// <param name="index">the index of the thing to return</param>
		/// <returns>the value at the given index</returns>
		friend std::ostream& operator<<(std::ostream& os, const ArrayList& a)
		{
			for (int i = 0; i < a.mSize; i++)
			{
				if (i == a.mSize - 1 && i == 0)
					os << "[" << a[i] << "]";
				else if (i == a.mSize - 1 )
					os << a[i] << "]";
				else if (i == 0)
					os << "[" << a[i] << ", ";
				else
					os << a[i] << ", ";
			}
			return os;
		}

		T& operator[](unsigned int index) const
		{
			if (index >= mSize)
				throw std::out_of_range("Invalid index: " + std::to_string(index));
			else
				return mData[index];
		}

		ArrayList& operator=(const ArrayList& other)
		{

			// Throw out OUR mData
			delete[] mData;

			// Allocate a NEW array (of size big enough all their data)
			mData = new T[other.mCapacity];

			// Copy over all elements from other to our new array.
			for (int i = 0; i < other.mSize; i++)
			{
				mData[i] = other[i];
			}
			// Copy their size to us
			mSize = other.mSize;
			mCapacity = other.mCapacity;
			// Last step: return us to support "chain assignment"
			// a = b = c;
			return *this;
		}

		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(const T& val,const int index)
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

		/// <summary>
		/// Removes a data item at the given index
		/// </summary>
		/// <param name="index">the index of the thing to remove (will return a std::out_of_bounds exception if invalid (<0 or >= size)</param>
		/// <returns>the data item that was just removed</returns>
		T remove(const int index)
		{
			if (index >= mSize || index < 0)
				throw std::out_of_range("Invalid index: " + std::to_string(index));

			// Get the value we'll return at the end (the element removed)
			T result = mData[index];

			// Move all elements that come after index down one spot
			for (int i = index; i < mSize - 1; i++)
				mData[i] = mData[i + 1];

			// Re-allocate the array (the reverse of a grow operation)
			

			// Decrement our size
			mSize--;
			mCapacity >>= 1;

			if (mCapacity >> 1 < mSize && mCapacity > start_capacity)
			{
				T* new_array = new T[mCapacity];
				for (int i = 0; i < mSize; i++)
					new_array[i] = mData[i];
				delete[] mData;
				mData = new_array;
			}

			// Return the result
			return result;
		}

		/// <summary>
		/// Removes all occurrences of a given value.  Uses find and remove internally to do the removal
		/// </summary>
		/// <param name="val">the value to remove</param>
		/// <returns>the number of occurrences of that data item that were removed</returns>
		int remove_all(const T& val)
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

		/// <summary>
		/// Returns the size of the internal array (i.e.) how many things are being stored in the ArrayList
		/// </summary>
		/// <returns>the size of the ArrayList</returns>
		int size() const
		{
			return mSize;
		}

		/// <summary>
		/// Returns the total space of the current array
		/// </summary>
		int capactiy_size() const
		{
			return mCapacity;
		}
	protected:
		/// <summary>
		/// An internal method to increase the size of the internal array by 1.
		/// </summary>
		void grow()
		{
			mCapacity <<= 1;
			T* bigger_array = new T[mCapacity];
			for (int i = 0; i < mSize; i++)
				bigger_array[i] = mData[i];
			delete[] mData;
			mData = bigger_array;
		}
	};
}
