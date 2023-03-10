#include <iostream>

#include "lib.hpp"

int main() {
  std::cout << std::boolalpha;

  lazy_priority_queue<int> container;

  std::cout << "Initially, container.empty(): " << container.empty() << '\n';

  container.push(42);
  std::cout << "After adding an element, container.empty(): "
            << container.empty() << '\n';

  container.erase(42);
  std::cout << "After removing an element, container.empty(): "
            << container.empty() << '\n';

  return 0;
}