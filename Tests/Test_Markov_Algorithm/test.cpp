
#include "gtest/gtest.h"
#include "../../Markov_Algorithm/MarkovAlgorithm.cpp"


TEST(TestMarkovAlgorithm, Test1) {
	EXPECT_EQ(String("Hello, C++!"), MarkovAlgorithm("Hello, world!", { make_pair("world", "C++") }));
}

TEST(TestMarkovAlgorithm, Test2) {
	EXPECT_EQ(String("|||||"), MarkovAlgorithm("101", { make_pair("1", "0|"),
												make_pair("|0", "0||"),
												make_pair("0", "") }));
}

TEST(TestMarkovAlgorithm, Test3) {
	EXPECT_EQ(String("||"), MarkovAlgorithm("|*||", { make_pair("|b", "ba|"),
												make_pair("ab", "ba"),
												make_pair("b",  ""),
												make_pair("*|", "b*"),
												make_pair("*",  "c"),
												make_pair("|c", "c"),
												make_pair("ac", "c|"),
												make_pair("c",  "") }));
}

TEST(TestMarkovAlgorithm, Test4) {
	EXPECT_EQ(String("1qw41qw4cbc"), MarkovAlgorithm("abcdabcdcbc", { make_pair("ab", "12"),
																make_pair("cd", "34"),
																make_pair("23", "qw") }));
}

TEST(TestMarkovAlgorithm, Test5) {
	EXPECT_EQ(String("Cats like apples"), MarkovAlgorithm("Cats like apples", { make_pair("sausages", "apples"),
																		make_pair("Dogs", "Cats") }));
}

TEST(TestMarkovAlgorithm, Test6) {
	EXPECT_EQ(String("1tyuio22p"), MarkovAlgorithm("qwertyuiopopop", { make_pair("qwer", "1"),
																make_pair("po", "2"),
																make_pair("1q", "error") }));
}

TEST(TestMarkovAlgorithm, Test7) {
	EXPECT_EQ(String("what?what?what?what?what?what?"), MarkovAlgorithm("qwqwqwqwqwqw", { make_pair("qw", "what?") }));
}

