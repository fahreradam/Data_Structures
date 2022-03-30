#include <gtest/gtest.h>
#include <unordered_map.h>
#include <ostream>

TEST(UnorderedMapTests, BracketOperator)
{
	ssuds::UnorderedMap<std::string, int> ulist;
	std::stringstream ss;
	ulist["bob"] = 45;
	ulist["steve"] = 60;
	ulist["khjgertjnu"] = 8934;

	ASSERT_EQ(ulist["bob"], 45);
	
	ss << ulist;
	ASSERT_EQ(ss.str(), "{bob:45, khjgertjnu:8934, steve:60}");

	ulist["bob"] = 31;
	ASSERT_EQ(ulist["bob"], 31);
	
	ulist.remove("bob");
	ss.str("");
	ss << ulist;
	ASSERT_EQ(ss.str(), "{khjgertjnu:8934, steve:60}");
}