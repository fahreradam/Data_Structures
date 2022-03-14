// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <array_list_utility.h>
#include <fstream>
#include <vector>
#include <gtest/gtest.h>
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


    ssuds::ArrayList<float> testing = { 3.2, 4.5, 9.3, 11.4, 15.6, 18.9, 22.7, 29.0, 33.1, 37.4, 42.1 };
    std::cout << ssuds::find_binary_search(testing, ssuds::SortOrder::ASCENDING, 3.6f) << std::endl;

    // My simple, informal testing (I'm not using google tests here:-( )

    // Make an ArrayList with a few values
    // 
  
//    ssuds::ArrayList<float> flist{ 3.2f, 1.1f, 9.9f, 6.3f, 2.1f, 4.0f, 8.3f, 13.9f };
//    
//
//    // Check that we have some permutation of the initial flist values
//    std::cout << "flist = " << flist << std::endl;      // flist = [3.2, 1.1, 9.9, 6.3, 2.1, 4, 8.3, 13.9]  (some random permutation of this)
//    
//    // Make a copy so we can use it for bubble-sort and quicksort
//    ssuds::ArrayList<float> flist_copy(flist);
//    
//    // Test quicksort
//    long num_ops = ssuds::quicksort(flist, ssuds::SortOrder::ASCENDING);
//    std::cout << "flist (quicksorted) = " << flist << std::endl;      // flist (quicksorted) = [1.1, 2.1, 3.2, 4, 6.3, 8.3, 9.9, 13.9]
//    std::cout << "\t\t" << num_ops << " swaps" << std::endl;          //         7 swaps     (this will vary depending on the shuffle)
//    num_ops = ssuds::quicksort(flist, ssuds::SortOrder::DESCENDING);
//    std::cout << "flist (quicksorted) = " << flist << std::endl;      // flist (quicksorted) = [13.9, 9.9, 8.3, 6.3, 4, 3.2, 2.1, 1.1]
//    std::cout << "\t\t" << num_ops << " swaps" << std::endl;          //         7 swaps     (this will vary depending on the shuffle)
//
//    // Test bubblesort
//    ssuds::bubblesort(flist_copy, ssuds::SortOrder::ASCENDING);
//    std::cout << "flist (bubblesorted) = " << flist_copy << std::endl;      // flist (bubblesorted) = [1.1, 2.1, 3.2, 4, 6.3, 8.3, 9.9, 13.9]
//    std::cout << "\t\t" << num_ops << " swaps" << std::endl;                //          8 swaps (this will vary depending on the shuffle)
//    ssuds::bubblesort(flist_copy, ssuds::SortOrder::DESCENDING);
//    std::cout << "flist (bubblesorted) = " << flist_copy << std::endl;      // flist (bubblesorted) = [13.9, 9.9, 8.3, 6.3, 4, 3.2, 2.1, 1.1]
//    std::cout << "\t\t" << num_ops << " swaps" << std::endl;                //          8 swaps (this will vary depending on the shuffle)
//
//
//
//    // Test binary search / find.  This seems kind of silly to test this way, but it will test every value and make
//    //   we're able to find it.  If working, it should just output 0...7
//    ssuds::quicksort(flist, ssuds::SortOrder::ASCENDING);
//    for (int i = 0; i < flist.size(); i++)
//    {
//        std::cout << ssuds::find_binary_search(flist, ssuds::SortOrder::ASCENDING, flist[i]) << std::endl;
//    }
//    ssuds::quicksort(flist, ssuds::SortOrder::DESCENDING);
//    for (int i = 0; i < flist.size(); i++)
//    {
//        std::cout << ssuds::find_binary_search(flist, ssuds::SortOrder::DESCENDING, flist[i]) << std::endl;
//    }
//    
//
//
//    // Now do our "stress test" -- generate a list of random floats of size 100 (and then of increasing sizes, step of 100 up to 1000000000)
//    std::ofstream results("..\\..\\results.txt");
//    std::ofstream results_csv("..\\..\\results.csv");
//    // Reference: https://www.cplusplus.com/reference/random/
//    std::default_random_engine generator;
//    std::chrono::steady_clock::time_point start, end;
//    std::uniform_real<float> distribution(-10000000.0f, 10000000.0f);
//    std::chrono::milliseconds elapsed;
//
//    results_csv << ", Copy-time, QS-ops, QS-time, BS-ops, BS-time, BSearch-ops, BSearch-time, LSearch-ops, LSearch-time" << std::endl;
// 
//    for (int sample_size = 1000; sample_size < /*1000000000*/210000; sample_size += 1000)
//    {
//        std::cout << "Batch-processing sample size=" << sample_size << "...";
//        // Generate the sample
//        results << "SampleSize=" << sample_size << std::endl;
//        results << "=========================" << std::endl;
//        results_csv << sample_size << ",";
//        ssuds::ArrayList<float> AL;
//        for (int i = 0; i < sample_size; i++)
//        {
//            float num = distribution(generator);
//            AL.append(num);
//        }
//
//        // Get the first element of AL (to find later)
//        float find_val = AL[0];
//
//        /*#define TIMING(op, label) \
//op;\
//\
//;
//
//#define TIMING_AND_OPS(op, label) start = std::chrono::steady_clock::now();\
//num_ops = op;\
//*/
//
//        // Make a backup copy of AL
//        std::cout << "copy...";
//        start = std::chrono::steady_clock::now();
//        ssuds::ArrayList<float> AL_copy(AL);
//        end = std::chrono::steady_clock::now();
//        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); 
//        results << "\tCopy time: " << elapsed.count() << "ms" << std::endl; 
//        results_csv << elapsed.count() << ",";
//
//
//        // Sort AL using quicksort
//        std::cout << "quicksort...";
//        start = std::chrono::steady_clock::now();
//        num_ops = ssuds::quicksort(AL, ssuds::SortOrder::ASCENDING);
//        end = std::chrono::steady_clock::now();
//        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); 
//        results << "\tQuicksort: " << elapsed.count() << "ms and " << num_ops << " operations" << std::endl; 
//        results_csv << num_ops << ", " << elapsed.count() << ",";
//
//        // Sort AL_copy using bubble-sort
//        std::cout << "bubble-sort...";
//        start = std::chrono::steady_clock::now();
//        num_ops = ssuds::bubblesort(AL_copy, ssuds::SortOrder::ASCENDING);
//        end = std::chrono::steady_clock::now();
//        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); 
//        results << "\tBubblesort: " << elapsed.count() << "ms and " << num_ops << " operations" << std::endl; 
//        results_csv << num_ops << ", " << elapsed.count() << ",";
//
//        // Find our item with binary search
//        std::cout << "binary-search...";
//        start = std::chrono::steady_clock::now();
//        ssuds::find_binary_search(AL, ssuds::SortOrder::ASCENDING, find_val, &num_ops);
//        end = std::chrono::steady_clock::now();
//        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); 
//        results <<  "\tBinarySearch: " << elapsed.count() << "ms and " << num_ops << " operations" << std::endl; 
//        results_csv << num_ops << ", " << elapsed.count() << ",";
//
//        // Find our item with linear search (Lab1)
//        std::cout << "linear-search...";
//        start = std::chrono::steady_clock::now();
//        num_ops = AL.find(find_val);
//        end = std::chrono::steady_clock::now();
//        elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(end - start); 
//        results << "\tLinear Search: " << elapsed.count() << "ms and " << num_ops << " operations" << std::endl; 
//        results_csv << num_ops << ", " << elapsed.count() << ",";
//
//        std::cout << "done!" << std::endl;
//        results_csv << "\n";
    //}
}
