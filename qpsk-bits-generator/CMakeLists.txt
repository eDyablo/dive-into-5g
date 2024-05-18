project(qpsk-bits-generator)

add_executable(qpsk-bits-generator src/main.cpp)
set_target_properties(qpsk-bits-generator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(qpsk-bits-generator PUBLIC -static)
