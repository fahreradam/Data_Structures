#pragma once
#include <array_list.h>
#include <random>

namespace ssuds
{
	enum class SortOrder { ASCENDING, DESCENDING };

	// Reference: https://www.geeksforgeeks.org/quick-sort/
	template <class T>
	int _quicksort_partition(ArrayList<T>& alist, SortOrder type, int low, int high, long& num_operations)
	{
		int mid = (low + high) / 2;
		T& pivot_val = alist[high];
		int i = low - 1;
		for (int j = low; j <= high; j++)
		{
			if (_out_of_order(alist, type, pivot_val, alist[j]))
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

	// Reference: https://www.geeksforgeeks.org/quick-sort/
	template <class T>
	void _quicksort_internal(ArrayList<T>& alist, SortOrder type, int low, int high, long& op_count)
	{
		if (low < high)
		{
			int part_index = _quicksort_partition(alist, type, low, high, op_count);
			_quicksort_internal(alist, type, low, part_index - 1, op_count);
			_quicksort_internal(alist, type, part_index + 1, high, op_count);
		}
	}

	

	template <class T>
	bool _out_of_order(const ArrayList<T>& alist, SortOrder sort_type, int index1, int index2)
	{
		return ((sort_type == SortOrder::ASCENDING && alist[index1] > alist[index2]) ||
			    (sort_type == SortOrder::DESCENDING && alist[index1] < alist[index2]));
	}


	template <class T>
	bool _out_of_order(const ArrayList<T>& alist, SortOrder sort_type, const T& val1, const T& val2)
	{
		return ((sort_type == SortOrder::ASCENDING && val1 > val2) || (sort_type == SortOrder::DESCENDING && val1 < val2));
	}

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
			else if (_out_of_order(alist, sort_order, search_value, alist[mid]))
				left = mid + 1;
			else
				right = mid - 1;
		} 
		if (num_ops != nullptr)
			*num_ops = comparisons;
		return -1;
	}

	// Reference: https://www.geeksforgeeks.org/quick-sort/
	template <class T>
	long quicksort(ArrayList<T>& alist, SortOrder type)
	{
		long op_count = 0;
		_quicksort_internal(alist, type, 0, alist.size() - 1, op_count);
		return op_count;
	}


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


	// Reference: https://www.cplusplus.com/reference/random/
	// Reference: https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
	template <class T>
	void shuffle(ArrayList<T>& alist)
	{
		
		std::default_random_engine generator;
		for (int i = alist.size() - 1; i > 0; i--)
		{
			std::uniform_int_distribution<int> distribution(0, i);
			int j = distribution(generator);  // generates number in the range 0...i
			
			std::swap(alist[i], alist[j]);
		}
	}
	
}
