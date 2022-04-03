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
	
	// Clear Method
	test_list.clear();
	ASSERT_EQ(test_list.size(), 0);
	ASSERT_EQ(test_list.capacity(), 20);

}

TEST(UnorderedMapTests, IterationsTest)
{
	// Forward Iteration
	ssuds::UnorderedMap<std::string, float> unmap;
	unmap["place"] = 32.0f;
	unmap["float"] = 41.0f;
	unmap["real"] = 54.9f;
	ssuds::UnorderedMap<std::string, float>::UnorderedMapIterator it = unmap.begin();
	
	std::pair<std::string, float>* pair;
	pair = *it;
	ASSERT_EQ(pair->first, "place");
	ASSERT_EQ(pair->second, 32.0f);
	it++;

	pair = *it;
	ASSERT_EQ(pair->first, "float");
	ASSERT_EQ(pair->second, 41.0f);
	it++;

	pair = *it;
	ASSERT_EQ(pair->first, "real");
	ASSERT_EQ(pair->second, 54.9f);

	// Backwards Iteration

	ssuds::UnorderedMap<std::string, float>::UnorderedMapIterator it_rend = unmap.rbegin();
	pair = *it_rend;
	ASSERT_EQ(pair->first, "real");
	ASSERT_EQ(pair->second, 54.9f);
	it_rend++;

	pair = *it_rend;
	ASSERT_EQ(pair->first, "float");
	ASSERT_EQ(pair->second, 41.0f);
	it_rend++;

	pair = *it_rend;
	ASSERT_EQ(pair->first, "place");
	ASSERT_EQ(pair->second, 32.0f);

	// Find Method

	ssuds::UnorderedMap<std::string, float>::UnorderedMapIterator it_find = unmap.find("float");

	pair = *it_find;
	ASSERT_EQ(pair->first, "float");
	ASSERT_EQ(pair->second, 41.0f);

	//ssuds::UnorderedMap<std::string, float>::UnorderedMapIterator it_find2 = unmap.find("not here");
	//pair = *it_find2;
	// ASSERT_NE(pair->first, "float"); //Errors which is expected because pair->first does not have a value

}