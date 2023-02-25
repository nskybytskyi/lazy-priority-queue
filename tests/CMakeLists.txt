add_executable(simple_test simple.cpp)

target_link_libraries(simple_test PRIVATE compiler_flags lib)

target_include_directories(simple_test PRIVATE "${PROJECT_SOURCE_DIR}/src")