#include "gtest/gtest.h"
#include <stack>
#include "../../Stack/Stack.cpp"

TEST(TestStack, TestPush) 
{
	Stack st;

	st.push(1);
	EXPECT_EQ(1, st.top());
	st.push(5);
	EXPECT_EQ(5, st.top());
	st.push(10);
	EXPECT_EQ(10, st.top());
}

TEST(TestStack, TestPop)
{
	Stack st;

	st.push(1);
	st.push(5);
	st.push(10);

	st.pop();
	EXPECT_EQ(5, st.top());
	st.pop();
	EXPECT_EQ(1, st.top());
}

TEST(TestStack, TestSize)
{
	Stack st;

	EXPECT_EQ(0, st.getSize());
	st.push(1);
	st.push(1);
	st.push(1);
	EXPECT_EQ(3, st.getSize());
}

TEST(TestStack, TestEmpty)
{
	Stack st;
	EXPECT_TRUE(st.empty());
	st.push(1);
	EXPECT_FALSE(st.empty());
}



TEST(TestStackSTL, TestPush)
{
	std::stack<int> st;

	st.push(4);
	EXPECT_EQ(4, st.top());

	st.push(9);
	EXPECT_EQ(9, st.top());

	st.push(14);
	EXPECT_EQ(14, st.top());
}

TEST(TestStackSTL, TestPop)
{
	std::stack<int> st;

	for (int i = 0; i < 4; ++i) {
		st.push(i + 1);
	}

	for (int i = 0; i < 3; ++i) {
		st.pop();
		EXPECT_EQ(3 - i, st.top());
	}
}

TEST(TestStackSTL, TestSize)
{
	std::stack<int> st;

	EXPECT_EQ(0, st.size());

	st.push(1);
	st.push(2);
	st.push(3);

	EXPECT_EQ(3, st.size());
}

TEST(TestStackSTL, TestEmpty)
{
	std::stack<int> st;

	EXPECT_TRUE(st.empty());
	st.push(3);
	EXPECT_FALSE(st.empty());
}

TEST(TestStackSTL, TestSwap)
{
	std::stack<int> lhs;
	std::stack<int> rhs;

	for (int i = 0; i < 5; ++i) {
		lhs.push(i + 1);
		rhs.push(5 - i);
	}

	lhs.swap(rhs);

	// 1 2 3 4 5
	// 5 4 3 2 1

	for (int i = 0; i < 5; ++i) {
		EXPECT_EQ(i + 1, lhs.top());
		EXPECT_EQ(5-i, rhs.top());
		lhs.pop();
		rhs.pop();
	}
}

TEST(TestStackSTL, TestEmplace)
{
	std::stack<int> st;

	st.emplace(1);
	EXPECT_EQ(1, st.top());
	st.emplace(2);
	EXPECT_EQ(2, st.top());
	st.emplace(3);
	EXPECT_EQ(3, st.top());
}
