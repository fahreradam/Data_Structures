// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <fstream>
#include <gtest\gtest.h>

// Just a silly class to test that our ArrayList is fully templatized
//void a_func(Foo f);
class Foo
{
protected:
    int value;
    std::string name;
public:
    Foo() : value(0), name("") {}           // <- must have to be used in the "C++-memory-style" version of ArrayList
    Foo(int v, std::string n) : value(v), name(n) {}
    int get_value() const { return value; }
    std::string get_name() const { return name; }
};

// This isn't a templated class, so we have more flexibility in defining the stream operator
std::ostream& operator<<(std::ostream& os, const Foo& f)
{
    os << "{Foo:" << f.get_name() << "-" << f.get_value() << "}";
    return os;
}


TEST(BasicTests, BasicTest01)
{
    int x = 47;
    int y = 47;
    EXPECT_EQ(x, y) << "They're not equal!!";


    ssuds::ArrayList<float> test_list;
    test_list.append(1.5f);
    test_list.append(1.5f);

    EXPECT_EQ(test_list[0], test_list[1]);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
    
}
