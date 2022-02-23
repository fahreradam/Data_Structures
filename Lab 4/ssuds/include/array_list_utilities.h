#pragma once
#include <array_list.h>
#include <iostream>
#include <random>

namespace ssuds
{
	enum class SortType { ASCENDING, DESCENDING };
	template <class T>
	/// Uses the bubble sort method to sort the array 
	void bubble_sort(const ssuds::ArrayList<T>& list, const SortType tp, long* num_ops = nullptr)
	{

		int n = list.size();
		for (int i = 0; i < n; i++)
		{
			bool is_sorted = true;
			for (int j = 0; j < (n - i-1); j++)
			{
				if (out_of_order(tp, list[j], list[j + 1])) 
				{
					swap_list(list, j, j+1);
					is_sorted = false;
					num_ops++;
				}
			}
		}
	}
	/// checks to see if an item is less than or greater than another given item 
	template <class T>
	bool out_of_order(const SortType type, const T& val1, const T& val2)
	{
		if (type == SortType::ASCENDING)
			return val1 > val2;
		else
			return val1 < val2;
	}

	/// Searchs for a designated value throughout the arraylist 
	template<class T>
	int binary_search(const ssuds::ArrayList<T>& list, const T& search_val, long * num_ops=nullptr)
	{
		int left = 0;
		int right = list.size() - 1;
		while (left <= right)
		{
			int mid = (left + right) / 2;
			if (list[mid] == search_val)
				return mid;
			else if (list[mid] > search_val)
				right = mid - 1;
			else
				left = mid + 1;
			num_ops++;
		}
		return -1;
	}

	/// Shuffles the arraylist 
	template<class T>
	void shuffle(const ssuds::ArrayList<T>& list)
	{
		std::default_random_engine generator;
		int n = list.size();
		for (unsigned int i = n-1; i > 0; i--)
		{
			std::uniform_int_distribution<int> distribution(0, i); // found from https://www.cplusplus.com/reference/random/
			int j = distribution(generator);
			swap_list(list, i, j);
		}
	}

	/// Recives an arraylist clears any left over items and fills it with random items 
	template<class T>
	void random_list(ssuds::ArrayList<T>& list, const int num_size)
	{
		list.clear();
		std::default_random_engine generator;
		for (int i = 0; i < num_size; i++)
		{
			std::uniform_real_distribution<float> distribution(0, 1000);
			float j = distribution(generator);
			list.append(j);
		}
	}

	/// Creating the Quick Sort Method
	template<class T>
	int* qsort(const ssuds::ArrayList<T>& list, ssuds::SortType tp)
	{
		int* num_swap = 0;
		qsort_recursive(list, tp, 0, list.size() - 1, num_swap);
		return num_swap;
	}
	template<class T>
	void qsort_recursive(const ssuds::ArrayList<T>& list, ssuds::SortType tp, const int left, const int right, int* num_swap = NULL)
	{
		if (left >= right)
		{
			return;
		}
		int pivot_index = pivot(list,tp, left, right);
		qsort_recursive(list,tp, left, pivot_index - 1);
		qsort_recursive(list,tp, pivot_index + 1, right);
	}
	template<class T>
	int pivot(const ssuds::ArrayList<T>& list, ssuds::SortType tp, const int left, const int right, int *num_swap = NULL)
	{
		T pivot_val = list[right];
		int processed_index = left - 1;
		int cur_index = left;
		if (tp == ssuds::SortType::ASCENDING)
		{
			while (cur_index < right)
			{
				if (list[cur_index] <= pivot_val)
				{
					processed_index++;
					swap_list(list, cur_index, processed_index);
					num_swap++;
				}
				cur_index++;
			}
		}
		else
		{
			while (cur_index <= right)
			{
				if (list[cur_index] > pivot_val)
				{
					processed_index++;
					swap_list(list, cur_index, processed_index);
				}
				cur_index++;
			}
		}
		processed_index++;
		swap_list(list, processed_index, right);
		return processed_index;
	}
	/// A simply method that swaps two values in the same array_list 
	template<class T>
	void swap_list(const ssuds::ArrayList<T>& list, const int val1, const int val2)
	{
		T temp = list[val1];
		list[val1] = list[val2];
		list[val2] = temp;
	}
}