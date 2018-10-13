cmake_minimum_required(VERSION 3.12)
project(HUFFMAN_LIB)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O2 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/h)

set(LIB_HEADERS h/code.h
        h/code_tree.h
        h/data_compressor.h
        h/data_decompressor.h
        h/types_consts.h)

set(LIB_SOURCES code_tree.cpp code.cpp data_compressor.cpp data_decompressor.cpp)

add_library(huf_lib ${LIB_HEADERS} ${LIB_SOURCES})