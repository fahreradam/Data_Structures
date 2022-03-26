#include <linked_list.h>
#include <gtest/gtest.h>

#define EXECUTE_LINKED_LIST_TESTS 2
#if EXECUTE_LINKED_LIST_TESTS == 1

class LinkedListTestFixture : public ::testing::Test
{
protected:
	void SetUp() override
	{
		slist2.append("B");
		slist2.append("C");
		slist2.insert("A", 0);
		slist2.insert("D", 3);
	}

	void TearDown() override
	{

	}


	ssuds::LinkedList<std::string> slist1;
	ssuds::LinkedList<std::string> slist2;
	ssuds::LinkedList<int> ilist;
};

TEST_F(LinkedListTestFixture, InitiallyEmpty)
{
	EXPECT_EQ(slist1.size(), 0);
	EXPECT_EQ(ilist.size(), 0);
}


TEST_F(LinkedListTestFixture, AppendAndBracket)
{
	ASSERT_EQ(slist1.size(), 0);
	slist1.append("A");
	slist1.append("B");
	ASSERT_EQ(slist1.size(), 2);
	EXPECT_EQ(slist1[0], "A");
	EXPECT_EQ(slist1[1], "B");
}


TEST_F(LinkedListTestFixture, Insert)
{
	slist1.append("B");
	slist1.append("D");
	slist1.insert("A", 0);
	slist1.insert("C", 2);
	slist1.insert("E", 4);

	ASSERT_EQ(slist1.size(), 5);
	EXPECT_EQ(slist1[0], "A");
	EXPECT_EQ(slist1[1], "B");
	EXPECT_EQ(slist1[2], "C");
	EXPECT_EQ(slist1[3], "D");
	EXPECT_EQ(slist1[4], "E");
}



TEST_F(LinkedListTestFixture, BracketOperator)
{
	slist1.append("A");
	slist1.append("B");
	EXPECT_EQ(slist1[0], "A");
	EXPECT_EQ(slist1[1], "B");
	EXPECT_THROW(slist1[-1], std::out_of_range);
	EXPECT_THROW(slist1[2], std::out_of_range);
}


TEST_F(LinkedListTestFixture, EmptyManualIteration)
{
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist1.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist1.end();
	ASSERT_EQ(it, it_end);
}


TEST_F(LinkedListTestFixture, ManualIteration)
{
	slist1.append("A");
	slist1.append("B");
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist1.begin();
	ssuds::LinkedList<std::string>::LinkedListIterator it_end = slist1.end();
	std::string val1, val2, val3, val4;
	ASSERT_NE(it, it_end);
	val1 = *it;
	++it;
	EXPECT_EQ(val1, std::string("A"));
	val2 = *it;
	EXPECT_EQ(val2, std::string("B"));
	++it;
	EXPECT_EQ(it, it_end);
}


TEST_F(LinkedListTestFixture, IteratorOffset)
{
	slist1.append("A");
	slist1.append("B");
	slist1.append("C");
	slist1.append("D");
	slist1.append("E");
	ssuds::LinkedList<std::string>::LinkedListIterator iter = slist1.begin();
	iter = iter + 2;
	EXPECT_EQ(*iter, "C");
	EXPECT_EQ(iter.index(), 2);
	iter = iter + 2;
	EXPECT_EQ(*iter, "E");
	EXPECT_EQ(iter.index(), 4);
}


TEST_F(LinkedListTestFixture, InsertWithIterator)
{
	slist1.append("A");
	slist1.append("B");
	slist1.append("C");
	slist1.append("D");
	slist1.append("E");
	ssuds::LinkedList<std::string>::LinkedListIterator iter = slist1.begin();
	iter = iter + 2;
	slist1.insert("X", iter);

	std::stringstream ss;
	ss << slist1;

	EXPECT_EQ(ss.str(), "[A, B, X, C, D, E]");
}

TEST_F(LinkedListTestFixture, PrettyIteration)
{
	int i = 0;
	for (std::string s : slist2)
	{
		if (i == 0)
			EXPECT_EQ(s, "A");
		else if (i == 1)
			EXPECT_EQ(s, "B");
		else if (i == 2)
			EXPECT_EQ(s, "C");
		else
			EXPECT_EQ(s, "D");
		i++;
	}
}


TEST_F(LinkedListTestFixture, Remove)
{
	slist1.append("A");
	slist1.append("B");
	slist1.append("C");
	slist1.append("D");
	slist1.append("E");
	ssuds::LinkedList<std::string>::LinkedListIterator it = slist1.begin();
	it = slist1.remove(it);
	EXPECT_EQ(slist1[0], "B");
	EXPECT_EQ(*it, "B");
	it = slist1.begin() + 3;
	it = slist1.remove(it);
	EXPECT_EQ(it, slist1.end());
}


TEST_F(LinkedListTestFixture, OS_Stream)
{
	std::stringstream ss;
	ss << slist1;
	EXPECT_EQ(ss.str(), "[]");
	ss.str(std::string());
	ss << slist2;
	EXPECT_EQ(ss.str(), "[A, B, C, D]");
}


TEST_F(LinkedListTestFixture, CopyConstructor)
{
	ssuds::LinkedList<std::string> slist_copy1 = slist2;
	ssuds::LinkedList<std::string> slist_copy2(slist2);
	ASSERT_EQ(slist_copy1.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	slist2.remove(slist2.begin());
	EXPECT_EQ(slist_copy1.size(), 4);

	// Same thing, really, but just to make sure...
	ASSERT_EQ(slist_copy2.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	EXPECT_EQ(slist_copy2.size(), 4);
}


TEST_F(LinkedListTestFixture, Assignment)
{
	ssuds::LinkedList<std::string> slist3;
	slist3.append("X");
	ASSERT_EQ(slist3.size(), 1);
	ASSERT_EQ(slist3[0], "X");
	slist3 = slist2;
	ASSERT_EQ(slist3.size(), 4);
	EXPECT_EQ(slist3[0], "A");
	EXPECT_EQ(slist3[1], "B");
	EXPECT_EQ(slist3[2], "C");
	EXPECT_EQ(slist3[3], "D");
	slist2.remove(slist2.begin());
	EXPECT_EQ(slist3.size(), 4);
}


TEST_F(LinkedListTestFixture, InitializerListConstructor)
{
	ssuds::LinkedList<int> test{ 5, 8, 9, 3, 1, 2, 7, 0 };
	ASSERT_EQ(test.size(), 8);
	EXPECT_EQ(test[0], 5);
	EXPECT_EQ(test[1], 8);
	EXPECT_EQ(test[2], 9);
	EXPECT_EQ(test[3], 3);
	EXPECT_EQ(test[4], 1);
	EXPECT_EQ(test[5], 2);
	EXPECT_EQ(test[6], 7);
	EXPECT_EQ(test[7], 0);
}


ssuds::LinkedList<float> move_func()
{
	ssuds::LinkedList<float> result;
	result.append(3.1f);
	result.append(4.2f);
	return result;
}

TEST_F(LinkedListTestFixture, MoveConstructor)
{
	ssuds::LinkedList<float> my_arr = move_func();
	ASSERT_EQ(my_arr.size(), 2);
	EXPECT_EQ(my_arr[0], 3.1f);
	EXPECT_EQ(my_arr[1], 4.2f);
	my_arr.remove(my_arr.begin());
	EXPECT_EQ(my_arr.size(), 1);
}

#endif