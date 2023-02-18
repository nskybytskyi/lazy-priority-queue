#include <queue>
#include <tuple>

template <class T>
class lazy_priority_queue {
  public:
    T top() const {
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

    void push(T value) {
      ++size_;
      insert_.push(value);
    }

    void pop() {
      --size_;
      std::ignore = top();
      insert_.pop();
    }

    void erase(T value) {
      --size_;
      remove_.push(value);
    }

  private:
    int size_{0};
    mutable std::priority_queue<T> insert_;
    mutable std::priority_queue<T> remove_;
};