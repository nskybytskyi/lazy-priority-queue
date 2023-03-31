/**
 * @file
 * @brief Defines a utility function to generate random set difference queries.
 */

#include <algorithm>
#include <cassert>
#include <iterator>
#include <random>
#include <vector>

/// @brief Generates insertion and removal queries.
/// @param num_insertions the number of insertion queries to generate
/// @param num_removals the number of removal queries to generate
/// @param max_value an upper bound on the values appearing in queries
/// @param seed a seed to use for random number generation
/// @return a list of random queries where nonnegative values represent
/// insertions and negative ones represent removals, with ~x removing a
/// previously inserted value of x
[[nodiscard]] std::vector<int> generate_random_queries(
    unsigned int num_insertions, unsigned int num_removals,
    unsigned int max_value, unsigned int seed) {
  assert(num_removals <= num_insertions && num_insertions <= 100'000'000);
  assert(0 < max_value && max_value <= std::numeric_limits<int>::max());

  std::mt19937 gen(seed);

  std::vector<int> insertions(num_insertions);
  // Note: std::uniform_int_distribution is not portable
  std::generate(insertions.begin(), insertions.end(),
                [max_value, &gen]() { return gen() % max_value; });

  std::vector<int> removals = insertions;
  // Note: std::shuffle is not portable either
  for (size_t first = 0; first < num_removals; ++first) {
    const auto second = gen() % num_insertions;
    std::swap(removals[first], removals[second]);
  }

  for (size_t first = 0; first < num_removals; ++first) {
    removals[first] = ~removals[first];
  }

  copy(removals.cbegin(), next(removals.cbegin(), num_removals),
       std::back_inserter(insertions));
  return insertions;
}