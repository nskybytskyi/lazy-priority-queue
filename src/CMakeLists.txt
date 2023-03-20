add_library(lib INTERFACE)

target_link_libraries(lib INTERFACE compiler_flags)

add_subdirectory(set_difference)