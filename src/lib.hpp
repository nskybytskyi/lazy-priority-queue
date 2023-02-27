#include <functional>
#include <queue>
#include <tuple>
#include <vector>

template <class T, class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class lazy_priority_queue {
 public:
  using value_type = typename Container::value_type;
  using const_reference = typename Container::const_reference;

  lazy_priority_queue() : lazy_priority_queue(Compare()) {}
  lazy_priority_queue(const Compare& compare)
      : insert_(compare), remove_(compare) {}

  const_reference top() const {
    while (!remove_.empty() && remove_.top() == insert_.top()) {
      remove_.pop();
      insert_.pop();
    }
    return insert_.top();
  }

  bool empty() const { return size_ == 0; }

  int size() const { return size_; }

  void push(const value_type& value) {
    ++size_;
    insert_.push(value);
  }

  void pop() {
    --size_;
    std::ignore = top();
    insert_.pop();
  }

  void erase(const value_type& value) {
    --size_;
    remove_.push(value);
  }

 private:
  int size_{0};
  mutable std::priority_queue<T, Container, Compare> insert_;
  mutable std::priority_queue<T, Container, Compare> remove_;
};