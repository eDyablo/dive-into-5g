cmake_minimum_required(VERSION 3.20.0)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project(dive-into-5g)

add_subdirectory(googletest)

include_directories(
  "googletest/googlemock/include"
  "googletest/googletest/include")

add_subdirectory(qpsk-modulator)
add_subdirectory(qpsk-demodulator)
