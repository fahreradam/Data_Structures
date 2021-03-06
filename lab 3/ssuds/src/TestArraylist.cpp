#include <iostream>
#include <array_list.h>
#include <fstream>
#include <gtest\gtest.h>
#include <sstream>


TEST(ArrayListTest, PrintingAnArray)
{
    ssuds::ArrayList<float> test_list;
    test_list.append(4);
    test_list.append(5);

    std::stringstream ss;
    ss << test_list;
    EXPECT_EQ(ss.str(), "[4, 5]");;

}

TEST(ArrayListTests, BracketOperator)
{
    ssuds::ArrayList<int> ilist;
    ilist.append(4);
    ilist.append(5);

    EXPECT_EQ(ilist[0], 4);

    int result = 0;
    try
    {
        ilist[2];
    }
    catch (std::out_of_range)
    {
        result = 1;
    }
    EXPECT_EQ(result, 1);

}


TEST(ArrayListTests, IteratorTest)
{
    // Testing begin
    ssuds::ArrayList<int> ilist;
    ssuds::ArrayList<int>::ArrayListIterator it;
    it = ilist.begin();
   
    EXPECT_EQ(it != ilist.end(), false);

    ilist.append(4);
    ilist.append(5);
    ilist.append(6);
    it = ilist.begin();
    EXPECT_EQ(*it, 4);

    it++;
    EXPECT_EQ(*it, 5);

    it++;
    EXPECT_EQ(*it, 6);
    
    it++;
    EXPECT_EQ(it != ilist.end(), false);

    // Testing rbegin

    // Testing rbegin
    ilist.clear();
    ilist.append(4);
    ilist.append(5);
    ilist.append(6);
    it = ilist.rbegin();

    EXPECT_EQ(*it, 6);

    it++;
    EXPECT_EQ(*it, 5);

    ++it;
    EXPECT_EQ(*it, 4);

    it++;
    EXPECT_EQ(it != ilist.rend(), false);

}

ssuds::ArrayList<int>func()
{
    ssuds::ArrayList<int>temp;
    temp.append(42);
    return temp;
}


TEST(ArrayListTests, Constructors)
{
    ssuds::ArrayList<int> a; // calles defult constructor
    a.append(4);

    ssuds::ArrayList<int> b(a); // calls copy constructor
    std::stringstream ss;
    ss << a;

    EXPECT_NE(ss.str(), "[2]"); // Will fail
    EXPECT_EQ(ss.str(), "[4]");
    ss.str(std::string());


    ssuds::ArrayList<int> c = func(); // calls move constructor
    ss << c;
    EXPECT_EQ(ss.str(), "[42]");
    ss.str(std::string());

    ssuds::ArrayList<int> d = { 1, 2, 3, 4 }; // calls initialize_list constructor
    ss << d;
    EXPECT_EQ(ss.str(), "[1, 2, 3, 4]");


}

TEST(ArrayListTests, ArrayListMethods)
{
    ssuds::ArrayList<float> a;
    a.append(4.0f);
    a.append(8.6f);
    a.append(34.2f);

    EXPECT_EQ(a[0], 4.0);
    a[0] = a[1];
    EXPECT_EQ(a[0], 8.6f); // errored if set to 8.6 and not 8.6f

    EXPECT_EQ(a.find(34.2), 2);

    EXPECT_EQ(a.size(), 3);

    EXPECT_EQ(a.capacity(), 5);


    int result = 0;
    try
    {
        a.remove(5);
    }
    catch (std::out_of_range)
    {
        result = 1;
    }
    EXPECT_EQ(result, 1);
}

int Run_Test(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

int main(int argc, char ** argv)
{
    Run_Test(argc, argv);
}

