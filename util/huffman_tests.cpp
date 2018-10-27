#include "h/file_compressor.h"
#include "h/file_decompressor.h"
#include "../test/gtest.h"

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

/*bool compare_files(std::string file1, std::string file2) {
    std::ifstream ifs1(file1, std::ios_base::binary);
    std::ifstream ifs2(file2, std::ios_base::binary);

    char buffer1[BUFFER_SIZE];
    char buffer2[BUFFER_SIZE];

    if (!ifs1 || !ifs2) {
        return false;
    }
    do {
        ifs1.read(buffer1, BUFFER_SIZE);
        ifs2.read(buffer2, BUFFER_SIZE);
        if (ifs1.gcount() != ifs2.gcount()) return false;
        for (ptrdiff_t i = 0; i < ifs1.gcount(); ++i) {
            if (buffer1[i] != buffer2[i]) {
                return false;
            }
        }

    } while (ifs1.gcount() > 0 || ifs2.gcount() > 0);

    return true;
}*/

template<typename Byte_gen>
void generate_file(std::string const &name, uint64_t size, Byte_gen byte_generator) {
    file_writer writer(name);
    for (uint64_t i = 0; i < size; ++i) {
        writer.print(byte_generator(i));
    }
}

TEST(correctness, example) {
    file_compressor::compress("example", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("example", "decompressed"));
}


/*TEST(correctness, img) {
    file_compressor::compress("img.jpg", "compressed");
    file_decompressor::decompress("compressed", "decompressed.jpg");
    EXPECT_TRUE(compare_files("img.jpg", "decompressed.jpg"));
}*/

/*
TEST(correctness, empty) {
    generate_file("test.test", 0, [](uint64_t) { return 0; });
    file_compressor::compress("test.test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, only_0_test) {
    generate_file("test.test", (1 << 10) + 17, [](uint64_t) { return 0; });
    file_compressor::compress("test.test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, irregular_1_mb) {
    generate_file("test.test", (1 << 20), [](uint64_t x) {
        x = static_cast<uint64_t>(random());
        if (x % 16 == 0) {
            return 0;
        } else if (x % 16 <= 5) {
            return 1;
        }
        return 2;
    });
    file_compressor::compress("test.test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, _80_mb_random) {
    generate_file("test.test", 80 * (1 << 20), [](uint64_t) { return static_cast<symbol>(random()); });
    file_compressor::compress("test.test", "compressed");
    file_decompressor::decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_10_mb_or_less) {
    for (int i = 0; i < 10; ++i) {
        generate_file("test.test", static_cast<uint64_t>(random()) % (10 << 20),
                      [](uint64_t) { return static_cast<symbol>(random()); });
        file_compressor::compress("test.test", "compressed");
        file_decompressor::decompress("compressed", "decompressed");
        EXPECT_TRUE(compare_files("test.test", "decompressed"));
    }
}
*/
