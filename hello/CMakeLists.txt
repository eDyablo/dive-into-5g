project(hello)

add_executable(hello src/hello.cpp)

target_link_libraries(hello PUBLIC -static)

set_target_properties(hello PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
