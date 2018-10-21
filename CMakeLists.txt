cmake_minimum_required(VERSION 3.12)
project(HUFFMAN)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O2 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

add_subdirectory(lib)
add_subdirectory(util)

#[[add_executable(tests
        gtest/gtest_main.cc
        gtest/haffman_algo_tests.cpp
        gtest/gtest.h
        gtest/gtest-all.cc
        gtest/gtest_main.cc)]]
