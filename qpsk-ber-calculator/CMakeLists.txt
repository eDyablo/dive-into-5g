project(qpsk-ber-calculator)

file(GLOB TESTS test/*.cpp)

add_executable(qpsk-ber-calculator-test ${TESTS})
set_target_properties(qpsk-ber-calculator-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_include_directories(qpsk-ber-calculator-test PRIVATE src)
target_link_libraries(qpsk-ber-calculator-test gmock gtest gtest_main)

add_executable(qpsk-ber-calculator src/main.cpp)
set_target_properties(qpsk-ber-calculator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(qpsk-ber-calculator PUBLIC -static)
