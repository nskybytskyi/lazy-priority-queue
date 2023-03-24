#include <algorithm>
#include <iterator>
#include <set>
#include <vector>

#include "lib.hpp"

std::vector<int> process_queries_sort(std::vector<int> queries) {
  auto pivot_it = std::find_if(queries.begin(), queries.end(),
                               [](auto&& query) { return query < 0; });
  std::sort(queries.begin(), pivot_it);
  std::transform(pivot_it, queries.end(), pivot_it,
                 [](auto&& query) { return ~query; });
  std::sort(pivot_it, queries.end());

  std::vector<int> answer;
  answer.reserve(std::distance(queries.begin(), pivot_it) -
                 std::distance(pivot_it, queries.end()));
  std::set_difference(queries.begin(), pivot_it, pivot_it, queries.end(),
                      std::back_inserter(answer));
  return answer;
}

std::vector<int> process_queries_multiset(const std::vector<int>& queries) {
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

std::vector<int> process_queries_lazypq(const std::vector<int>& queries) {
  lazy_priority_queue<int> container;
  for (const auto& query : queries) {
    if (query >= 0) {
      container.push(query);
    } else {
      container.erase(~query);
    }
  }

  std::vector<int> answer;
  answer.reserve(container.size());
  while (!container.empty()) {
    answer.push_back(container.top());
    container.pop();
  }
  return {answer.crbegin(), answer.crend()};
}