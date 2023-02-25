cmake_minimum_required(VERSION 3.25.2)

project(lazy_priority_queue VERSION 0.1)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_11)

add_subdirectory(src)
add_subdirectory(tests)