#include "gtest.h"
#include "../util/h/file_compressor.h"
#include "../util/h/file_decompressor.h"


bool compare_two_files(std::string const &file1, std::string const &file2) {
    file_reader reader1(file1);
    file_reader reader2(file2);

    while (!reader1.eof() && !reader2.eof()) {
        if (reader1.get_symbol() != reader2.get_symbol()) {
            return false;
        }
    }

    return reader1.eof() && reader2.eof();
}

TEST(correctness, empty) {
    file_compressor::compress("../gtest/empty_test.txt", "compressed_file");
    file_decompressor::decompress("compressed_file", "decoded_empty_test.txt");
    EXPECT_TRUE(compare_two_files("../gtest/empty_test.txt", "decoded_empty_test.txt"));
}

TEST(correctness, so_many_0_test) {
    file_compressor::compress("../gtest/so_many_0_test.txt", "compressed_file");
    file_decompressor::decompress("compressed_file", "decoded_so_many_0_test.txt");
    EXPECT_TRUE(compare_two_files("../gtest/so_many_0_test.txt", "decoded_so_many_0_test.txt"));
}

TEST(correctness, one_mb) {
    file_compressor::compress("../gtest/test1Mb.txt", "compressed_file");
    file_decompressor::decompress("compressed_file", "decoded_test1Mb.txt");
    EXPECT_TRUE(compare_two_files("../gtest/test1Mb.txt", "decoded_test1Mb.txt"));
}

/*TEST(correctness, compress_eighty_mb)
{
 file_compressor::compress("../gtest/test80Mb.txt", "compressed_file");
}*/

//TEST(correctness, eighty_mb)
//{
//  class_helper helper;
//  huffman_coding huff;
//  file_compressor::compress("../gtest/test80Mb.txt", "compressed_file");
//  file_decompressor::decompress("test80Mb.txt.huff", "compressed_file");
//  EXPECT_EQ(compare_two_files("../gtest/test80Mb.txt", "decoded_test80Mb.txt"), true);
//}

TEST(correctness, jpg_test) {
    file_compressor::compress("../gtest/jpg_test.jpg", "compressed_file");
    file_decompressor::decompress("compressed_file", "decoded_jpg_test.jpg");
    EXPECT_TRUE(compare_two_files("../gtest/jpg_test.jpg", "decoded_jpg_test.jpg"));
}
