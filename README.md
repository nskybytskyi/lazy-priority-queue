This project provides an implementation of std::priority_queue with implicit removals.
An explicit removal is performed only when the accessed top element has been removed.
The behavior is undefined if the element being removed was not present in the queue. 

This project uses a variety of tools and utilities that accompany the algorithmic part:
- [ ] CMake;
- [ ] Clang Tools:
    - [x] clang-format;
    - [ ] clang-tidy.
- [ ] Testing:
    - [ ] GoogleTest.
- [x] Git:
    - [x] gitignore;
    - [x] gitattributes.
- [ ] CI:
    - [ ] git hooks;
    - [ ] doxygen.

In the future I may consider adding the following tools and utilities to the project:
- cppcheck;
- valgrind;
- gprof/gperf.