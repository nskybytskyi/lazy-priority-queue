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
  /// underlying containers.
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
      : comp_(compare), insert_(cont), remove_(Container()) {
    std::make_heap(insert_.begin(), insert_.end(), comp_);
  }

  /// @brief Move-constructs the underlying insert container with
  /// `std::move(cont)`. Value-initializes the underlying remove container.
  /// Copy-constructs the comparison functor with `compare`. Calls
  /// `std::make_heap`.
  /// @param compare the comparison function object to initialize the
  /// underlying comparison functor
  /// @param cont container to be used as source to initialize the underlying
  /// insert container
  lazy_priority_queue(const Compare& compare, Container&& cont)
      : comp_(compare), insert_(std::move(cont)), remove_(Container()) {
    std::make_heap(insert_.begin(), insert_.end(), comp_);
  }

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
      : comp_(compare), insert_(first, last), remove_(Container()) {
    std::make_heap(insert_.begin(), insert_.end(), comp_);
  }

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
      : comp_(compare), insert_(cont), remove_(Container()) {
    insert_.insert(insert_.end(), first, last);
    std::make_heap(insert_.begin(), insert_.end(), comp_);
  }

  const_reference top() const {  // TODO
    while (!remove_.empty() && remove_.front() == insert_.front()) {
      std::pop_heap(insert_.begin(), insert_.end(), comp_);
      insert_.pop_back();
      std::pop_heap(remove_.begin(), remove_.end(), comp_);
      remove_.pop_back();
    }
    return insert_.front();
  }

  bool empty() const { return size() == 0; }

  int size() const {
    return static_cast<int>(insert_.size()) - static_cast<int>(remove_.size());
  }

  void push(const value_type& value) {
    insert_.push_back(value);
    std::push_heap(insert_.begin(), insert_.end(), comp_);
  }

  void push(value_type&& value) {
    insert_.push_back(std::move(value));
    std::push_heap(insert_.begin(), insert_.end(), comp_);
  }

  template <class InputIt>
  void push(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      push(*it);
    }
  }

  void pop() {
    std::ignore = top();
    std::pop_heap(insert_.begin(), insert_.end(), comp_);
    insert_.pop_back();
  }

  void erase(const value_type& value) {
    remove_.push_back(value);
    std::push_heap(remove_.begin(), remove_.end(), comp_);
  }

  void erase(value_type&& value) {
    remove_.push_back(std::move(value));
    std::push_heap(remove_.begin(), remove_.end(), comp_);
  }

  template <class InputIt>
  void erase(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      erase(*it);
    }
  }

 private:
  Compare comp_;
  mutable Container insert_;
  mutable Container remove_;
};

template <class Comp, class Container>
lazy_priority_queue(Comp, Container)
    -> lazy_priority_queue<typename Container::value_type, Container, Comp>;

template <
    class InputIt,
    class Comp = std::less<typename std::iterator_traits<InputIt>::value_type>,
    class Container =
        std::vector<typename std::iterator_traits<InputIt>::value_type>>
lazy_priority_queue(InputIt, InputIt, Comp = Comp(), Container = Container())
    -> lazy_priority_queue<typename std::iterator_traits<InputIt>::value_type,
                           Container, Comp>;