This project provides an implementation of std::priority_queue with implicit removals.
An explicit removal is performed only when the accessed top element has been removed.
The behavior is undefined if the element being removed was not present in the queue. 

[![Build Status (GitHub Actions)](https://github.com/nskybytskyi/lazy-priority-queue/workflows/CMake%20Tests/badge.svg)](https://github.com/nskybytskyi/lazy-priority-queue/actions?query=workflow%3A"CMake%20Tests")

This project uses a variety of tools and utilities that accompany the algorithmic part:
- [x] CMake:
    - [x] googletest integration;
    - [ ] cppcheck integration;
    - [ ] clang-tidy integration.

- [ ] Clang tools:
    - [x] [clang-format](https://clang.llvm.org/docs/ClangFormat.html);
    - [ ] [clang-tidy](https://clang.llvm.org/extra/clang-tidy/).

- [ ] Correctness and performance:
    - [x] [googletest](https://github.com/google/googletest);
    - [ ] test coverage analysis with codecov;
    - [ ] runtime analysis:
        - [ ] address sanitizer;
        - [ ] undefined-behavior sanitizer;
        - [ ] memory sanitizer;
        - [ ] valgrind?
    - [ ] [google/benchmark](https://github.com/google/benchmark).

- [x] Git utilities:
    - [x] [gitignore](https://github.com/github/gitignore);
    - [x] [gitattributes](https://github.com/alexkaratarakis/gitattributes).

- [ ] GitHub actions & workflows:
    - [x] testing;
    - [ ] benchmarking;
    - [ ] codecov integration;
    - [ ] documentation generation;
    - [ ] documentation publishing.

- [ ] GitHub community guidelines:
    - [x] code of conduct;
    - [ ] contributing guidelines;
    - [ ] security policy;
    - [ ] issue and PR templates.
