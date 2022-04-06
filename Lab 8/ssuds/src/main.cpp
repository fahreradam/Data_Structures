#include <iostream>
#include <string>
#include <unordered_map.h>
#include <gtest/gtest.h>
#include <vector>
#include <Windows.h>
#include <unordered_map>

int main()
{
    std::unordered_map<std::string, int> test_map;
    test_map["a"] = 11;
    test_map["b"] = 13;
    std::unordered_map<std::string, int>::iterator it = test_map.begin();
    while (it != test_map.end())
    {
        std::pair<std::string, int> cur = *it;
        std::cout << "key=" << cur.first << "   value=" << cur.second << std::endl;
        ++it;
    }

    // My handful of "base-level" tests before I switched to google-tests
    ssuds::UnorderedMap<std::string, int> my_map;
    std::cout << my_map.size() << std::endl;                    // 0
    my_map["Bob"] = 42;
    my_map["Sue"] = 99;
    my_map["Carl"] = -1;
    my_map["Sue"] = 98;
    std::cout << my_map.size() << std::endl;                    // 3
    std::cout << my_map << std::endl;                           // {Sue: 98, Carl: -1, Bob: 42}         // your order might be different!

    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
}
