add_executable(simple_example simple.cpp)

target_link_libraries(simple_example PRIVATE compiler_flags lib)

target_include_directories(simple_example PRIVATE "${PROJECT_SOURCE_DIR}/src")