#include <iostream>
#include <string>
#include <ordered_set.h>
#include <array_list.h>
#include <gtest/gtest.h>
#include <vector>
#include <Windows.h>

int main()
{
    // My temporary tests (I didn't end up doing google tests on this one...sorry:-()

    // ======================================
    // | Basic operations                   |
    // ======================================
    ssuds::OrderedSet<std::string> slist;
    slist.insert("Doug");
    slist.insert("Abe");
    slist.insert("Bob");
    slist.insert("Carl");
    slist.insert("Abe");
    slist.insert("Erin");
    slist.insert("Erin");
    slist.insert("Eric");
    slist.insert("Erica");
    slist.insert("Ericaz");
    slist.insert("Carline");
    slist.insert("Dan");

    std::vector<std::string> tests{ "Abe", "Doug", "Eric", "Xavier", "Zazu", "Carlx" };
    for (std::string cur_test : tests)
    {
        if (slist.contains(cur_test))
            std::cout << "'" << cur_test << "' IS in slist" << std::endl;
        else
            std::cout << "'" << cur_test << "' is NOT in slist" << std::endl;
    }

    // ======================================
    // | traversals and tree-view           |
    // ======================================

    ssuds::ArrayList<std::string> results = slist.traversal(ssuds::TraversalType::IN_ORDER);
    std::cout << "contents: " << results << std::endl;

    std::cout << "tree-view: " << std::endl << slist.tree_string() << std::endl;
    // Doug
    //    L: Abe
    //       R: Bob
    //          R: Carl
    //              R: Carline
    //                 R: Dan
    //    R: Erin
    //       L: Eric
    //          R: Erica
    //             R: Ericaz
    std::cout << "height = " << slist.get_height() << std::endl;


    // ======================================
    // | Iterator tests                     |
    // ======================================
    std::cout << "slist = " << slist << std::endl;
    ssuds::OrderedSet<std::string>::OrderedSetIterator iter = slist.begin();
    while (iter != slist.end())
    {
        std::string cur = *iter;
        std::cout << cur << std::endl;
        ++iter;
    }
    std::cout << "for-each test:\n";
    for (std::string s : slist)
        std::cout << "\t" << s << std::endl;



    // ======================================
    // | rebalance                          |
    // ======================================

    slist.rebalance();
    std::cout << "tree-view: " << std::endl << slist.tree_string() << std::endl;
    // Dan
    //    L: Bob
    //       L: Abe
    //       R: Carl
    //          R: Carline
    //    R: Erica
    //       L: Doug
    //          R: Eric
    //       R: Ericaz
    //          R: Erin
    std::cout << "height = " << slist.get_height() << std::endl;


    // ======================================
    // | remove                              |
    // ======================================
    // tests of case1
    slist.erase("Erin");
    slist.erase("Abe");
    std::cout << "tree-view: " << std::endl << slist.tree_string() << std::endl;
    // Dan
    //    L: Bob
    //       R: Carl
    //          R: Carline
    //    R: Erica
    //       L: Doug
    //          R: Eric
    //       R: Ericaz

    // tests of case2
    slist.erase("Bob");
    slist.erase("Doug");
    std::cout << "tree-view: " << std::endl << slist.tree_string() << std::endl;
    // Dan
    //    L: Carl
    //       R: Carline
    //    R: Erica
    //       L: Eric
    //       R: Ericaz

    // tests of case 3
    slist.erase("Erica");
    // Dan
    //    L: Carl
    //       R: Carline
    //    R: Ericaz
    //       L: Eric
    slist.erase("Dan");
    std::cout << "tree-view: " << std::endl << slist.tree_string() << std::endl;
    // Eric
    //    L: Carl
    //       R: Carline
    //    R: Ericaz
    


    // ======================================
    // | set-operation functions            |
    // ======================================
    ssuds::OrderedSet<int> set1{ 1, 5, 7, 3, 2, 5, 9, 13 };
    ssuds::OrderedSet<int> set2{ 5, 2, 13, 99, 73 };

    std::cout << "set functions" << std::endl;
    std::cout << "=============" << std::endl;
    ssuds::ArrayList<int> union_result_arr;
    ssuds::OrderedSet<int> union_result;
    union_result = set1 | set2;
    union_result_arr = union_result.traversal(ssuds::TraversalType::IN_ORDER);
    ssuds::ArrayList<int> intersect_result_arr;
    ssuds::OrderedSet<int> intersect_result;
    intersect_result = set1 & set2;
    intersect_result_arr = intersect_result.traversal(ssuds::TraversalType::IN_ORDER);
    ssuds::ArrayList<int> diff_result_arr;
    ssuds::OrderedSet<int> diff_result;
    diff_result = set1 - set2;
    diff_result_arr = diff_result.traversal(ssuds::TraversalType::IN_ORDER);
    std::cout << "union = " << union_result_arr << std::endl;
    std::cout << "intersection = " << intersect_result_arr << std::endl;
    std::cout << "rel-diff = " << diff_result_arr << std::endl;



    // Invoke all google test fixtures we've registered
    //testing::InitGoogleTest();
    //RUN_ALL_TESTS();
}
