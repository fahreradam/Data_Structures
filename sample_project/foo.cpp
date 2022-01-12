#include "foo.h"
#include <iostream>

void ssuds::Foo::talk()
{
	std::cout << name << " says Hey!" << std::endl;
}

ssuds::Foo::Foo(std::string start_name) : name(start_name), age(0)
{
	// One way to initialize our attributes:
	//name = start_name;
	//age = 0;
	// The constructor-initializer above is slightly more efficient.
	std::cout << "constructor for '" << name << "'" << std::endl;
}

ssuds::Foo::~Foo()
{
	std::cout << "destructor for '" << name << "'" << std::endl;
}