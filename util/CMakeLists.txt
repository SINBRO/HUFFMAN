cmake_minimum_required(VERSION 3.12)
project(HUFFMAN_UTIL)

if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++11 -O2 -pedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address,undefined -D_GLIBCXX_DEBUG")
endif()

include_directories(${HUFFMAN_LIBRARY_SOURCE_DIR}/h)
include_directories(${HUFFMAN_UTILITY_SOURCE_DIR}/h)


set(HEADERS h/file_reader.h
        h/file_writer.h
        h/file_compressor.h
        h/file_decompressor.h)

set(SOURCES file_reader.cpp
        file_writer.cpp
        file_compressor.cpp
        file_decompressor.cpp
        main.cpp)

add_executable(huffman ${HEADERS} ${SOURCES})

target_link_libraries(huffman huf_lib)