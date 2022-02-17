#pragma once
#include <array_list.h>
#include <iostream>
#include <random>

namespace ssuds
{
	enum class SortType { ASCENDING, DESCENDING };
	template <class T>
	void bubble_sort(ssuds::ArrayList<T>& list, ssuds::SortType tp, int* num_ops = nullptr)
	{

		int n = list.size();
		for (int i = 0; i < n; i++)
		{
			bool is_sorted = true;
			for (int j = 0; j < (n - i-1); j++)
			{
				if (out_of_order(tp, list[j], list[j + 1])) 
				{
					T temp = list[j];
					list[j] = list[j + 1];
					list[j + 1] = temp;
					is_sorted = false;
				}
			}
		}
	}
	template <class T>
	bool out_of_order(SortType type, const T& val1, const T& val2)
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
	void shuffle(ssuds::ArrayList<T>& list)
	{
		std::default_random_engine generator;
		int n = list.size();
		for (unsigned int i = 0; i < n; i++)
		{
			std::uniform_int_distribution<int> distribution(0, i); // found from https://www.cplusplus.com/reference/random/
			int j = distribution(generator);
			T temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}

}