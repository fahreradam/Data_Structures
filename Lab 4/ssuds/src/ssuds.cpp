// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>
#include <array_list_utilities.h>


// Just a silly class to test that our ArrayList is fully templatized.  I put it here rather than
// in the google tests, just so you can see.
class Foo
{
protected:
    int value;
    std::string name;
public:
    //Foo() : value(0), name("") {}           // <- must have to be used in ArrayList
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



int main()
{
    // Invoke all google test fixtures we've registered
    testing::InitGoogleTest();
    RUN_ALL_TESTS();
    ssuds::ArrayList<std::string> header = {"SortType","Numb_Items","Iterations", "Time"};
    std::fstream output_file("..\\..\\media\\data.txt", std::ios::out);
    int i = 1000;
    int n = 1000;
    int* num_ops = 0;

    std::default_random_engine generator;
    


    while (i < 20000)
    {
        std::uniform_int_distribution<int> distribution(n, i);
        int j = distribution(generator);

        ssuds::ArrayList<float> testing_list;
        ssuds::random_list(testing_list, j);
        ssuds::shuffle(testing_list);
        ssuds::ArrayList<float> testing_list2(testing_list);
        ssuds::qsort(testing_list);
        ssuds::bubble_sort(testing_list2, ssuds::SortType::ASCENDING, num_ops);
        i += 1000;
    }





    

}
