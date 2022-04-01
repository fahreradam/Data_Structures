#include <iostream>
#include <string>
#include <linked_list.h>
#include <gtest/gtest.h>
#include <order_set.h>
#include <unordered_map.h>

int main()
{
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
	ssuds::UnorderedMap<int, int> test_list;
	for (int i = 0; i < 10; i++)
		test_list[i] = i;

	std::cout << test_list << std::endl;

}
