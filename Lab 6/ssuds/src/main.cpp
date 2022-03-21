#include <iostream>
#include <string>
#include <linked_list.h>
#include <gtest/gtest.h>
#include <order_set.h>

int main()
{
    // My temporary tests (I eventually did this in google-tests in linked_list_tests.cpp)
    ssuds::LinkedList<std::string> slist;
    slist.append("Abe");
    slist.append("Bob");
    slist.append("Carl");
    std::cout << "slist = " << slist << std::endl;
    ssuds::LinkedList<std::string>::LinkedListIterator iter = slist.begin();
    while (iter != slist.end())
    {
        std::string cur = *iter;
        std::cout << cur << std::endl;
        ++iter;
    }

    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}
