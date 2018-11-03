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

void compr(std::string const &mode, std::string const &src, std::string const &dst) {
    if (mode == "-c") {
//        file_compressor compressor(src);
//        compressor.compress(dst);

        auto * compressor = new file_compressor(src);
        compressor->compress(dst);
        delete compressor;
    } else if (mode == "-d") {
//        file_decompressor decompressor(src);
//        decompressor.decompress(dst);

        auto * decompressor = new file_decompressor(src);
        decompressor->decompress(dst);
        delete decompressor;
    }
}

template<typename Byte_gen>
void generate_file(std::string const &name, uint64_t size, Byte_gen byte_generator) {
    file_writer writer(name);
    for (uint64_t i = 0; i < size; ++i) {
        writer.print(byte_generator(i));
    }
}

TEST(correctness, example) {
    compr("-c", "example", "compressed");
    compr("-d", "compressed", "decompressed");
    EXPECT_TRUE(compare_files("example", "decompressed"));
}

TEST(correctness, img) {
    compr("-c", "example.jpg", "compressed");
    compr("-d", "compressed", "decompressed.jpg");
    EXPECT_TRUE(compare_files("example.jpg", "decompressed.jpg"));

}

TEST(correctness, empty) {
    generate_file("test.test", 0, [](uint64_t) { return 0; });
    compr("-c", "test.test", "compressed");
    compr("-d", "compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, only_0_test) {
    generate_file("test.test", (1 << 10) + 17, [](uint64_t) { return 0; });
    compr("-c", "test.test", "compressed");
    compr("-d", "compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_short) {
    generate_file("test.test", (1 << 10) + 17, [](uint64_t x) { return static_cast<symbol>(random()); });
    compr("-c", "test.test", "compressed");
    compr("-d", "compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_1_mb) {
    generate_file("test.test", (1 << 20) , [](uint64_t x) { return static_cast<symbol>(random()); });
    compr("-c", "test.test", "compressed");
    compr("-d", "compressed", "decompressed");
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
    compr("-c", "test.test", "compressed");
    compr("-d", "compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

/*TEST(correctness, random_80_mb) {
    generate_file("test.test", 80 * (1 << 20), [](uint64_t) { return static_cast<symbol>(random()); });
    compr("-c", "test.test", "compressed");
    compr("-d", "compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_10_mb_or_less) {
    for (int i = 0; i < 10; ++i) {
        generate_file("test.test", static_cast<uint64_t>(random()) % (10 << 20),
                      [](uint64_t) { return static_cast<symbol>(random()); });
        compr("-c", "test.test", "compressed");
        compr("-d", "compressed", "decompressed");
        EXPECT_TRUE(compare_files("test.test", "decompressed"));
    }
}*/
