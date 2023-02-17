#include <queue>
#include <tuple>

class lazy_priority_queue {
  public:
    int top() const {
      while (!remove_.empty() && remove_.top() == insert_.top()) {
        remove_.pop();
        insert_.pop();
      }
      return insert_.top();
    }

    bool empty() const {
      return size_ == 0;
    }

    int size() const {
      return size_;
    }

    void push(int value) {
      ++size_;
      insert_.push(value);
    }

    void pop() {
      --size_;
      std::ignore = top();
      insert_.pop();
    }

    void erase(int value) {
      --size_;
      remove_.push(value);
    }

  private:
    int size_{0};
    mutable std::priority_queue<int> insert_;
    mutable std::priority_queue<int> remove_;
};