#include <cassert>
#include <deque>
#include <functional>
#include <string>
#include <vector>

#include "../src/lib.hpp"

int main() {
  {
    lazy_priority_queue<int> queue;
    assert(queue.empty());
    assert(queue.size() == 0);

    queue.push(1);
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == 1);

    queue.push(3);
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == 3);

    queue.push(2);
    assert(!queue.empty());
    assert(queue.size() == 3);
    assert(queue.top() == 3);

    queue.erase(2);
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == 3);

    queue.pop();
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == 1);

    queue.pop();
    assert(queue.empty());
    assert(queue.size() == 0);
  }

  {
    lazy_priority_queue<std::string> queue;
    assert(queue.empty());
    assert(queue.size() == 0);

    queue.push("hello");
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == "hello");

    queue.push("world");
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == "world");

    queue.push("nicky");
    assert(!queue.empty());
    assert(queue.size() == 3);
    assert(queue.top() == "world");

    queue.erase("nicky");
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == "world");

    queue.pop();
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == "hello");

    queue.pop();
    assert(queue.empty());
    assert(queue.size() == 0);
  }

  {
    lazy_priority_queue<int, std::deque<int>> queue;
    assert(queue.empty());
    assert(queue.size() == 0);

    queue.push(1);
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == 1);

    queue.push(3);
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == 3);

    queue.push(2);
    assert(!queue.empty());
    assert(queue.size() == 3);
    assert(queue.top() == 3);

    queue.erase(2);
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == 3);

    queue.pop();
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == 1);

    queue.pop();
    assert(queue.empty());
    assert(queue.size() == 0);
  }

  {
    lazy_priority_queue<int, std::vector<int>, std::greater<int>> queue;
    assert(queue.empty());
    assert(queue.size() == 0);

    queue.push(3);
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == 3);

    queue.push(1);
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == 1);

    queue.push(2);
    assert(!queue.empty());
    assert(queue.size() == 3);
    assert(queue.top() == 1);

    queue.erase(2);
    assert(!queue.empty());
    assert(queue.size() == 2);
    assert(queue.top() == 1);

    queue.pop();
    assert(!queue.empty());
    assert(queue.size() == 1);
    assert(queue.top() == 3);

    queue.pop();
    assert(queue.empty());
    assert(queue.size() == 0);
  }

  return 0;
}