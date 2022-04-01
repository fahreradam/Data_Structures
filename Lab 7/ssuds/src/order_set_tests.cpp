#include <gtest/gtest.h>
#include <order_set.h>
#include <ostream>

#define THIS_ONE  0

#if THIS_ONE == 1

TEST(OrderSet, Methods)
{
	ssuds::OrderedSet<std::string> olist;
	olist.insert("g");
	olist.insert("a");
	olist.insert("c");
	olist.insert("h");
	olist.insert("o");

	ssuds::ArrayList<std::string> alist;
	olist.traversal(alist, ssuds::NodeType::Pre);
	std::stringstream ss;
	ss << alist;
	// Insert, traversal, and size tests
	ASSERT_EQ(ss.str(), "[g, a, c, h, o]");
	ASSERT_EQ(olist.size(), 5);

	// clear tests
	olist.clear();
	ASSERT_EQ(olist.size(), 0);

	// contains tests

	olist.insert("gsersdg");
	olist.insert("gldr");
	olist.insert("adsa");
	olist.insert("ohng");

	ASSERT_TRUE(olist.contains("adsa"));
	ASSERT_FALSE(olist.contains("fgkjgr"));

	// reballance and get height tests
	ssuds::OrderedSet<int> rlist;
	ssuds::ArrayList<int> alist2;

	for (int i = 0; i <= 200; i += 10)
	{
		if (rlist.size() == 0)
			rlist.insert(50);
		rlist.insert(i);
	}
	rlist.traversal(alist2, ssuds::NodeType::In_Order);
	std::stringstream ss2;
	ss2 << alist2;
	ASSERT_EQ(ss2.str(), "[0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, " 
							"120, 130, 140, 150, 160, 170, 180, 190, 200]");
	ASSERT_EQ(rlist.get_height(), 16);
	rlist.rebalance();
	std::stringstream ss3;
	ASSERT_EQ(rlist.get_height(), 5);

	// erase tests
	ASSERT_TRUE(rlist.erase(100));
	ASSERT_EQ(rlist.size(), 20);
	ASSERT_FALSE(rlist.erase(100));
	std::stringstream ss4;
	rlist.traversal(alist2, ssuds::NodeType::In_Order);
	ss4 << alist2;
	ASSERT_EQ(ss4.str(), "[0, 10, 20, 30, 40, 50, 60, 70, 80, 90, 110, "
							"120, 130, 140, 150, 160, 170, 180, 190, 200]");
}

TEST(OrderSetIterator, IterationTests)
{
	ssuds::OrderedSet<int> ilist;

	for (int i = 0; i <= 200; i += 10)
	{
		if (ilist.size() == 0)
			ilist.insert(50);
		ilist.insert(i);
	}
	ssuds::OrderedSet<int>::OrderedSetIterator it = ilist.begin();
	ssuds::OrderedSet<int>::OrderedSetIterator it_end = ilist.end();
	ssuds::ArrayList<int> alist;

	//ASSERT_NE(it, it_end); // Attemped but was getting an error I couldn't figure out

	ilist.traversal(alist, ssuds::NodeType::In_Order);
	int val1 = *it;
	ASSERT_EQ(val1, 50);
	
	it++;

	for (int i = 0; it != nullptr; i += 10, it++)
	{
		ASSERT_EQ(*it, i);
	}

	ssuds::OrderedSet<int> test;
	test.insert(100);
	test.insert(50);
	test.insert(40);
	test.insert(30);
	test.insert(20);
	test.insert(60);
	test.insert(35);
	ssuds::OrderedSet<int>::OrderedSetIterator it_test = test.begin();
	ASSERT_EQ(*it_test, 100);
	++it_test;
	ASSERT_EQ(*it_test, 20);
	++it_test;
	ASSERT_EQ(*it_test, 30);
	++it_test;
	ASSERT_EQ(*it_test, 35);
	++it_test;
	ASSERT_EQ(*it_test, 40);
	++it_test;
	ASSERT_EQ(*it_test, 50);
	++it_test;
	ASSERT_EQ(*it_test, 60);
	++it_test;
	ASSERT_EQ(*it_test, 100);
}

#endif