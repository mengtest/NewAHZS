cmake_minimum_required(VERSION 2.8)
project(googleTest)

include_directories(
   ./include
   ./src
   .
)
 
add_library (googleTest
    src/gtest.cc
	src/gtest-death-test.cc
	src/gtest-filepath.cc
	src/gtest-port.cc
	src/gtest-printers.cc
	src/gtest-test-part.cc
	src/gtest-typed-test.cc
)