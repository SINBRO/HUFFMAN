#include "../util/h/file_compressor.h"
#include "../util/h/file_decompressor.h"
#include "gtest.h"

bool compare_files(std::string const &file1, std::string const &file2) {
    file_reader reader1(file1);
    file_reader reader2(file2);

    while (!reader1.eof() && !reader2.eof()) {
        if (reader1.get_symbol() != reader2.get_symbol()) {
            return false;
        }
    }

    return reader1.eof() && reader2.eof();
}

template<typename Byte_gen>
void generate_file(std::string const &name, uint64_t size, Byte_gen byte_generator) {
    file_writer writer(name);
    for (uint64_t i = 0; i < size; ++i) {
        writer.print(byte_generator(i));
    }
}

TEST(correctness, empty) {
    generate_file("test", 0, [](uint64_t) { return 0; });
    file_compressor::compress("../test/test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("../test/test", "decompressed"));
}

TEST(correctness, only_0_test) {
    generate_file("test", (1 << 10) + 17, [](uint64_t) { return 0; });
    file_compressor::compress("../test/test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("../test/test", "decompressed"));
}

TEST(correctness, irregular_1_mb) {
    generate_file("test", (1 << 20), [](uint64_t x) {
        if (x % 16 == 0) {
            return 0;
        } else if (x % 16 <= 5) {
            return 1;
        }
        return 2;
    });
    file_compressor::compress("../test/test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("../test/test", "decompressed"));
}

TEST(correctness, _80_mb_random) {
    generate_file("test", 80 * (1 << 20), [](uint64_t) { return static_cast<symbol>(random()); });
    file_compressor::compress("../test/test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("../test/test", "decompressed"));
}

TEST(correctness, random_10_mb_or_less) {
    for (int i = 0; i < 20; ++i) {
        generate_file("test", static_cast<uint64_t>(random()) % (10 << 20),
                      [](uint64_t) { return static_cast<symbol>(random()); });
        file_compressor::compress("../test/test", "compressed");
        file_decompressor::decompress("compressed", "decompressed");
        EXPECT_TRUE(compare_files("../test/test", "decompressed"));
    }
}
