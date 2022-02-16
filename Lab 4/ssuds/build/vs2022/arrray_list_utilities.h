#pragma once
#include <array_list.h>

namespace ssuds
{
	enum class SortType { ASCENDING, DESCENDING };
	template <class T>
	void bubble_sort(ssuds::ArrayList<T>& list, ssuds::SortType tp, int* num_ops = nullptr)
	{

		n = list.size() // number of elements
			// We need to do at most n passes to sort
			for (int i = 0, i < n-1, i++)
			for i in range(0, n - 1) :
				// Start of a pass
				for j in range(0, n - 1 - i) :
					// Check for out - of - place neighbors
					if my_list[j] > my_list[j + 1]:
						swap elements jand j + 1
	}

	bool out_of_order(ssuds::SortType type)
	{

	}
}