#include <cassert>

int main() {
  lazy_priority_queue queue;
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

  return 0;
}