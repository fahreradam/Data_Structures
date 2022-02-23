// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>
#include <array_list_utilities.h>
#include <chrono>


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
    std::ofstream output_file("..\\..\\media\\data2.csv");
    output_file << "Qsort_Numb, Qsort_Time, Qsort_Iterations, Bubble_Numb, Bubble_Time, Bubble_Iterations, BinarySort_Time, BinarySort_Iterations, LinearSearch_Time, LinearSearch_Iterations" << std::endl;
    int i = 1000;
    long* num_ops = 0;
    float start_time = 0;

    std::default_random_engine generator;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    


    while (i <= 200000)
    {
        ssuds::ArrayList<float> testing_list;
        ssuds::random_list(testing_list, i);
        ssuds::shuffle(testing_list);
        ssuds::ArrayList<float> testing_list2(testing_list);

        start = std::chrono::system_clock::now();
        int* swap_num = ssuds::qsort(testing_list, ssuds::SortType::ASCENDING);
        end = std::chrono::system_clock::now();

        std::chrono::duration<double> elapsed_seconds = end - start;

        output_file << i << ", " << elapsed_seconds.count() <<"s, " << swap_num <<", ";
        
        start = std::chrono::system_clock::now();
        ssuds::bubble_sort(testing_list2, ssuds::SortType::ASCENDING, num_ops);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        output_file << i << ", " << elapsed_seconds.count() << "s, " << num_ops << ", ";


        num_ops = 0;
        start = std::chrono::system_clock::now();
        ssuds::binary_search(testing_list2, testing_list[i/2], num_ops);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        output_file << elapsed_seconds.count() << "s, " << num_ops << ", ";

        start = std::chrono::system_clock::now();
        long n = testing_list2.find(testing_list2[i/2]);
        end = std::chrono::system_clock::now();

        elapsed_seconds = end - start;
        output_file << elapsed_seconds.count() << "s, " << n << std::endl;

        

        i += 1000;
    }
    output_file.close();





    

}
