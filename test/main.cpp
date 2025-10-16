#include "../src/Fraction.h"
#include <gtest/gtest.h>
#include <iostream>
#include <sstream>
#include <format>
using std::istringstream, std::ostringstream;
using std::cin, std::cout;
using std::format;

bool executeAddFractions(Fraction a, Fraction b, Fraction expected) {
    return (Fraction::add(a, b) == expected);
}

// Testcase 1
TEST(add, ValidSum1) {
    bool found = executeAddFractions(Fraction(1, 2), Fraction(1, 3), Fraction(5, 6));
    EXPECT_EQ(found, true);
}

// Testcase 2
TEST(add, ValidSum2) {
    bool found = executeAddFractions(Fraction(-5, -2), Fraction(1, -3), Fraction(13, 6));
    EXPECT_EQ(found, true);
}

// Testcase 3
TEST(add, ValidSum3) {
    bool found = executeAddFractions(Fraction(100, 20), Fraction(14, 37), Fraction(199, 37));
    EXPECT_EQ(found, true);
}

// Testcase 4
TEST(add, ValidSum4) {
    bool found = executeAddFractions(Fraction(11, 32), Fraction(32, 11), Fraction(1145, 352));
    EXPECT_EQ(found, true);
}

// Testcase 5
TEST(add, ValidSum5) {
    bool found = executeAddFractions(Fraction(10, 9), Fraction(8, 7), Fraction(142, 63));
    EXPECT_EQ(found, true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}