#include "gtest/gtest.h"
#include "../../Queue/Queue.cpp"
#include "../../Queue/PriorityQueue.cpp"

TEST(TestQueue, TestPush) {
	Queue<int> q;
	q.push_back(1);
	q.push_back(2);
	q.push_back(3);

	EXPECT_EQ(q.size(), 3);
	EXPECT_EQ(q.front(), 1);
	EXPECT_EQ(q.end(), 3);
}

TEST(TestQueue, TestPop) {
	Queue<int> q;
	for (int i = 1; i <= 5; ++i) {
		q.push_back(i);
	}
	q.pop_front();

	EXPECT_EQ(q.size(), 4);
	EXPECT_EQ(q.front(), 2);
	EXPECT_EQ(q.end(), 5);
}

TEST(TestQueue, TestSize) {
	Queue<int> q;
	EXPECT_EQ(0, q.size());
	for (int i = 1; i <= 5; ++i) {
		q.push_back(i);
	}

	EXPECT_EQ(q.size(), 5);
}

TEST(TestQueue, TestEmpty) {
	Queue<int> q;
	EXPECT_TRUE(q.empty());
	q.push_back(10);
	EXPECT_FALSE(q.empty());
}

TEST(TestPriorityQueue, TestPush) {
	PriorityQueue<int> q;
	q.push_back(10, 1);
	q.push_back(40, 4);
	q.push_back(20, 2);
	q.push_back(30, 3);
	EXPECT_EQ(4, q.size());
	EXPECT_EQ(q.front(), 10);
	EXPECT_EQ(q.end(), 40);
}

TEST(TestPriorityQueue, TestPop) {
	PriorityQueue<int> q;
	q.push_back(10, 1);
	q.push_back(40, 4);
	q.push_back(20, 2);
	q.push_back(30, 3);
	EXPECT_EQ(q.front(), 10);
	EXPECT_EQ(q.end(), 40);
}

TEST(TestPriorityQueue, TestSize) {
	PriorityQueue<int> q;
	EXPECT_EQ(0, q.size());
	for (int i = 1; i < 5; ++i) {
		q.push_back(i * 10, i);
	}
	EXPECT_EQ(q.size(), 4);
}

TEST(TestPriorityQueue, TestEmpty) {
	PriorityQueue<int> q;
	EXPECT_TRUE(q.empty());
	q.push_back(10, 1);
	EXPECT_FALSE(q.empty());
}
