#include <functional>
#include <iterator>
#include <queue>
#include <tuple>
#include <vector>

/// @brief A priority queue is a container adaptor that provides constant time
/// lookup of the largest (by default) element, at the expense of logarithmic
/// insertion and extraction. A user-provided `Compare` can be supplied to
/// change the ordering, e.g.using `std::greater<T>` would cause the smallest
/// element to appear as the `top()`. Working with a `priority_queue` is similar
/// to managing a heap in some random access container, with the benefit of not
/// being able to accidentally invalidate the heap.
/// @tparam T The type of the stored elements. The behavior is undefined if
/// `T` is not the same type as `Container::value_type.
/// @tparam Container The type of the underlying container to use to store
/// the elements. The container must satisfy the requirements of
/// SequenceContainer, and its iterators must satisfy the requirements of
/// LegacyRandomAccessIterator. Additionally, it must provide the following
/// functions with the usual semantics:
/// - front()
/// - push_back()
/// - pop_back().
/// The standard containers `std::vector` (including `std::vector<bool>`)
/// and `std::deque` satisfy these requirements.
/// @tparam Compare A Compare type providing a strict weak ordering. Note
/// that the Compare parameter is defined such that it returns `true` if its
/// first argument comes before its second argument in a weak ordering. But
/// because the priority queue outputs largest elements first, the elements
/// that "come before" are actually output last. That is, the front of the
/// queue contains the "last" element according to the weak ordering imposed
/// by Compare.
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

  /// @brief Move-constructs the underlying insert container with
  /// `std::move(cont)`. Copy-constructs the comparison functor from
  /// `compare`. Then inserts all elements from the `{first, last}` range into
  /// the insert container. Finally calls `std::make_heap`.
  /// @tparam InputIt must meet the requirements of LegacyInputIterator.
  /// @param first the beginning of the range of elements to initialize with
  /// @param last the end of the range of elements to initialize with
  /// @param compare the comparison function object to initialize the
  /// underlying comparison functor
  /// @param cont container to be used as source to initialize the underlying
  /// insert container
  template <class InputIt>
  lazy_priority_queue(InputIt first, InputIt last, const Compare& compare,
                      Container&& cont)
      : comp_(compare), insert_(std::move(cont)), remove_(Container()) {
    insert_.insert(insert_.end(), first, last);
    std::make_heap(insert_.begin(), insert_.end(), comp_);
  }

  /// @brief Returns reference to the top element in the priority queue. This
  /// element will be removed on a call to `pop()`. If default comparison
  /// function is used, the returned element is also the greatest among the
  /// elements in the queue.
  /// @return Reference to the top element as if obtained by a call to
  /// `insert_.front()`
  /// @see pop()
  const_reference top() const {
    while (!remove_.empty() && remove_.front() == insert_.front()) {
      std::pop_heap(insert_.begin(), insert_.end(), comp_);
      insert_.pop_back();
      std::pop_heap(remove_.begin(), remove_.end(), comp_);
      remove_.pop_back();
    }
    return insert_.front();
  }

  /// @brief Checks if the underlying containers have no elements, i.e. whether
  /// `insert_` contains elements that `remove_` does not
  /// @return `true` if the underlying container is empty, `false` otherwise
  /// @see size()
  bool empty() const { return size() == 0; }

  /// @brief Returns the number of elements in the underlying containers, that
  /// is, `insert_.size() - remove_.size()`
  /// @return The number of elements in the container.
  /// @see empty()
  int size() const {
    return static_cast<int>(insert_.size()) - static_cast<int>(remove_.size());
  }

  /// @brief Pushes the given element value to the priority queue.
  /// @param value the value of the element to push
  /// @see emplace()
  /// @see pop()
  void push(const value_type& value) {
    insert_.push_back(value);
    std::push_heap(insert_.begin(), insert_.end(), comp_);
  }

  /// @brief Moves the given element value to the priority queue.
  /// @param value the value of the element to push
  /// @see emplace()
  /// @see pop()
  void push(value_type&& value) {
    insert_.push_back(std::move(value));
    std::push_heap(insert_.begin(), insert_.end(), comp_);
  }

  /// @brief Pushes the given range of value to the priority queue.
  /// @tparam InputIt must meet the requirements of LegacyInputIterator.
  /// @param first the beginning of the range of elements to push
  /// @param last the end of the range of elements to push
  /// @see emplace()
  /// @see pop()
  template <class InputIt>
  void push(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      push(*it);
    }
  }

  /// @brief Removes the top element from the priority queue.
  /// @see emplace()
  /// @see push()
  /// @see top()
  void pop() {
    std::ignore = top();
    std::pop_heap(insert_.begin(), insert_.end(), comp_);
    insert_.pop_back();
  }

  /// @brief Removes the value from the priority queue.
  /// @param value the value of the element to remove
  /// @see pop()
  void erase(const value_type& value) {
    remove_.push_back(value);
    std::push_heap(remove_.begin(), remove_.end(), comp_);
  }

  /// @brief Removes the value from the priority queue.
  /// @param value the value of the element to remove
  /// @see pop()
  void erase(value_type&& value) {
    remove_.push_back(std::move(value));
    std::push_heap(remove_.begin(), remove_.end(), comp_);
  }

  /// @brief Removes the given range of value from the priority queue.
  /// @tparam InputIt must meet the requirements of LegacyInputIterator.
  /// @param first the beginning of the range of elements to remove
  /// @param last the end of the range of elements to remove
  /// @see pop()
  template <class InputIt>
  void erase(InputIt first, InputIt last) {
    for (auto it = first; it != last; ++it) {
      erase(*it);
    }
  }

  /// @brief Pushes a new element to the priority queue. The element is
  /// constructed in-place, i.e. no copy or move operations are performed. The
  /// constructor of the element is called with exactly the same arguments as
  /// supplied to the function.
  /// @param args	arguments to forward to the constructor of the element
  /// @see push()
  /// @see pop()
  template <class... Args>
  void emplace(Args&&... args) {
    insert_.emplace_back(std::forward<Args>(args)...);
    std::push_heap(insert_.begin(), insert_.end(), comp_);
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