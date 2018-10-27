cmake_minimum_required(VERSION 3.12)
project(HUFFMAN_TESTS)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O2 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/h)
include_directories(${HUFFMAN_UTILITY_SOURCE_DIR}/h)

set(HEADERS
        ../lib/h/code.h
        ../lib/h/code_tree.h
        ../lib/h/data_compressor.h
        ../lib/h/data_decompressor.h
        ../lib/h/types_consts.h

        ../util/h/file_compressor.h
        ../util/h/file_decompressor.h
        ../util/h/file_reader.h
        ../util/h/file_writer.h

        gtest.h)

set(SOURCES
        ../lib/code.cpp
        ../lib/code_tree.cpp
        ../lib/data_compressor.cpp
        ../lib/data_decompressor.cpp

        ../util/file_compressor.cpp
        ../util/file_decompressor.cpp
        ../util/file_reader.cpp
        ../util/file_writer.cpp

        gtest_main.cc
        gtest-all.cc
        ../util/huffman_tests.cpp)

add_executable(test ${HEADERS} ${SOURCES})

target_link_libraries(test -lpthread)
