#include <iostream>
#include <array_list.h>
#include <stdexcept>
#include <fstream>

#define MODE 2

#if MODE == 1
int main()
{
	ssuds::ArrayList tester;

	tester.append("Start of array");
	tester.append("Adam");
	tester.append("Fahrer");
	tester.append("end of array");

	std::cout << "The size of the array is " << tester.size() << '\n' << std::endl; // Prints The size of the array is 4 and a new line

	std::cout << tester.get(0) << std::endl; // Prints Start of array
	std::cout << tester.get(1) << std::endl; // Prints Adam
	std::cout << tester.get(2) << std::endl; // Prints Fahrer
	std::cout << tester.get(3) << '\n'<< std::endl; // Prints end of array

	tester.clear();			// Clears the array

	tester.append("start");
	tester.append("1");
	tester.append("1");
	tester.append("1");
	tester.append("last");

	std::cout << tester.get(0) << std::endl; // Prints start
	std::cout << tester.get(1) << std::endl; // Prints 1
	std::cout << tester.get(2) << std::endl; // Prints 1
	std::cout << tester.get(3) << std::endl; // Prints 1
	std::cout << tester.get(4) << '\n' << std::endl; // Prints last


	std::cout << tester.remove_all("1") << '\n' << std::endl; // Prints 3

	std::cout << tester.get(0) << std::endl; // Prints start
	std::cout << tester.get(1) << '\n' << std::endl; // Prints last

	

	tester.insert("middle", 1);
	tester.insert("1", 0);
	std::cout << tester.size() << '\n' << std::endl; // Prints 4

	std::cout << tester.get(0) << std::endl; // Prints 1
	std::cout << tester.get(1) << std::endl; // Prints start
	std::cout << tester.get(2) << std::endl; // Prints middle
	std::cout << tester.get(3) << '\n' << std::endl; // Prints last


	std::cout << tester.size() << std::endl; // Prints 4
	// tester.insert("4", 10);								// Raises an index error
	// std::cout << tester.get(10) << std::endl;				// Raises an index error
}

#else
void main()
{
	ssuds::ArrayList tester;
	// Part 5
	std::fstream output_file("..\\..\\data\\my_data.txt", std::ios::out);
	output_file.close();

	std::fstream input_file("..\\..\\data\\my_data.txt", std::ios::in);

	// Part5.a: read data from the file (if there is one)
	// Part 5.b: interaction menu
	int menu_choice = -1;
	if (input_file.is_open())
	{
		int i = 0;
		while (!input_file.eof())
			std::string line;
		std::getline(input_file, line);
			tester.append(line);
		while (menu_choice != 9)
		{
			std::cout << "1		View what's in the array" 
			std::cout << "what do you want to do? ";
			std::cin >> menu_choice;
			if (std::cin.good())
			{
				std::cin.ignore(10000, '\n');
				// Execute that menu option
			}
			else
			{
				std::cout << "Invalid entry";
				std::cin.clear();			// Clears the error state
			}
		}
	}
	
	// Part 5.c: write data to the file (over-writing what was there)

}
#endif