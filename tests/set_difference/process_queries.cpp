#include "set_difference/process_queries.hpp"

#include <gtest/gtest.h>

#include "set_difference/generate_queries.hpp"

std::vector<std::pair<std::vector<int>, std::vector<int>>> queries_expected = {
    {generate_random_queries(5, 2, 10, 0), {0, 4, 9}},
    {generate_random_queries(5, 3, 10, 0), {4, 9}},
    {generate_random_queries(5, 2, 100, 0), {39, 44, 60}},
    {generate_random_queries(5, 2, 10, 1), {3, 4, 5}}};

TEST(ProcessQueriesTest, Sort) {
  for (const auto& [queries, expected] : queries_expected) {
    const auto actual = process_queries_sort(queries);
    EXPECT_EQ(actual, expected);
  }
}

TEST(ProcessQueriesTest, Multiset) {
  for (const auto& [queries, expected] : queries_expected) {
    const auto actual = process_queries_multiset(queries);
    EXPECT_EQ(actual, expected);
  }
}

TEST(ProcessQueriesTest, LazyPQ) {
  for (const auto& [queries, expected] : queries_expected) {
    const auto actual = process_queries_lazypq(queries);
    EXPECT_EQ(actual, expected);
  }
}