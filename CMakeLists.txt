cmake_minimum_required(VERSION 3.12)
project(HUFFMAN)

set(CMAKE_CXX_STANDARD 14)

add_executable(HUFFMAN util/main.cpp lib/code_tree.cpp lib/h/code_tree.h lib/h/types_consts.h util/file_compressor.cpp util/h/file_compressor.h util/file_reader.cpp util/h/file_reader.h util/file_writer.cpp util/h/file_writer.h util/file_decompressor.cpp util/h/file_decompressor.h lib/data_compressor.cpp lib/h/data_compressor.h lib/code.cpp lib/h/code.h lib/data_decompressor.cpp lib/h/data_decompressor.h)