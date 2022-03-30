#include <gtest/gtest.h>
#include <unordered_map.h>
#include <ostream>

TEST(UnorderedMapTests, BracketOperator)
{
	ssuds::UnorderedMap<std::string, int> ulist;
	ulist["bob"] = 45;
	ulist["steve"] = 60;
	ulist["khjgertjnu"] = 8934;
	std::cout << ulist << std::endl;
	ulist["bob"] = 31;

	std::cout << ulist << std::endl;
}