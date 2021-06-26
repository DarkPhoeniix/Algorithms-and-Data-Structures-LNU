
#include "gtest/gtest.h"
#include "../../Expression_Calculation/ExpressionCalculation.cpp"



TEST(TestCalculation, Test1) {
	EXPECT_EQ(4, calculate(makeReverseNotation("2+2")));
}

TEST(TestCalculation, Test2) {
	EXPECT_EQ(7, calculate(makeReverseNotation("9-2")));
}

TEST(TestCalculation, Test3) {
	EXPECT_EQ(6, calculate(makeReverseNotation("3*2")));
}

TEST(TestCalculation, Test4) {
	EXPECT_EQ(6, calculate(makeReverseNotation("6/1")));
}

TEST(TestCalculation, Test5) {
	EXPECT_EQ(27, calculate(makeReverseNotation("3^3")));
}

TEST(TestCalculation, Test6) {
	EXPECT_EQ(16, calculate(makeReverseNotation("(2+2)*(2^2)")));
}

TEST(TestCalculation, Test7) {
	EXPECT_EQ(2, calculate(makeReverseNotation("(1+3+4+2)/5")));
}

TEST(TestCalculation, Test8) {
	EXPECT_EQ(17, calculate(makeReverseNotation("2/1+3*5")));
}

TEST(TestCalculation, Test9) {
	EXPECT_EQ(-4, calculate(makeReverseNotation("2-2-2-2")));
}

TEST(TestCalculation, Test10) {
	EXPECT_EQ(-20, calculate(makeReverseNotation("1^7+4-2*5^2/2")));
}

TEST(TestCalculation, Test11) {
	EXPECT_EQ(0, calculate(makeReverseNotation("-2+2")));
}

TEST(TestCalculation, Test12) {
	EXPECT_EQ(-10, calculate(makeReverseNotation("6*(-2)+2")));
}