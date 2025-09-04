#include "gtest/gtest.h"
#include "solution.hpp"
using namespace std;

TEST(Part1_Example_Test, BasicAssertions) {
  std::string filename = "../src/example_input.txt";
  // Expect you get the right answer
  EXPECT_EQ(part1(filename), 24000);
}

TEST(Part1_Actual_Test, BasicAssertions) {
  std::string filename = "../src/input.txt";
  // Expect you get the right answer
  EXPECT_EQ(part1(filename), 66719);
}

TEST(Part2_Example_Test, BasicAssertions) {
  std::string filename = "../src/example_input.txt";
  int top_n = 3;
  // Expect you get the right answer
  EXPECT_EQ(part2(filename, top_n), 45000);
}

TEST(Part2_Actual_Test, BasicAssertions) {
  std::string filename = "../src/input.txt";
  int top_n = 3;
  // Expect you get the right answer
  EXPECT_EQ(part2(filename, top_n), 198551);
}
