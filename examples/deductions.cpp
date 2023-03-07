#include <functional>
#include <iostream>
#include <vector>

#include "lib.hpp"

int main() {
  const std::vector<int> v = {1, 2, 3, 4};

  lazy_priority_queue pq1{std::greater<int>{},
                          v};  // deduces lazy_priority_queue<int,
                               // std::vector<int>, std::greater<int>>
  for (; !pq1.empty(); pq1.pop()) std::cout << pq1.top() << ' ';
  std::cout << '\n';

  lazy_priority_queue pq2{v.begin(),
                          v.end()};  // deduces lazy_priority_queue<int>

  for (; !pq2.empty(); pq2.pop()) std::cout << pq2.top() << ' ';
  std::cout << '\n';

  return 0;
}