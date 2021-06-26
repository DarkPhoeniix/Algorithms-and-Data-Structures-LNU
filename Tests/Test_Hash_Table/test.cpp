
#include "gtest/gtest.h"
#include "../../Hash_Table/HashTable.cpp"

TEST(TestHashTable, TestInsert1) {
	HashTable<int, std::string> t;

	t.insert(5, "hello");
	t.insert(105, "world");

	EXPECT_EQ("hello", t[5]);
}

TEST(TestHashTable, TestInsert2) {
	HashTable<int, std::string> t;

	t.insert(5, "hello");
	t.insert(105, "world");

	EXPECT_EQ("world", t[105]);
}

TEST(TestHashTable, TestInsert3) {
	HashTable<int, std::string> t;

	t.insert(5, "hello");
	t.insert(105, "world");
	t.insert(1005, "C++");

	EXPECT_EQ("C++", t[1005]);
}

TEST(TestHashTable, TestErase1) {
	HashTable<int, std::string> t;

	try {
		t.insert(5, "hello");
		t.insert(105, "world");
		t.erase(5);
	}
	catch (exception& ex) {
		EXPECT_EQ("There is no data with such key", string(ex.what()));
	}
}

TEST(TestHashTable, TestErase2) {
	HashTable<int, std::string> t;

	try {
		t.insert(5, "hello");
		t.insert(105, "world");
		t.erase(55);
	}
	catch (exception& ex) {
		EXPECT_EQ("This key doesn't exist in table", string(ex.what()));
	}
}

TEST(TestHashTable, TestMaxSize) {
	HashTable<int, std::string> t;
	EXPECT_EQ(t.maxSize(), 100);
}

TEST(TestHashTable, TestClearAndEmpty) {
	HashTable<int, char> t;
	for (int i = 0; i < t.maxSize(); ++i) {
		t.insert(i, char(i % 26 + 65));
	}
	t.clear();
	EXPECT_TRUE(t.empty());
}
