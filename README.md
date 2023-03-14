This project provides an implementation of std::priority_queue with implicit removals.
An explicit removal is performed only when the accessed top element has been removed.
The behavior is undefined if the element being removed was not present in the queue. 

[![Build Status (GitHub Actions)](https://github.com/nskybytskyi/lazy-priority-queue/workflows/CMake%20Tests/badge.svg)](https://github.com/nskybytskyi/lazy-priority-queue/actions?query=workflow%3A"CMake%20Tests")

This project uses a variety of tools and utilities that accompany the algorithmic part:
- [x] CMake;
- [ ] Clang Tools:
    - [x] clang-format;
    - [ ] clang-tidy.
- [x] Testing:
    - [x] GoogleTest.
- [x] Git:
    - [x] gitignore;
    - [x] gitattributes.
- [ ] CI:
    - [ ] git hooks;
    - [x] CTest;
    - [x] doxygen.

In the future I may consider adding the following tools and utilities to the project:
- cppcheck;
- valgrind;
- gprof/gperf.