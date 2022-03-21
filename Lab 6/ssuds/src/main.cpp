#include <iostream>
#include <string>
#include <linked_list.h>
#include <gtest/gtest.h>
#include <order_set.h>

int main()
{
    //testing::InitGoogleTest();
    //RUN_ALL_TESTS();

    ssuds::OrderedSet<float> S;
    S.insert(3.4f);
    S.insert(5.8f);
    S.insert(4.2f);
    S.insert(5.8f);
    std::cout << S.size();		// 3
}
