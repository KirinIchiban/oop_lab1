#include <gtest/gtest.h>
#include "solve.hpp"

TEST(GrowSuccessTest, AchievableLevel) {
    EXPECT_EQ(find_target_height(100, 10, 910), 10);
    EXPECT_EQ(find_target_height(5, 4, 5), 1);
    EXPECT_EQ(find_target_height(3, 2, 10), 8);
}

TEST(GrowSuccessTest, EqualUpDown) {
    EXPECT_EXIT(find_target_height(100, 100, 200), testing::ExitedWithCode(1), "Error: impossible to solve input data");
    EXPECT_EQ(find_target_height(20, 20, 10), 1); 
    EXPECT_EQ(find_target_height(20, 20, 20), 1); 
}

TEST(GrowSuccessTest, UnevenDivision) { 
    EXPECT_EQ(find_target_height(4, 1, 50), 17); 
    EXPECT_EQ(find_target_height(10, 5, 24), 4);
    EXPECT_EQ(find_target_height(7, 3, 30), 7);
}

TEST(GrowSuccessTest, NegativeParams) {
    EXPECT_EXIT(find_target_height(-100, 10, 910), testing::ExitedWithCode(1), "Error: negative input data");
    EXPECT_EXIT(find_target_height(100, -10, 910), testing::ExitedWithCode(1), "Error: negative input data");
    EXPECT_EXIT(find_target_height(100, 10, -910), testing::ExitedWithCode(1), "Error: negative input data"); 
}

TEST(GrowSuccessTest, ZeroParams) {
    EXPECT_EXIT(find_target_height(100, 10, 0), testing::ExitedWithCode(1), "Error: zero input data");
    EXPECT_EQ(find_target_height(3, 0, 20), 7);
    EXPECT_EXIT(find_target_height(0, 10, 10), testing::ExitedWithCode(1), "Error: zero input data");
    EXPECT_EXIT(find_target_height(0, 0, 200), testing::ExitedWithCode(1), "Error: zero input data"); 
}

TEST(GrowSuccessTest, DownMoreUp) {
    EXPECT_EXIT(find_target_height(20, 100, 50), testing::ExitedWithCode(1), "Error: impossible to solve input data");
    EXPECT_EXIT(find_target_height(10, 100, 910), testing::ExitedWithCode(1), "Error: impossible to solve input data");
    EXPECT_EQ(find_target_height(50, 100, 50), 1);
}

TEST(GrowSuccessTest, HighValues) {
    EXPECT_EQ(find_target_height(100'000, 99'999, 1'000'000'000), 999900001);
    int up = 1000000;
    int down = 999999;
    int target = std::numeric_limits<int>::max() - 10;
    EXPECT_EQ(find_target_height(up, down, target), target - down);
}