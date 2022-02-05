// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <fstream>
#include <vector>

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


int main()
{
    // The basic test program (for floats)
    ssuds::ArrayList<float> float_list;
    float_list.append(2.1f);
    float_list.append(3.6f);
    std::cout << float_list.size() << std::endl;                  // 2
    std::cout << float_list[0] << std::endl;                      // 2.1
    std::cout << float_list[1] << std::endl;                      // 3.6
    float_list.insert(1.8f, 0);
    float_list.insert(4.2f, 3);
    float_list.insert(2.0f, 1);                         
    for (int i = 0; i < float_list.size(); i++)                   // 1.8 2 2.1 3.6 4.2
        std::cout << float_list[i] << " ";
    std::cout << std::endl;
    float_list.append(2.0f);                                      // <= a capacity increase should be triggered here
    float_list.append(2.0f);
    for (int i = 0; i < float_list.size(); i++)                   // 1.8 2 2.1 3.6 4.2 2 2
        std::cout << float_list[i] << " ";
    std::cout << std::endl;
    std::cout << float_list.remove_all(2.0f) << std::endl;        // 3 <= a capacity decrease should be triggered here
    for (int i = 0; i < float_list.size(); i++)                   // 1.8 2.1 3.6 4.2
            std::cout << float_list[i] << " ";
    std::cout << std::endl;

    // Test the stream operator
    std::cout << float_list << std::endl;                         // [1.8, 2.1, 3.6, 4.2]

    // Test the = operator
    ssuds::ArrayList<float> float_list_copy = float_list;         // (will call the copy-constructor)
    std::cout << float_list_copy << std::endl;                    // [1.8, 2.1, 3.6, 4.2]
    float_list_copy.remove(1);
    std::cout << float_list_copy << std::endl;                    // [1.8, 3.6, 4.2]
    std::cout << float_list << std::endl;                         // [1.8, 2.1, 3.6, 4.2]

    float_list_copy = float_list;                                 // (will call the = operator)
    std::cout << float_list_copy << std::endl;                    // [1.8, 2.1, 3.6, 4.2]

    // Just for the sake of argument -- make sure it'll work with custom-types too
    //std::vector<Foo> foo_vec;
    //foo_vec.push_back(Foo(5, "Bob"));
    ssuds::ArrayList<Foo> foo_test;
    foo_test.append(Foo(5, "Bob"));
    foo_test.insert(Foo(4, "Abe"), 0);
    foo_test.append(Foo(7, "Carl"));
    std::cout << foo_test << std::endl;                           // [{Foo:Abe-4}, {Foo:Bob-5}, {Foo:Carl-7}]
    
}
