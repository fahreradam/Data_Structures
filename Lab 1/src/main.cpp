#include <iostream>
#include <array_list.h>

int main()
{
	ssuds::ArrayList tester;
	tester.append("1");
	tester.append("2");
	tester.append("4");
	std::cout << tester.find("4") << std::endl;
	std::cout << tester.get(1) << std::endl;
	tester.insert("3", 2);
	std::cout << tester.find("4") << std::endl;
	tester.clear();
	tester.insert("start of the array", 0);
	std::cout << tester.get(0) << std::endl;
	tester.append("1");
	tester.append("1st place");
	tester.append("1");
	std::cout << tester.get(1) << std::endl;
	tester.remove_all("1");
	std::cout << tester.get(0) << std::endl;



}