#include <gtest/gtest.h>
#include <linked_list.h>
#include <fstream>



TEST(LinkedListTests, LinkedListTests)
{
	ssuds::LinkedList<float> list;
	list.append(5.5f);
	list.append(3.3f);
	list.append(5.3f);
	std::stringstream ss;
	ssuds::LinkedList<float> list2(list);
	ss << list2;
	
	ASSERT_EQ(ss.str(), "[5.5, 3.3, 5.3]");
}

TEST(LinkedListIterationTest, LinkedListIteratorFind)
{
	ssuds::LinkedList<int> ilist{ 1, 5, 7, 13, 18, 22, 25, 30, 22, 38 };
	ssuds::LinkedList<int>::LinkedListIterator it = ilist.find(22);
	EXPECT_EQ(*it, 22);
	EXPECT_EQ(it.index(), 5);
	++it;
	EXPECT_EQ(*it, 25);
	EXPECT_EQ(it.index(), 6);
	it = ilist.find(22, it);
	EXPECT_EQ(*it, 22);
	EXPECT_EQ(it.index(), 8);

	++it;
	it = ilist.find(22, it);
	EXPECT_EQ(it != ilist.end(), false);
}

TEST(LinkedListIteratorTest, IterationTest)
{
	// Testing begin
	ssuds::LinkedList<int> ilist;
	ssuds::LinkedList<int>::LinkedListIterator it = ilist.begin();

	EXPECT_EQ(it != ilist.end(), false);

	ilist.append(4);
	ilist.append(5);
	ilist.append(6);
	it = ilist.begin();
	EXPECT_EQ(*it, 4);

	it++;
	EXPECT_EQ(*it, 5);

	it++;
	EXPECT_EQ(*it, 6);

	it++;
	EXPECT_EQ(it != ilist.end(), false);

	// Testing rbegin
	ilist.clear();
	ilist.append(4);
	ilist.append(5);
	ilist.append(6);
	it = ilist.rbegin();

	EXPECT_EQ(*it, 6);

	it++;
	EXPECT_EQ(*it, 5);

	++it;
	EXPECT_EQ(*it, 4);

	it++;
	EXPECT_EQ(it != ilist.rend(), false);
}

ssuds::LinkedList<int>func()
{
	ssuds::LinkedList<int>temp;
	temp.append(42);
	return temp;
}

TEST(LinkedListTests, Constructors)
{
	ssuds::LinkedList<int> a; // calles defult constructor
	a.append(4);

	ssuds::LinkedList<int> b(a); // calls copy constructor
	std::stringstream ss;
	ss << a;

	EXPECT_NE(ss.str(), "[2]"); // Will fail
	EXPECT_EQ(ss.str(), "[4]");
	ss.str(std::string());

	ssuds::LinkedList<int> c = func(); // calls move constructor
	ss << c;
	EXPECT_EQ(ss.str(), "[42]");
	ss.str(std::string());

	ssuds::LinkedList<int> d = { 1, 2, 3, 4 }; // calls initialize_list constructor
	ss << d;
	EXPECT_EQ(ss.str(), "[1, 2, 3, 4]");
}

TEST(LinkedListTests, ArrayListMethods)
{
	ssuds::LinkedList<float> a;
	a.append(4.0f);
	a.append(8.6f);
	a.append(34.2f);

	EXPECT_EQ(a[0], 4.0);
	a[0] = a[1];
	EXPECT_EQ(a[0], 8.6f); // errored if set to 8.6 and not 8.6f
	a.clear();
	a.append(4.0f);
	EXPECT_EQ(a[0], 4.0f);
	a.prepend(23.5f);
	EXPECT_EQ(a[0], 23.5f);

	a.clear();
	a.append(4.0f);
	a.append(8.6f);
	a.append(34.2f);
	EXPECT_EQ(a.size(), 3);
	a.insert(2, 23541351.055f);
	EXPECT_EQ(a[2], 23541351.055f);
	EXPECT_EQ(a.size(), 4);

}

TEST(ArrayListTest, PrintingAnArray)
{
	ssuds::LinkedList<float> test_list;
	test_list.append(4);
	test_list.append(5);

	std::stringstream ss;
	ss << test_list;
	EXPECT_EQ(ss.str(), "[4, 5]");;

}

TEST(ArrayListTests, BracketOperator)
{
	ssuds::LinkedList<int> ilist;
	ilist.append(4);
	ilist.append(5);

	EXPECT_EQ(ilist[0], 4);

	int result = 0;
	try
	{
		ilist[2];
	}
	catch (std::out_of_range)
	{
		result = 1;
	}
	EXPECT_EQ(result, 1);

}


