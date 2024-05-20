cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

project(dive-into-5g)

add_subdirectory(googletest)

include_directories(
  "cxxopts/include"
  "googletest/googlemock/include"
  "googletest/googletest/include"
  "./")

add_subdirectory(qpsk-bits-generator)
add_subdirectory(qpsk-demodulator)
add_subdirectory(qpsk-modulator)
add_subdirectory(qpsk-noise-injector)
add_subdirectory(qpsk)
