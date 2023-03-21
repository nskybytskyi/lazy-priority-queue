link_libraries(compiler_flags lib GTest::gtest_main)

add_executable(interface_test interface.cpp)

include_directories("${PROJECT_SOURCE_DIR}/src")

gtest_discover_tests(interface_test)

add_subdirectory(set_difference)