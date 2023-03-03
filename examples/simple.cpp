#include <functional>
#include <iostream>
#include <string_view>
#include <vector>

#include "lib.hpp"

template <typename T>
void print(std::string_view name, T const& q) {
  std::cout << name << ": \t";
  for (auto const& n : q) {
    std::cout << n << ' ';
  }
  std::cout << '\n';
}

template <typename Q>
void print_queue(std::string_view name, Q q) {
  // NB: q is passed by value because there is no way to traverse
  // lazy_priority_queue's content without erasing the queue.
  for (std::cout << name << ": \t"; !q.empty(); q.pop()) {
    std::cout << q.top() << ' ';
  }
  std::cout << '\n';
}

int main() {
  const auto insert_data = {1, 8, 5, 6, 3, 4, 0, 9, 7, 2};
  print("insrt", insert_data);
  const auto erase_data = {1, 4, 7};
  print("erase", erase_data);

  lazy_priority_queue<int> q1;  // Max lazy priority queue
  for (int n : insert_data) {
    q1.push(n);
  }
  for (int n : erase_data) {
    q1.erase(n);
  }
  print_queue("q1", q1);

  // Min lazy priority queue
  // std::greater<int> makes the max lazy priority queue
  // act as a min lazy priority queue
  lazy_priority_queue<int, std::vector<int>, std::greater<int>> minq1(
      insert_data.begin(), insert_data.end());
  minq1.erase(erase_data.begin(), erase_data.end());
  print_queue("minq1", minq1);

  // Second way to define a min lazy priority queue
  lazy_priority_queue minq2(insert_data.begin(), insert_data.end(),
                            std::greater<int>());
  minq2.erase(erase_data.begin(), erase_data.end());
  print_queue("minq2", minq2);

  // Using a custom function object to compare elements.
  struct {
    bool operator()(const int l, const int r) const { return l > r; }
  } customLess;
  lazy_priority_queue minq3(insert_data.begin(), insert_data.end(), customLess);
  minq3.erase(erase_data.begin(), erase_data.end());
  print_queue("minq3", minq3);

  // Using lambda to compare elements.
  auto cmp = [](int left, int right) { return (left ^ 1) < (right ^ 1); };
  lazy_priority_queue<int, std::vector<int>, decltype(cmp)> q5(cmp);
  for (int n : insert_data) {
    q5.push(n);
  }
  for (int n : erase_data) {
    q5.erase(n);
  }
  print_queue("q5", q5);

  return 0;
}