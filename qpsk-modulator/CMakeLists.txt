project(qpsk-modulator)

file(GLOB TESTS test/*.cpp)

add_executable(qpsk-modulator-test ${TESTS})
set_target_properties(qpsk-modulator-test PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_include_directories(qpsk-modulator-test PRIVATE src)
target_link_libraries(qpsk-modulator-test gmock gtest gtest_main)

add_executable(qpsk-modulator src/main.cpp)
set_target_properties(qpsk-modulator PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
target_link_libraries(qpsk-modulator PUBLIC -static)
