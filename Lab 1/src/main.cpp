#include <iostream>
#include <array_list.h>

int main()
{
	ssuds::ArrayList tester;

	tester.append("Start of array");
	tester.append("Adam");
	tester.append("Fahrer");
	tester.append("end of array");

	std::cout << "The size of the array is " << tester.size() << std::endl;
	
	std::cout << "" << std::endl;
	for(int i =0; i < tester.size(); i ++)
		std::cout << tester.get(i) << std::endl;

	tester.clear();
	tester.append("start");
	tester.append("1");
	tester.append("1");
	tester.append("1");
	tester.append("last");

	for (int i = 0; i < tester.size(); i++)
		std::cout << "index " << i << " is '" << tester.get(i) << "'" << std::endl;

	tester.remove_all("1");

	for (int i = 0; i < tester.size(); i++)
		std::cout << "index " << i << " is '" << tester.get(i) << "'" << std::endl;

	tester.insert("middle", 1);

	for (int i = 0; i < tester.size(); i++)
		std::cout << "index " << i << " is '" << tester.get(i) << "'" << std::endl;



}