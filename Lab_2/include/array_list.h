#pragma once
#include <string>
#include <utility>

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

	public:
		/// Default constructor
		ArrayList() : mData(nullptr), mSize(0), mCapacity(5)
		{
			mData = new T[mCapacity];
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
		void append(std::string val);

		/// <summary>
		/// Clears the array back to its original state
		/// </summary>
		void clear();

		/// <summary>
		/// Finds the index of the first occurrence of the given value
		/// </summary>
		/// <param name="val">the value to search for</param>
		/// <param name="start_index">the index to start searching at</param>
		/// <returns></returns>
		int find(std::string val, int start_index = 0);

		/// <summary>
		/// Gets the data item at the given index.  This will throw an std::out_of_bounds exception if index is invalid (less than 0 or >= size)
		/// </summary>
		/// <param name="index">the index of the thing to return</param>
		/// <returns>the value at the given index</returns>
		std::string get(int index);

		/// <summary>
		/// Inserts a new data item at a given index
		/// </summary>
		/// <param name="val">the new value to insert</param>
		/// <param name="index">the index at which to insert (must be >= 0 and <= size) </param>
		void insert(std::string val, int index);

		/// <summary>
		/// Removes a data item at the given index
		/// </summary>
		/// <param name="index">the index of the thing to remove (will return a std::out_of_bounds exception if invalid (<0 or >= size)</param>
		/// <returns>the data item that was just removed</returns>
		std::string remove(int index);

		/// <summary>
		/// Removes all occurrences of a given value.  Uses find and remove internally to do the removal
		/// </summary>
		/// <param name="val">the value to remove</param>
		/// <returns>the number of occurrences of that data item that were removed</returns>
		int remove_all(std::string val);

		/// <summary>
		/// Returns the size of the internal array (i.e.) how many things are being stored in the ArrayList
		/// </summary>
		/// <returns>the size of the ArrayList</returns>
		int size();
	protected:
		/// <summary>
		/// An internal method to increase the size of the internal array by 1.
		/// </summary>
		void grow();
	};
}
