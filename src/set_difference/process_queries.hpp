/**
 * @file
 * @brief Defines three algorithms capable of processing set difference queries.
 */

#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

#include "lib.hpp"

/// @brief Processes set difference queries using sorting and
/// std::set_difference. This is an
/// [offline](https://en.wikipedia.org/wiki/Online_algorithm) algorithm.
/// @param queries a list of queries where nonnegative values represent
/// insertions and negative ones represent removals, with ~x removing a
/// previously inserted value of x
/// @return (multi)set difference of all inserted
[[nodiscard]] std::vector<int> process_queries_sort(std::vector<int> queries) {
  auto pivot_it = std::find_if(queries.begin(), queries.end(),
                               [](auto&& query) { return query < 0; });
  std::sort(queries.begin(), pivot_it);
  std::transform(pivot_it, queries.end(), pivot_it,
                 [](auto&& query) { return ~query; });
  std::sort(pivot_it, queries.end());

  std::vector<int> answer;
  const auto num_insertions = std::distance(queries.begin(), pivot_it);
  const auto num_removals = std::distance(pivot_it, queries.end());
  answer.reserve(num_insertions - num_removals);

  std::set_difference(queries.begin(), pivot_it, pivot_it, queries.end(),
                      std::back_inserter(answer));
  return answer;
}

/// @brief Processes set difference queries using std::multiset. This is an
/// [online](https://en.wikipedia.org/wiki/Online_algorithm) algorithm.
/// @param queries a list of queries where nonnegative values represent
/// insertions and negative ones represent removals, with ~x removing a
/// previously inserted value of x
/// @return (multi)set difference of all inserted values and all removed values
[[nodiscard]] std::vector<int> process_queries_multiset(
    const std::vector<int>& queries) {
  std::multiset<int> container;
  for (const auto& query : queries) {
    if (query >= 0) {
      container.insert(query);
    } else {
      container.erase(container.find(~query));
    }
  }
  return {container.cbegin(), container.cend()};
}

/// @brief Processes set difference queries using a lazy priority queue. This is
/// an [offline](https://en.wikipedia.org/wiki/Online_algorithm) algorithm.
/// @param queries a list of queries where nonnegative values represent
/// insertions and negative ones represent removals, with ~x removing a
/// previously inserted value of x
/// @return (multi)set difference of all inserted values and all removed values
[[nodiscard]] std::vector<int> process_queries_lazypq(
    const std::vector<int>& queries) {
  lazy_priority_queue<int> container;
  for (const auto& query : queries) {
    if (query >= 0) {
      container.push(query);
    } else {
      container.erase(~query);
    }
  }

  std::vector<int> answer;
  answer.reserve(static_cast<size_t>(container.size()));
  while (!container.empty()) {
    answer.push_back(container.top());
    container.pop();
  }
  return {answer.crbegin(), answer.crend()};
}