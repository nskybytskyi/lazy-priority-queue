cmake_minimum_required(VERSION 3.25.2)

project(lazy_priority_queue VERSION 0.1)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_17)

set(gcc_like_cxx "$<COMPILE_LANG_AND_ID:CXX,ARMClang,AppleClang,Clang,GNU,LCC>")
set(msvc_cxx "$<COMPILE_LANG_AND_ID:CXX,MSVC>")
target_compile_options(compiler_flags INTERFACE
  "$<${gcc_like_cxx}:-Wall;-Wextra;-Werror>"
  "$<${msvc_cxx}:-W3>"
)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)