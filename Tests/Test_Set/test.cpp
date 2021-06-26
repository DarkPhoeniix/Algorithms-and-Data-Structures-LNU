
#include "gtest/gtest.h"
#include "../../Set/Set.cpp"

TEST(TestSet, TestAdd) 
{
	Set set;
	set.add('a');
	set.add('f');
	set.add('q');

	EXPECT_TRUE(set.isInSet('a'));
	EXPECT_TRUE(set.isInSet('f'));
	EXPECT_TRUE(set.isInSet('q'));
	EXPECT_FALSE(set.isInSet('w'));
	EXPECT_FALSE(set.isInSet('b'));
}

TEST(TestSet, TestRemove) 
{
	Set set;
	set.add('a');
	set.add('f');
	set.add('q');
	set.add('z');
	set.remove('q');
	set.remove('a');
	set.remove('b');

	EXPECT_FALSE(set.isInSet('a'));
	EXPECT_TRUE(set.isInSet('f'));
	EXPECT_FALSE(set.isInSet('q'));
	EXPECT_FALSE(set.isInSet('w'));
	EXPECT_FALSE(set.isInSet('b'));
	EXPECT_TRUE(set.isInSet('z'));
}

TEST(TestSet, TestEmpty)
{
	Set set;
	EXPECT_TRUE(set.empty());
	set.add('a');
	EXPECT_FALSE(set.empty());
}

TEST(TestSet, TestCombination)
{
	Set set1;
	Set set2;

	set1.add('a');
	set1.add('b');
	set1.add('c');
	set2.add('c');
	set2.add('b');
	set2.add('e');

	Set set3 = combination(set1, set2);
	EXPECT_TRUE(set3.isInSet('a'));
	EXPECT_TRUE(set3.isInSet('b'));
	EXPECT_TRUE(set3.isInSet('c'));
	EXPECT_FALSE(set3.isInSet('d'));
	EXPECT_TRUE(set3.isInSet('e'));
	EXPECT_FALSE(set3.isInSet('f'));
}

TEST(TestSet, TestIntersection)
{
	Set set1;
	Set set2;

	set1.add('a');
	set1.add('b');
	set1.add('c');
	set2.add('c');
	set2.add('b');
	set2.add('e');

	Set set3 = intersection(set1, set2);
	EXPECT_FALSE(set3.isInSet('a'));
	EXPECT_TRUE(set3.isInSet('b'));
	EXPECT_TRUE(set3.isInSet('c'));
	EXPECT_FALSE(set3.isInSet('d'));
	EXPECT_FALSE(set3.isInSet('e'));
	EXPECT_FALSE(set3.isInSet('f'));
}

TEST(TestSet, TestDifference)
{
	Set set1;
	Set set2;

	set1.add('a');
	set1.add('b');
	set1.add('c');
	set2.add('c');
	set2.add('b');
	set2.add('e');

	Set set3 = difference(set1, set2);
	EXPECT_TRUE(set3.isInSet('a'));
	EXPECT_FALSE(set3.isInSet('b'));
	EXPECT_FALSE(set3.isInSet('c'));
	EXPECT_FALSE(set3.isInSet('d'));
	EXPECT_FALSE(set3.isInSet('e'));
	EXPECT_FALSE(set3.isInSet('f'));
}
