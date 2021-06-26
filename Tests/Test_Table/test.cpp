#include "gtest/gtest.h"
#include "../../Table/Table.cpp"

TEST(TestTable, TestInsert1) {
	Table<int, std::string> t;
	t.insert(5, "five");
	EXPECT_EQ("five", t[5]);
}

TEST(TestTable, TestInsert2) {
	Table<int, std::string> t;
	t.insert(5, "five");
	t.insert(2, "two");
	t.insert(3, "three");
	t.insert(10, "ten");
	EXPECT_EQ("three", t[3]);
}

TEST(TestTable, TestInsert3) {
	Table<int, std::string> t;
	try {
		t.insert(5, "five");
		t.insert(2, "two");
		t.insert(10, "ten");
		t[-3];
		FAIL();
	}
	catch (exception& ex) {
		EXPECT_EQ("Wrong key", string(ex.what()));
	}
}

TEST(TestTable, TestNotEmpty) {
	Table<int, std::string> t;
	t.insert(5, "five");
	EXPECT_FALSE(t.empty());
}

TEST(TestTable, TestEmpty) {
	Table<int, std::string> t;
	EXPECT_TRUE(t.empty());
}

TEST(TestTable, TestErase1) {
	Table<int, std::string> t;
	try {
		t.insert(5, "five");
		t.insert(2, "two");
		t.insert(-3, "minus three");
		t.insert(10, "ten");
		t.erase(2);
		t[2];
		FAIL();
	}
	catch (exception& ex) {
		EXPECT_EQ("Wrong key", string(ex.what()));
	}
}

TEST(TestTable, TestErase2) {
	Table<int, std::string> t;
	try {
		t.insert(5, "five");
		t.insert(2, "two");
		t.insert(-3, "minus three");
		t.insert(10, "ten");
		t.erase(5);
		t[5];
		FAIL();
	}
	catch (exception& ex) {
		EXPECT_EQ("Wrong key", string(ex.what()));
	}
}

TEST(TestTable, TestErase3) {
	Table<int, std::string> t;
	try {
		t.insert(5, "five");
		t.insert(2, "two");
		t.insert(-3, "minus three");
		t.insert(10, "ten");
		t.erase(10);
		t[10];
		FAIL();
	}
	catch (exception& ex) {
		EXPECT_EQ("Wrong key", string(ex.what()));
	}
}

TEST(TestTable, TestFind1) {
	Table<int, int> t;
	t.insert(1, 10);
	t.insert(5, 50);
	t.insert(10, 100);
	EXPECT_TRUE(t.find(5));
}

TEST(TestTable, TestFind2) {
	Table<int, int> t;
	t.insert(1, 10);
	t.insert(5, 50);
	t.insert(10, 100);
	EXPECT_FALSE(t.find(7));
}

TEST(TestTable, TestSize1) {
	Table<int, int> t;
	for (int i = 0; i < 10; ++i) {
		t.insert(i, i * 10);
	}
	t.erase(2);
	t.erase(7);
	EXPECT_EQ(t.size(), 8);
}

TEST(TestTable, TestSize2) {
	Table<int, int> t;
	EXPECT_EQ(t.size(), 0);
}

TEST(TestTable, TestClear) {
	Table<int, bool> t;
	for (int i = 0; i < 5; i++) {
		t.insert(i, 0);
	}
	t.clear();
	EXPECT_TRUE(t.empty());
}

TEST(TestTable, TestOperator1) {
	Table<int, string> t;
	t.insert(5, "five");
	t.insert(10, "ten");
	t.insert(0, "zero");
	EXPECT_EQ("ten", t[10]);
}

TEST(TestTable, TestOperator2) {
	Table<int, string> t;
	t.insert(5, "five");
	t.insert(10, "ten");
	t.insert(0, "zero");
	t.insert(-10, "minus ten");
	EXPECT_EQ("minus ten", t[-10]);
}
