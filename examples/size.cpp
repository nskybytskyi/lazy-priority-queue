#include <iostream>

#include "lib.hpp"

int main() {
  lazy_priority_queue<int> container;

  std::cout << "Initially, container.size(): " << container.size() << '\n';

  for (int i = 0; i < 7; ++i) {
    container.push(i);
  }

  std::cout << "After adding elements, container.size(): " << container.size()
            << '\n';

  for (int i = 1; i < 7; i += 2) {
    container.erase(i);
  }

  std::cout << "After removing elements, container.size(): " << container.size()
            << '\n';

  return 0;
}