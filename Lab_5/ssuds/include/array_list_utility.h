#pragma once
#include <array_list.h>
#include <ssuds.h>
#include <random>

namespace ssuds
{
	/// <summary>
	/// An internal method used to support the quicksort function.  It probably has limited
	/// use to an external user, but we can't really hide it since templated functions need
	/// to be available in all translation units (cpp files)
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="alist">The ArrayList we're sorting</param>
	/// <param name="type">The type of sort we're trying to implement</param>
	/// <param name="low">The left-most index of the portion of alist we're modifying</param>
	/// <param name="high">The right-most index of the portion of alist we're modifying</param>
	/// <param name="num_operations">used to track the total number of operations performed by quicksort</param>
	/// <returns>the pivot index (for use by quicksort)</returns>
	template <class T>
	int _quicksort_partition(ArrayList<T>& alist, SortOrder type, int low, int high, long& num_operations)
	{
		// Reference: https://www.geeksforgeeks.org/quick-sort/
		T& pivot_val = alist[high];
		int i = low - 1;
		for (int j = low; j <= high; j++)
		{
			if (_out_of_order(type, pivot_val, alist[j]))
			{
				i++;
				// Takes advantage of the move semantics, which would be faster than making a temp T value
				std::swap(alist[j], alist[i]);
				num_operations++;
			}
		}
		std::swap(alist[i + 1], alist[high]);
		return i + 1;
	}

	
	/// <summary>
	/// Another internal support method used by quicksort.  This method subdivides the portion of the list
	/// it is tasked with sorting.  The real work is done by pivot -- this method just recurses
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="alist">The ArrayList we're sorting</param>
	/// <param name="type">The type of sort we're trying to implement</param>
	/// <param name="low">The left-most index of the portion of alist we're modifying</param>
	/// <param name="high">The right-most index of the portion of alist we're modifying</param>
	/// <param name="op_count">used to track the total number of operations performed by quicksort</param>
	template <class T>
	void _quicksort_internal(ArrayList<T>& alist, SortOrder type, int low, int high, long& op_count)
	{
		// Reference: https://www.geeksforgeeks.org/quick-sort/
		if (low < high)
		{
			int part_index = _quicksort_partition(alist, type, low, high, op_count);
			_quicksort_internal(alist, type, low, part_index - 1, op_count);
			_quicksort_internal(alist, type, part_index + 1, high, op_count);
		}
	}

	
	/// <summary>
	/// A useful method that is used to determine if element index1 ? index2 where index1
	/// is < for ASCENDING sorts and > for DESCENGING sorts.  By using this method (rather than
	/// actual < or >, we don't have to write special code in the various methods that work with / on
	/// sorted ArrayLists.
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="alist">The ArrayList we're sorting</param>
	/// <param name="sort_type">The type of sort we're trying to implement</param>
	/// <param name="index1">Index of the first item in the comparison</param>
	/// <param name="index2">Index of the second item in the comparison</param>
	/// <returns></returns>
	template <class T>
	bool _out_of_order(const ArrayList<T>& alist, SortOrder sort_type, int index1, int index2)
	{
		return ((sort_type == SortOrder::ASCENDING && alist[index1] > alist[index2]) ||
			    (sort_type == SortOrder::DESCENDING && alist[index1] < alist[index2]));
	}

	/// <summary>
	/// This method is very similar to the other _out_of_order implementation, but rather than 
	/// using the ArrayList and indices, a reference to two values (one / both of which might really
	/// exist within an ArrayList)
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="sort_type">The type of sort we're trying to implement</param>
	/// <param name="val1">The first value in the comparison</param>
	/// <param name="val2">The second value in the comparison</param>
	/// <returns></returns>
	template <class T>
	bool _out_of_order(SortOrder sort_type, const T& val1, const T& val2)
	{
		return ((sort_type == SortOrder::ASCENDING && val1 > val2) || (sort_type == SortOrder::DESCENDING && val1 < val2));
	}


	/// <summary>
	/// If we have a sorted ArrayList, we can find a particular value much more quickly using
	/// this binary search function (as opposed to a linear search, which is what the ArrayList::find
	/// method implements)
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="alist">The sorted ArrayList to search within</param>
	/// <param name="sort_order">The way alist is sorted</param>
	/// <param name="search_value">The value to search for</param>
	/// <param name="num_ops">If not nullptr, the number of comparisons performed is written here</param>
	/// <returns>The index of an occurrence of search_value (or -1 if none are present in alist)</returns>
	template <class T>
	int find_binary_search(const ArrayList<T>& alist, SortOrder sort_order, const T& search_value, long* num_ops = nullptr)
	{
		long comparisons = 0;
		int left = 0;
		int right = alist.size() - 1;
		while (left <= right)
		{
			int mid = (left + right) >> 1;			// divide by 2 (the average)
			comparisons++;
			if (alist[mid] == search_value)
			{
				if (num_ops != nullptr)
					*num_ops = comparisons;
				return mid;
			}
			else if (_out_of_order(sort_order, search_value, alist[mid]))
				left = mid + 1;
			else
				right = mid - 1;
		} 
		if (num_ops != nullptr)
			*num_ops = comparisons;
		return -1;
	}

	
	/// <summary>
	/// Performs an in-place quicksort operation, O(n log n), on alist
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="alist">the ArrayList we wish to sort</param>
	/// <param name="type">The type of sort to perform</param>
	/// <returns>The number of swaps performed while sorting</returns>
	template <class T>
	long quicksort(ArrayList<T>& alist, SortOrder type)
	{
		// Reference: https://www.geeksforgeeks.org/quick-sort/
		long op_count = 0;
		_quicksort_internal(alist, type, 0, alist.size() - 1, op_count);
		return op_count;
	}


	/// <summary>
	/// Performs an in-place bubble-sort sort on the given ArrayList, O(n^2)
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="alist">the ArrayList we wish to sort</param>
	/// <param name="type">The type of sort to perform</param>
	/// <returns>The number of swaps performed during bubble-sort</returns>
	template <class T>
	long bubblesort(ArrayList<T>& alist, SortOrder type)
	{
		long swaps = 0;
		for (int z = 0; z < alist.size(); z++)
		{
			bool sorted = true;
			for (int i = 0; i < alist.size() - 1 - z; i++)
			{
				if (_out_of_order(alist, type, i, i + 1))
				{
					sorted = false;
					std::swap(alist[i], alist[i + 1]);
					swaps++;
				}
			}
			if (sorted)
				break;
		}
		return swaps;
	}


	/// <summary>
	/// Applies an in-place Fisher-Yates shuffle on the given ArrayList, using the <random> module
	/// </summary>
	/// <typeparam name="T">The type of ArrayList we're working on</typeparam>
	/// <param name="alist">the ArrayList we wish to sort</param>
	template <class T>
	void shuffle(ArrayList<T>& alist)
	{
		// Reference: https://www.cplusplus.com/reference/random/
		// Reference: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
		std::default_random_engine generator;
		for (int i = alist.size() - 1; i > 0; i--)
		{
			std::uniform_int_distribution<int> distribution(0, i);
			int j = distribution(generator);  // generates number in the range 0...i
			
			std::swap(alist[i], alist[j]);
		}
	}
}
