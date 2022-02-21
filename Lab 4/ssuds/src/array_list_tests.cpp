#include <gtest/gtest.h>
#include <array_list.h>
#include <array_list_utilities.h>

#define EXECUTE_ARRAY_LIST_TESTS 1
#if EXECUTE_ARRAY_LIST_TESTS

class ArrayListTestFixture : public ::testing::Test
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


	ssuds::ArrayList<std::string> slist1;
	ssuds::ArrayList<std::string> slist2;
	ssuds::ArrayList<int> ilist;
};

TEST_F(ArrayListTestFixture, InitiallyEmpty)
{
	EXPECT_EQ(slist1.size(), 0);
	EXPECT_EQ(ilist.size(), 0);
}


TEST_F(ArrayListTestFixture, AddingItems)
{
	ASSERT_EQ(slist2.size(), 4);
	EXPECT_EQ(slist2[0], "A");
	EXPECT_EQ(slist2[1], "B");
	EXPECT_EQ(slist2[2], "C");
	EXPECT_EQ(slist2[3], "D");
}


TEST_F(ArrayListTestFixture, EmptyManualIteration)
{
	ssuds::ArrayList<std::string>::ArrayListIterator it = slist1.begin();
	ssuds::ArrayList<std::string>::ArrayListIterator it_end = slist1.end();
	ASSERT_EQ(it, it_end);
}


TEST_F(ArrayListTestFixture, ManualIteration)
{
	ssuds::ArrayList<std::string>::ArrayListIterator it = slist2.begin();
	ssuds::ArrayList<std::string>::ArrayListIterator it_end = slist2.end();
	std::string val1, val2, val3, val4;
	ASSERT_NE(it, it_end);
	val1 = *it;
	++it;
	EXPECT_EQ(val1, "A");
	val2 = *it;
	++it;
	val3 = *it;
	++it;
	val4 = *it;
	++it;
	EXPECT_EQ(val2, "B");
	EXPECT_EQ(val3, "C");
	EXPECT_EQ(val4, "D");
	EXPECT_EQ(it, it_end);
}

TEST_F(ArrayListTestFixture, PrettyIteration)
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


TEST_F(ArrayListTestFixture, OS_Stream)
{
	std::stringstream ss;
	ss << slist1;
	EXPECT_EQ(ss.str(), "[]");
	ss.str(std::string());
	ss << slist2;
	EXPECT_EQ(ss.str(), "[A, B, C, D]");
}


TEST_F(ArrayListTestFixture, CopyConstructor)
{
	ssuds::ArrayList<std::string> slist_copy1 = slist2;
	ssuds::ArrayList<std::string> slist_copy2(slist2);
	ASSERT_EQ(slist_copy1.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	slist2.remove(0);
	EXPECT_EQ(slist_copy1.size(), 4);

	// Same thing, really, but just to make sure...
	ASSERT_EQ(slist_copy2.size(), 4);
	EXPECT_EQ(slist_copy2[0], "A");
	EXPECT_EQ(slist_copy2[1], "B");
	EXPECT_EQ(slist_copy2[2], "C");
	EXPECT_EQ(slist_copy2[3], "D");
	EXPECT_EQ(slist_copy2.size(), 4);
}


TEST_F(ArrayListTestFixture, Assignment)
{
	ssuds::ArrayList<std::string> slist3;
	slist3.append("X");
	ASSERT_EQ(slist3.size(), 1);
	ASSERT_EQ(slist3[0], "X");
	slist3 = slist2;
	ASSERT_EQ(slist3.size(), 4);
	EXPECT_EQ(slist3[0], "A");
	EXPECT_EQ(slist3[1], "B");
	EXPECT_EQ(slist3[2], "C");
	EXPECT_EQ(slist3[3], "D");
	slist2.remove(0);
	EXPECT_EQ(slist3.size(), 4);
}


TEST_F(ArrayListTestFixture, InitializerListConstructor)
{
	ssuds::ArrayList<int> test{ 5, 8, 9, 3, 1, 2, 7, 0 };
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


ssuds::ArrayList<float> move_func()
{
	ssuds::ArrayList<float> result;
	result.append(3.1f);
	result.append(4.2f);
	return result;
}

TEST_F(ArrayListTestFixture, MoveConstructor)
{
	ssuds::ArrayList<float> my_arr = move_func();
	ASSERT_EQ(my_arr.size(), 2);
	EXPECT_EQ(my_arr[0], 3.1f);
	EXPECT_EQ(my_arr[1], 4.2f);
	my_arr.remove(0);
	EXPECT_EQ(my_arr.size(), 1);
}

TEST_F(ArrayListTestFixture, Utilities)
{
	ssuds::ArrayList<float> flist = { 3.1f, 2.2f, 5.5f, 1.3f, -0.1f, 9.9f, 4.2f };

	ssuds::bubble_sort(flist, ssuds::SortType::ASCENDING);
	std::stringstream ss;
	ss << flist;
	EXPECT_EQ(ss.str(), "[-0.1, 1.3, 2.2, 3.1, 4.2, 5.5, 9.9]");
	int pos = ssuds::binary_search(flist, 5.5f);
	EXPECT_EQ(pos, 5);

	ssuds::ArrayList<std::string> flist1 = { "a", "b", "f", "w", "y", "y", "t"};

	ssuds::bubble_sort(flist1, ssuds::SortType::ASCENDING);
	std::stringstream ss1;
	ss1 << flist1;
	EXPECT_EQ(ss1.str(), "[a, b, f, t, w, y, y]");


	ssuds::ArrayList<float> flist2 = { 3.1f, 2.2f, 5.5f, 1.3f, -0.1f, 9.9f, 4.2f };

	ssuds::qsort(flist2);
	std::stringstream ss2;
	ss2 << flist2;
	EXPECT_EQ(ss2.str(), "[-0.1, 1.3, 2.2, 3.1, 4.2, 5.5, 9.9]");
	pos = ssuds::binary_search(flist2, 5.5f);
	EXPECT_EQ(pos, 5);

	ssuds::ArrayList<std::string> flist3 = { "a", "b", "f", "w", "y", "y", "t" };

	ssuds::qsort(flist3);
	std::stringstream ss3;
	ss3 << flist3;
	EXPECT_EQ(ss3.str(), "[a, b, f, t, w, y, y]");
}



#endif