#include <iostream>

#include "lib.hpp"

struct Event {
  int priority{};
  char data{' '};

  friend bool operator<(Event const& lhs, Event const& rhs) {
    return lhs.priority < rhs.priority;
  }

  friend std::ostream& operator<<(std::ostream& os, Event const& e) {
    return os << "{ " << e.priority << ", '" << e.data << "' } ";
  }

  bool operator==(const Event& other) const {
    return priority == other.priority && data == other.data;
  }
};

int main() {
  lazy_priority_queue<Event> events;

  std::cout << "Fill the events queue:\n";

  for (auto const e : {Event{6, 'L'},
                       {8, 'I'},
                       {7, 'I'},
                       {9, 'S'},
                       {1, 'T'},
                       {5, 'E'},
                       {4, 'E'},
                       {3, 'N'}}) {
    std::cout << e << ' ';
    events.push(e);
  }

  std::cout << "\n"
               "Remove events from the queue:\n";

  for (auto const e : {Event{7, 'I'}, {4, 'E'}}) {
    std::cout << e << ' ';
    events.erase(e);
  }

  std::cout << "\n"
               "Process events:\n";

  for (; !events.empty(); events.pop()) {
    Event const& e = events.top();
    std::cout << e << ' ';
  }
}