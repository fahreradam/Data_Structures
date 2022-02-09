// ssuds.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <array_list.h>
#include <fstream>
#include <gtest\gtest.h>
#include <sstream>

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





