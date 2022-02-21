#pragma once
#include <array_list.h>
#include <iostream>
#include <random>

namespace ssuds
{
	enum class SortType { ASCENDING, DESCENDING };
	template <class T>
	void bubble_sort(const ssuds::ArrayList<T>& list, const SortType tp, int* num_ops = nullptr)
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
				}
			}
		}
	}
	template <class T>
	bool out_of_order(const SortType type, const T& val1, const T& val2)
	{
		if (type == SortType::ASCENDING)
			return val1 > val2;
		else
			return val1 < val2;
	}
	template<class T>
	int binary_search(const ssuds::ArrayList<T>& list, const T& search_val, int * num_ops=nullptr)
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
		}
		return -1;
	}
	template<class T>
	void shuffle(const ssuds::ArrayList<T>& list)
	{
		std::default_random_engine generator;
		int n = list.size();
		for (unsigned int i = 0; i < n; i++)
		{
			std::uniform_int_distribution<int> distribution(0, i); // found from https://www.cplusplus.com/reference/random/
			int j = distribution(generator);
			swap_list(list, i, j);
		}
	}
	//template<class T>
	//void random_list(ssuds::ArrayList<T>& list, unsigned int num_size)
	//{
	//	 
	//}

	template<class T>
	void qsort(const ssuds::ArrayList<T>& list)
	{
		qsort_recursive(list, 0, list.size() - 1);
	}
	template<class T>
	ssuds::ArrayList<T> qsort_recursive(const ssuds::ArrayList<T>& list, const int left, const int right)
	{
		if (left >= right)
		{
			return list;
		}
		int pivot_index = pivot(list, left, right);
		qsort_recursive(list, left, pivot_index - 1);
		qsort_recursive(list, pivot_index + 1, right);
	}
	template<class T>
	int pivot(const ssuds::ArrayList<T>& list, const int left, const int right)
	{
		T pivot_val = list[right];
		int processed_index = left - 1;
		int cur_index = left;
		while (cur_index < right)
		{
			processed_index++;
			swap_list(list, cur_index, processed_index);
			cur_index++;
		}
		processed_index++;
		swap_list(list, processed_index, right);
		return processed_index;

	}

	template<class T>
	void swap_list(const ssuds::ArrayList<T>& list, const int val1, const int val2)
	{
		T temp = list[val1];
		list[val1] = list[val2];
		list[val2] = temp;
	}

	template<class T>
	void random_list()
}