project(qpsk-demodulator)

file(GLOB TESTS test/*.cpp)

add_executable(qpsk-demodulator-test ${TESTS})
set_target_properties(qpsk-demodulator-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_include_directories(qpsk-demodulator-test PRIVATE src)
target_link_libraries(qpsk-demodulator-test gmock gtest gtest_main)

add_executable(qpsk-demodulator src/main.cpp)
set_target_properties(qpsk-demodulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(qpsk-demodulator PUBLIC -static)
