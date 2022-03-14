#include "mars.h"
#include <iostream>

int main()
{
	ssuds::Mars string;

	std::cout << string << std::endl;

	ssuds::Mars list(string);
	std::cout << list << std::endl;

	ssuds::Mars list2 = { "fds", "fes", "g", 156.53f };
	std::cout << list2 << std::endl;

	ssuds::Mars list3(list2);
	std::cout << list3 << std::endl;

	string = list3;
	std::cout << string << std::endl;

}