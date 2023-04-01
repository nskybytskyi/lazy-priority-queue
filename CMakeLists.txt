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

# Find CppCheck executable
find_program(CMAKE_CXX_CPPCHECK NAMES cppcheck)

# If CppCheck executable found
if(CMAKE_CXX_CPPCHECK)
  # Check CppCheck version
  set(CPP_CHECK_CMD ${CMAKE_CXX_CPPCHECK} --version)
  execute_process(COMMAND ${CPP_CHECK_CMD}
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    RESULT_VARIABLE CPP_CHECK_RESULT
    OUTPUT_VARIABLE CPP_CHECK_VERSION
    ERROR_VARIABLE CPP_CHECK_ERROR)

  # Check if version could be extracted
  if(CPP_CHECK_RESULT EQUAL 0)
    # Append desired arguments to CppCheck
	  list(APPEND CMAKE_CXX_CPPCHECK "--enable=all" "--suppress=missingIncludeSystem")
  endif()
endif()

enable_testing()

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
include(GoogleTest)

add_subdirectory(src)
add_subdirectory(tests)
add_subdirectory(examples)