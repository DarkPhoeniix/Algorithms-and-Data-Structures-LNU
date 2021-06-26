
#include "gtest/gtest.h"
#include "../../AVL_Tree/AVL_Tree.h"

TEST(Test_AVL_Tree, TestInsertINT)
{
	AVL_Tree<int> tree;
	std::vector<int> data = { 3, 3, 67, 11, -34, 2, -10, 100, -136 };

	for (int i = 0; i < data.size(); ++i) {
		tree.insert(data[i]);
	}

	for (int i = 0; i < data.size(); ++i) {
		EXPECT_TRUE(tree.find(data[i]));
	}

	EXPECT_FALSE(tree.find(-100));
	EXPECT_FALSE(tree.find(0));
	EXPECT_FALSE(tree.find(5));
}

TEST(Test_AVL_Tree, TestInsertSTRING)
{
	AVL_Tree<std::string> tree;
	std::vector<std::string> data = { "Hello", "world", "C++", "CuteCats^^", "Algorithm" };

	for (int i = 0; i < data.size(); ++i) {
		tree.insert(data[i]);
	}

	for (int i = 0; i < data.size(); ++i) {
		EXPECT_TRUE(tree.find(data[i]));
	}

	EXPECT_FALSE(tree.find("Java"));
	EXPECT_FALSE(tree.find("Goodbye"));
}

TEST(Test_AVL_Tree, TestErase)
{
	AVL_Tree<int> tree;
	std::vector<int> data = { 3, -3, 83, 11, 23, 193, 35, -1200 };

	for (int i = 0; i < data.size(); ++i) {
		tree.insert(data[i]);
	}

	for (int i = 0; i < data.size() / 2; ++i) {
		tree.erase(data[i]);
	}

	for (int i = 0; i < data.size(); ++i) {
		if (i < data.size() / 2) {
			EXPECT_FALSE(tree.find(data[i]));
		}
		else {
			EXPECT_TRUE(tree.find(data[i]));
		}
	}
}

TEST(Test_AVL_Tree, TestTreeToVector)
{
	AVL_Tree<int> tree;
	std::vector<int> data = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	for (int i = 0; i < data.size(); ++i) {
		tree.insert(data[i]);
	}

	std::vector<int> test = tree.treeToVector();
	EXPECT_EQ(test, std::vector<int>({ 1,2,3,4,5,6,7,8,9,10 }));
}
