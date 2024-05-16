project(qpsk)

file(GLOB TESTS test/*.cpp)

add_executable(qpsk-test ${TESTS})
set_target_properties(qpsk-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_include_directories(qpsk-test PRIVATE src)
target_link_libraries(qpsk-test gmock gtest gtest_main)
