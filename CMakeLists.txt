cmake_minimum_required(VERSION 3.5.0)

project(dive-into-5g)

add_subdirectory(googletest)

include_directories(
  "googletest/googlemock/include"
  "googletest/googletest/include")

add_subdirectory(hello)
