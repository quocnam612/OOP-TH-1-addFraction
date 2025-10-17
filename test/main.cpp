#include "../src/usecase.h"
#include <gtest/gtest.h>
#include <sstream>
using std::istringstream, std::ostringstream;

bool executeGetInput(auto num1, auto denom1, auto num2, auto denom2) {
    istringstream input(format("{}/{}\n{}/{}\n",
        num1, denom1,
        num2, denom2
    ));
    ostringstream output;

    auto* cinBuf = cin.rdbuf();
    cin.rdbuf(input.rdbuf());
    cout.rdbuf(nullptr);

    auto result = executeGetInputUseCase();
    cin.rdbuf(cinBuf);
    
    return result.has_value() && result.value() == make_tuple(Fraction(num1, denom1), Fraction(num2, denom2));
}

bool executePrintAddFractions(Fraction a, Fraction b, Fraction expected, string expectedOutput) {
    ostringstream output;
    auto* coutBuf = cout.rdbuf();
    cout.rdbuf(output.rdbuf());
    Fraction result = executePrintAddFractionsUseCase(a, b);
    cout.rdbuf(coutBuf);

    return (result == expected && output.str().find(": " + expectedOutput) != string::npos);
}

bool executeSimplifyFraction(Fraction f, Fraction expected) {
    cout.rdbuf(nullptr);
    return (executeSimplifyFractionUseCase(f) == expected);
}

// Test cases for input use case
TEST(GetInput, ValidInput1) {
    bool found = executeGetInput(1, 2, 3, 4);
    EXPECT_EQ(found, true);
}

TEST(GetInput, ValidInput2) {
    bool found = executeGetInput(-5, 6, 7, -8);
    EXPECT_EQ(found, true);
}

TEST(GetInput, InvalidInput1) {
    bool found = executeGetInput(1, 0, 3, 4);
    EXPECT_EQ(found, false);
}

TEST(GetInput, InvalidInput2) {
    bool found = executeGetInput('a', 'b', 'c', 'd');
    EXPECT_EQ(found, false);
}

TEST(GetInput, InvalidInput3) {
    bool found = executeGetInput(1, 2, '-', 3);
    EXPECT_EQ(found, false);
}

// Test cases for add fractions and output use case
TEST(AddFractions, ValidSum1) {
    bool found = executePrintAddFractions(Fraction(1, 2), Fraction(1, 3), Fraction(5, 6), "5/6");
    EXPECT_EQ(found, true);
}

TEST(AddFractions, ValidSum2) {
    bool found = executePrintAddFractions(Fraction(-5, -2), Fraction(1, -3), Fraction(13, 6), "13/6");
    EXPECT_EQ(found, true);
}

TEST(AddFractions, ValidSum3) {
    bool found = executePrintAddFractions(Fraction(100, 20), Fraction(-20, 10), Fraction(3, 1), "3");
    EXPECT_EQ(found, true);
}

// Test cases for simplify fraction use case
TEST(SimplifyFraction, ValidSimplify1) {
    bool found = executeSimplifyFraction(Fraction(2, 4), Fraction(1, 2));
    EXPECT_EQ(found, true);
}

TEST(SimplifyFraction, ValidSimplify2) {
    bool found = executeSimplifyFraction(Fraction(-10, 15), Fraction(-2, 3));
    EXPECT_EQ(found, true);
}

TEST(SimplifyFraction, ValidSimplify3) {
    bool found = executeSimplifyFraction(Fraction(-100, -250), Fraction(2, 5));
    EXPECT_EQ(found, true);
}

int main(int argc, char **argv) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}