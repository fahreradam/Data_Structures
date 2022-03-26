#include <gtest/gtest.h>
#include <order_set.h>
#include <ostream>

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