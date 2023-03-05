link_libraries(compiler_flags lib)
include_directories("${PROJECT_SOURCE_DIR}/src")

add_executable(simple_example simple.cpp)
add_executable(events_example events.cpp)