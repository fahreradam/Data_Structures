#include <gtest/gtest.h>
#include <unordered_map.h>
#include <ostream>

TEST(UnorderedMapTests, Methods)
{
	// Bracket Operator Testing
	ssuds::UnorderedMap<std::string, int> ulist;
	std::stringstream ss;
	ulist["bob"] = 45;
	ulist["steve"] = 60;
	ulist["khjgertjnu"] = 8934;
	ASSERT_EQ(ulist["bob"], 45);
	
	//Stream Operator
	ss << ulist;
	ASSERT_EQ(ss.str(), "{bob:45, khjgertjnu:8934, steve:60}");

	// Changing an already made std::pair
	ulist["bob"] = 31;
	ASSERT_EQ(ulist["bob"], 31);
	
	// Remove Operator
	ulist.remove("bob");
	ss.str("");
	ss << ulist;
	ASSERT_EQ(ss.str(), "{khjgertjnu:8934, steve:60}");

	ulist["ges"] = 468;

	
	// Size, Capacity, and grow operators
	ssuds::UnorderedMap<int, int> test_list;

	ASSERT_EQ(test_list.size(), 0);
	ASSERT_EQ(test_list.capacity(), 10);

	for (int i = 0; i < 10; i++)
		test_list[i] = i;
	
	ASSERT_EQ(test_list.size(), 9);
	ASSERT_EQ(test_list.capacity(), 20);
}

TEST(UnorderedMapTests, IterationsTest)
{
	ssuds::UnorderedMap<std::string, float> unmap;
	unmap["place"] = 32.0f;
	unmap["float"] = 41.0f;
	unmap["real"] = 54.9f;
	ssuds::UnorderedMap<std::string, float>::UnorderedMapIterator it = unmap.begin();
	
	std::pair<std::string, float>* pair;
	for (int i = 0; i < unmap.size(); i++)
	{
		pair = *it;
		std::cout << pair->first << ":" << pair->second << std::endl;
		it++;

	}
}