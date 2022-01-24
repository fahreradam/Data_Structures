#include <iostream>
#include <array_list.h>
#include <stdexcept>
#include <fstream>
#include <string>

#define MODE 1		 // Change MODE to 2 for Part 5

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


	std::cout << "Removed " << tester.remove_all("1") << " instances of 1"<<'\n' << std::endl; // Prints Removed 3 instances of 1

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
int main()
{
	ssuds::ArrayList tester;

	std::fstream input_file("..\\..\\data\\my_data.txt", std::ios::in);
	int menu_choice = -1;
	int main_screen = 1;
	if (input_file.is_open())
	{
		int i = 0;
		std::string item;
		while (!input_file.eof())
		{
			std::string line;
			std::getline(input_file, line);
			tester.append(line);
		}
		while (menu_choice != 8)
		{
			if(main_screen == 1)
			{ 
				std::cout << "1:		View what's in the array" << std::endl;
				std::cout << "2:		What is the size of the array" << std::endl;
				std::cout << "3:		Add an item by index" << std::endl;
				std::cout << "4:		Add an item to the end of the array" << std::endl;
				std::cout << "5:		Remove an item by index" << std::endl;
				std::cout << "6:		Remove all items with the same name" << std::endl;
				std::cout << "7:		Clear the array" << std::endl;
				std::cout << "8:		Close program\n" << std::endl;
				std::cout << "What would you like to do?\nPlease enter a number: ";
				std::cin >> menu_choice;
				main_screen = 0;
			}
			
			if (std::cin.good())
			{
				std::cin.ignore(10000, '\n');
				// View Array
				if (menu_choice == 1)
				{
					for (int i = 0; i < tester.size(); i++)
						std::cout << "item at index " << i << " is " << tester.get(i) << std::endl;
					std::cout << "Press any number to return to main menu or press 8 to close: "; // This goes for all the returns, just pressing enter does not work you need to type at least one character
					std::cin >> menu_choice;
					if (std::cin.good())
					{
						std::cin.ignore(10000, '\n');
						if (menu_choice == 8)
							break;
						else
							main_screen = 1;
					}
					else
					{
						std::cin.clear();			// Clears the error state
						std::cin.ignore(10000, '\n');
						main_screen = 1;
					}
				}
				// View Size of Array
				if (menu_choice == 2)
				{
					std::cout << "The size of the array is " << tester.size() << std::endl;

					std::cout << "Press any number to return to main menu or press 8 to close: ";
					std::cin >> menu_choice;
					if (std::cin.good())
					{
						std::cin.ignore(10000, '\n');
						if (menu_choice == 8)
							break;
						else
							main_screen = 1;
					}
					else
					{
						std::cin.clear();			// Clears the error state
						std::cin.ignore(10000, '\n');
						main_screen = 1;
					}
				}
				// Add item by index
				if (menu_choice == 3)
				{
					std::cout << "What would you like to add: ";
					std::getline(std::cin, item);
					std::cout << "Where would you like to add this: ";
					std::cin >> i;
					std::cin.ignore(10000, '\n');
					tester.insert(item, i);

					std::cout << "Press any number to return to main menu or press 8 to close: ";
					std::cin >> menu_choice;
					if (std::cin.good())
					{
						std::cin.ignore(10000, '\n');
						if (menu_choice == 8)
							break;
						else
							main_screen = 1;
					}
					else
					{
						std::cin.clear();			// Clears the error state
						std::cin.ignore(10000, '\n');
						main_screen = 1;
					}
				}
				// Add item at the end of array
				if (menu_choice == 4)
				{
					std::cout << "What would you like to add: ";
					std::getline(std::cin, item);
					tester.append(item);

					std::cout << "Press any number to return to main menu or press 8 to close: ";
					std::cin >> menu_choice;
					if (std::cin.good())
					{
						std::cin.ignore(10000, '\n');
						if (menu_choice == 8)
							break;
						else
							main_screen = 1;
					}
					else
					{
						std::cin.clear();			// Clears the error state
						std::cin.ignore(10000, '\n');
						main_screen = 1;
					}
				}
				// Remove by index
				if (menu_choice == 5)
				{
					std::cout << "At what index would you like to be removed: ";
					std::cin >> i;
					std::cin.ignore(10000, '\n');
					tester.remove(i);

					std::cout << "Press any number to return to main menu or press 8 to close: ";
					std::cin >> menu_choice;
					if (std::cin.good())
					{
						std::cin.ignore(10000, '\n');
						if (menu_choice == 8)
							break;
						else
							main_screen = 1;
					}
					else
					{
						std::cin.clear();			// Clears the error state
						std::cin.ignore(10000, '\n');
						main_screen = 1;
					}
				}
				// Remove all by item
				if (menu_choice == 6)
				{
					std::cout << "What instance would you like to remove all of: ";
					std::getline(std::cin, item);
					tester.remove_all(item);

					std::cout << "Press any number to return to main menu or press 8 to close: ";
					std::cin >> menu_choice;
					if (std::cin.good())
					{
						std::cin.ignore(10000, '\n');
						if (menu_choice == 8)
							break;
						else
							main_screen = 1;
					}
					else
					{
						std::cin.clear();			// Clears the error state
						std::cin.ignore(10000, '\n');
						main_screen = 1;
					}
				}
				// Clear the array
				if (menu_choice == 7)
				{
					tester.clear();
					std::cout << "Array has been cleared" << std::endl;

					std::cout << "Press enter to return to main menu or press 8 to close: ";
					std::cin >> menu_choice;
					if (std::cin.good())
					{
						std::cin.ignore(10000, '\n');
						if (menu_choice == 8)
							break;
						else
							main_screen = 1;
					}
					else
					{
						std::cin.clear();			// Clears the error state
						std::cin.ignore(10000, '\n');
						main_screen = 1;
					}
				}
			}
			else
			{
				std::cout << "Invalid entry\n";
				std::cin.clear();			// Clears the error state
				std::cin.ignore(10000, '\n');
				main_screen = 1;
			}
		}
		std::fstream output_file("..\\..\\data\\my_data.txt", std::ios::out);
		for (i = 0; i < tester.size(); i++)
			if(i != tester.size()-1)
				output_file << tester.get(i) << std::endl;
			else
				output_file << tester.get(i);
		output_file.close();
	}
}
#endif