#include <gtest/gtest.h>
#include <linked_list.h>
#include <fstream>



class LinkedListTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		slist2.append("B");
		slist2.append("C");

	}

	void TearDown() override
	{

	}

	ssuds::LinkedList<std::string> slist2;
	ssuds::LinkedList<int> ilist;
	ssuds::LinkedList<std::string> slist1;
};

TEST_F(LinkedListTestFixture, LinkedListIteratorTests)
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

TEST_F(LinkedListTestFixture, LinkedListIteratorFind)
{
	ssuds::LinkedList<int> ilist{ 1, 5, 7, 13, 18, 22, 25, 30, 22, 38 };
	ssuds::LinkedList<int>::LinkedListIterator it = ilist.find(22);
	std::cout << *it << " " << it.index() << std::endl;      // 22   5
	++it;
	std::cout << *it << " " << it.index() << std::endl;      // 25   6
	it = ilist.find(it);
	std::cout << *it << " " << it.index() << std::endl;      // 22   8
	++it;
	it = ilist.find(it);
	std::cout << (it != ilist.end()) << std::endl;              // false (they are equal)
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
}

TEST(ArrayListTests, Constructors)
{
	ssuds::LinkedList<int> a; // calles defult constructor
	a.append(4);

	ssuds::LinkedList<int> b(a); // calls copy constructor
	std::stringstream ss;
	ss << a;

	EXPECT_NE(ss.str(), "[2]"); // Will fail
	EXPECT_EQ(ss.str(), "[4]");
	ss.str(std::string());

	ssuds::LinkedList<int> d = { 1, 2, 3, 4 }; // calls initialize_list constructor
	ss << d;
	EXPECT_EQ(ss.str(), "[1, 2, 3, 4]");
}

TEST(ArrayListTests, ArrayListMethods)
{
	ssuds::LinkedList<float> a;
	a.append(4.0f);
	a.append(8.6f);
	a.append(34.2f);

	EXPECT_EQ(a[0], 4.0);
	a[0] = a[1];
	EXPECT_EQ(a[0], 8.6f); // errored if set to 8.6 and not 8.6f
}