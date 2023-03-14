add_executable(simple_test simple.cpp)

target_link_libraries(simple_test PRIVATE compiler_flags lib GTest::gtest_main)

target_include_directories(simple_test PRIVATE "${PROJECT_SOURCE_DIR}/src")

include(GoogleTest)
gtest_discover_tests(simple_test)