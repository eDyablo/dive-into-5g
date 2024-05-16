project(qpsk-noise-injector)

file(GLOB TESTS test/*.cpp)

add_executable(qpsk-noise-injector-test ${TESTS})
set_target_properties(qpsk-noise-injector-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_include_directories(qpsk-noise-injector-test PRIVATE src)
target_link_libraries(qpsk-noise-injector-test gmock gtest gtest_main)

add_executable(qpsk-noise-injector src/main.cpp)
set_target_properties(qpsk-noise-injector PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(qpsk-noise-injector PUBLIC -static)
