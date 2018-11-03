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

TEST(correctness, example) { // needs file "example" in ..release/test directory
    try {
        file_reader("example");
    } catch (...) {
        std::cerr << "\"example\" not found, so created like empty file\n";
        generate_file("example", 0, [](uint64_t) { return 0; });
    }
    compress("example", "compressed");
    decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("example", "decompressed"));
}

TEST(correctness, img) { // needs file "example.jpg" in ..release/test directory
    try {
        file_reader("example.jpg");
    } catch (...) {
        std::cerr << "\"example.jpg\" not found, so created like empty file\n";
        generate_file("example.jpg", 0, [](uint64_t) { return 0; });
    }
    compress("example.jpg", "compressed");
    decompress("compressed", "decompressed.jpg");
    EXPECT_TRUE(compare_files("example.jpg", "decompressed.jpg"));
}

TEST(correctness, empty) {
    generate_file("test.test", 0, [](uint64_t) { return 0; });
    compress("test.test", "compressed");
    decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, wrong_compressed) {
    {
        file_writer writer("test.test");
        writer.print_n_bytes(8, 2 << 10);
        writer.print_number(10);
        for (int i = 0; i < 2 << 10; ++i) {
            writer.print(0);
        }
    }
    EXPECT_ANY_THROW(decompress("test.test", "decompressed"));
}

TEST(correctness, only_0) {
    generate_file("test.test", (1 << 10) + 17, [](uint64_t) { return 0; });
    compress("test.test", "compressed");
    decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_short) {
    generate_file("test.test", (1 << 10) - 5, [](uint64_t x) { return static_cast<symbol>(random()); });
    compress("test.test", "compressed");
    decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_1_mb) {
    generate_file("test.test", (1 << 20), [](uint64_t x) { return static_cast<symbol>(random()); });
    compress("test.test", "compressed");
    decompress("compressed", "decompressed");
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
    compress("test.test", "compressed");
    decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_80_mb) {
    generate_file("test.test", 80 * (1 << 20), [](uint64_t) { return static_cast<symbol>(random()); });
    compress("test.test", "compressed");
    decompress("compressed", "decompressed");
    EXPECT_TRUE(compare_files("test.test", "decompressed"));
}

TEST(correctness, random_10_mb_or_less) {
    int passed = 0;
    int tests = 10;
    for (int i = 0; i < tests; ++i) {
        generate_file("test.test", static_cast<uint64_t>(random()) % (10 << 20),
                      [](uint64_t) { return static_cast<symbol>(random()); });
        compress("test.test", "compressed");
        decompress("compressed", "decompressed");
        passed += compare_files("test.test", "decompressed");
    }
    EXPECT_EQ(passed, tests);
}

TEST(correctness, random_many_small) {
    int passed = 0;
    int tests = 10000;
    for (int i = 0; i < tests; ++i) {
        generate_file("test.test", static_cast<uint64_t>(random()) % (1 << 12),
                      [](uint64_t) { return static_cast<symbol>(random()); });
        compress("test.test", "compressed");
        decompress("compressed", "decompressed");
        passed += compare_files("test.test", "decompressed");
    }
    EXPECT_EQ(passed, tests);
}
