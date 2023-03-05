#include <functional>
#include <iterator>
#include <queue>
#include <tuple>
#include <vector>

template <class T, class Container = std::vector<T>,
          class Compare = std::less<typename Container::value_type>>
class lazy_priority_queue {
 public:
  using value_type = typename Container::value_type;
  using const_reference = typename Container::const_reference;

  /// @brief Default constructor. Value-initializes the comparator and the
  /// underlying containesr.
  lazy_priority_queue() : lazy_priority_queue(Compare(), Container()) {}

  /// @brief Copy-constructs the comparison functor with the contents of
  /// `compare`. Value-initializes the underlying containers.
  /// @param compare the comparison function object to initialize the
  /// underlying comparison functor
  explicit lazy_priority_queue(const Compare& compare)
      : lazy_priority_queue(compare, Container()) {}

  /// @brief Copy-constructs the underlying insert container from `cont`.
  /// Value-initializes the underlying remove container. Copy-constructs the
  /// comparison functor from `compare`. Calls `std::make_heap`.
  /// @param compare the comparison function object to initialize the
  /// underlying comparison functor
  /// @param cont container to be used as source to initialize the underlying
  /// insert container
  explicit lazy_priority_queue(const Compare& compare, const Container& cont)
      : insert_(compare, cont), remove_(compare, Container()) {}

  /// @brief Move-constructs the underlying insert container with
  /// `std::move(cont)`. Value-initializes the underlying remove container.
  /// Copy-constructs the comparison functor with `compare`. Calls
  /// `std::make_heap`.
  /// @param compare the comparison function object to initialize the
  /// underlying comparison functor
  /// @param cont container to be used as source to initialize the underlying
  /// insert container
  lazy_priority_queue(const Compare& compare, Container&& cont)
      : insert_(compare, cont), remove_(compare, Container()) {}

  /// @brief Constructs the underlying container from the `{first, last}` range
  /// and the comparator from `compare`. Calls `std::make_heap`.
  /// @tparam InputIt must meet the requirements of LegacyInputIterator.
  /// @param first the beginning of the range of elements to initialize with
  /// @param last the end of the range of elements to initialize with
  /// @param compare the comparison function object to initialize the
  /// underlying comparison functor
  template <class InputIt>
  lazy_priority_queue(InputIt first, InputIt last,
                      const Compare& compare = Compare())
      : insert_(first, last, compare), remove_(compare) {}

  /// @brief Copy-constructs the underlying insert container from `cont`.
  /// Value-initializes the underlying remove container. Copy-constructs the
  /// comparison functor from `compare`. Then inserts all elements from the
  /// `{first, last}` range into the insert container. Finally calls
  /// `std::make_heap`.
  /// @tparam InputIt must meet the requirements of LegacyInputIterator.
  /// @param first the beginning of the range of elements to initialize with
  /// @param last the end of the range of elements to initialize with
  /// @param compare the comparison function object to initialize the
  /// underlying comparison functor
  /// @param cont container to be used as source to initialize the underlying
  /// insert container
  template <class InputIt>
  lazy_priority_queue(InputIt first, InputIt last, const Compare& compare,
                      const Container& cont)
      : insert_(first, last, compare, cont), remove_(compare, Container()) {}

  const_reference top() const {
    while (!remove_.empty() && remove_.top() == insert_.top()) {
      remove_.pop();
      insert_.pop();
    }
    return insert_.top();
  }

  bool empty() const { return size() == 0; }

  int size() const {
    return static_cast<int>(insert_.size()) - static_cast<int>(remove_.size());
  }

  void push(const value_type& value) { insert_.push(value); }

  template <class InputIt>
  void push(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      push(*it);
    }
  }

  void pop() {
    std::ignore = top();
    insert_.pop();
  }

  void erase(const value_type& value) { remove_.push(value); }

  template <class InputIt>
  void erase(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      erase(*it);
    }
  }

 private:
  // TODO: do not duplicate Compare
  mutable std::priority_queue<T, Container, Compare> insert_;
  mutable std::priority_queue<T, Container, Compare> remove_;
};

template <
    class InputIt,
    class Comp = std::less<typename std::iterator_traits<InputIt>::value_type>,
    class Container =
        std::vector<typename std::iterator_traits<InputIt>::value_type>>
lazy_priority_queue(InputIt, InputIt, Comp = Comp(), Container = Container())
    -> lazy_priority_queue<typename std::iterator_traits<InputIt>::value_type,
                           Container, Comp>;