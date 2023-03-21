#include "set_difference/generate_queries.hpp"

#include <gtest/gtest.h>

TEST(GenerateRandomQueriesTest, NumInsertions) {
  {  // num_insertions = 4
    const std::vector<int> expected{5, 0, 3, 3, -4, -4};
    const auto actual = generate_random_queries(4, 2, 9, 0);
    EXPECT_EQ(actual, expected);
  }

  {  // num_insertions = 5
    const std::vector<int> expected{5, 0, 3, 3, 7, -1, -8};
    const auto actual = generate_random_queries(5, 2, 9, 0);
    EXPECT_EQ(actual, expected);
  }

  {  // num_insertions = 6
    const std::vector<int> expected{5, 0, 3, 3, 7, 9, -4, -6};
    const auto actual = generate_random_queries(6, 2, 9, 0);
    EXPECT_EQ(actual, expected);
  }
}

TEST(GenerateRandomQueriesTest, NumRemovals) {
  {  // num_removals = 2
    const std::vector<int> expected{5, 0, 3, 3, 7, -1, -8};
    const auto actual = generate_random_queries(5, 2, 9, 0);
    EXPECT_EQ(actual, expected);
  }

  {  // num_removals = 3
    const std::vector<int> expected{5, 0, 3, 3, 7, -1, -8, -4};
    const auto actual = generate_random_queries(5, 3, 9, 0);
    EXPECT_EQ(actual, expected);
  }

  {  // num_removals = 4
    const std::vector<int> expected{5, 0, 3, 3, 7, -1, -8, -4, -4};
    const auto actual = generate_random_queries(5, 4, 9, 0);
    EXPECT_EQ(actual, expected);
  }
}

TEST(GenerateRandomQueriesTest, MaxValues) {
  {  // max_value == 9
    const std::vector<int> expected{5, 0, 3, 3, 7, -1, -8};
    const auto actual = generate_random_queries(5, 2, 9, 0);
    EXPECT_EQ(actual, expected);
  }

  {  // max_value == 99
    const std::vector<int> expected{44, 47, 64, 67, 67, -48, -68};
    const auto actual = generate_random_queries(5, 2, 99, 0);
    EXPECT_EQ(actual, expected);
  }

  {  // max_value == 999
    const std::vector<int> expected{684, 559, 629, 192, 835, -193, -836};
    const auto actual = generate_random_queries(5, 2, 999, 0);
    EXPECT_EQ(actual, expected);
  }
}

TEST(GenerateRandomQueriesTest, Seeds) {
  {  // seed == 0
    const std::vector<int> expected{5, 0, 3, 3, 7, -1, -8};
    const auto actual = generate_random_queries(5, 2, 9, 0);
    EXPECT_EQ(actual, expected);
  }

  {  // seed == 1
    const std::vector<int> expected{5, 8, 9, 5, 0, -6, -10};
    const auto actual = generate_random_queries(5, 2, 9, 1);
    EXPECT_EQ(actual, expected);
  }

  {  // seed == 2
    const std::vector<int> expected{8, 8, 6, 2, 8, -7, -9};
    const auto actual = generate_random_queries(5, 2, 9, 2);
    EXPECT_EQ(actual, expected);
  }
}