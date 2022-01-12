#include <iostream>
#include "foo.h"

int main()
{
    int x = 42;
    std::cout << "Hello World" << x << std::endl;

    ssuds::Foo f("Bob");

    ssuds::Foo* fptr;       // fptr is a point an holds an address of a Foo 
                            // object (uninitialized)
    fptr = &f;              // store the address of f in fptr.
    (*fptr).talk();         // de-references fptr (which is f) and call talk 
                            // through it.
    fptr->talk();           // exactly line 14.  Called "syntactic sugar"

    // Make an array of 5 strings
    std::string string_list[5];
    string_list[0] = "AAA";
    string_list[1] = "BBB";
    // string_list[2]...string_list[4] hold empty string (b/c they have a constructor)
    std::string* sptr;
    sptr = string_list;     // sptr holds the address of the beginning of string_list
    (*(sptr + 1)) = "BBB";
    sptr[1] = "BBB";        // Same as line 25.

    // Dynamic allocation of a single object
    fptr = new ssuds::Foo("Sue");   
    fptr->talk();
    delete fptr;            // Frees up the memory pointed to by fptr (fptr still
                            //  exists and holds a [now garbage] address)

    // Dynamic allocation of an ARRAY of objects
    int num_strings = rand() % 11 + 10;
    //std::string dyn_list[num_strings];    // ERROR b/c num_strings not initialized 
    //                                            until run-time
    std::string* dyn_list = new std::string[num_strings];
    dyn_list[0] = "AAA";
    dyn_list[1] = "BBB";
    delete[] dyn_list;              // The [] is to tell it this is an array 

    f.talk();
}