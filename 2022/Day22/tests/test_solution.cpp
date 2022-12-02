#include "gtest/gtest.h"
#include "solution.hpp"
using namespace std;

TEST(Part1_Example_Test, BasicAssertions) {
  std::string filename = "../src/example_input.txt";
  // Expect you get the right answer
  EXPECT_EQ(part1(filename), -1);
}

TEST(Part1_Actual_Test, BasicAssertions) {
  std::string filename = "../src/input.txt";
  // Expect you get the right answer
  EXPECT_EQ(part1(filename), -1);
}

TEST(Part2_Example_Test, BasicAssertions) {
  std::string filename = "../src/example_input.txt";
  // Expect you get the right answer
  EXPECT_EQ(part2(filename), -1);
}

TEST(Part2_Actual_Test, BasicAssertions) {
  std::string filename = "../src/input.txt";
  // Expect you get the right answer
  EXPECT_EQ(part2(filename), -1);
}