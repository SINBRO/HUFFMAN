#include <iostream>
#include <cstring>
#include "h/file_compressor.h"
#include "h/file_decompressor.h"

int main(int argc, char* argv[]) {
    if (argc != 3) {
        std::cerr << "Incorrect arguments. Expected: -mode(-c/-d) SRC DST";
        return -1;
    }
    std::string mode, src, dst;
    mode = argv[0];
    src = argv[1];
    dst = argv[2];
    clock_t start, finish;

    if (mode == "-c") {
        std::cerr << "Compressing " + src + "\n";
        start = clock();
        try {
            file_compressor compressor(src);
            compressor.compress(dst);
        } catch (std::runtime_error &e) {
            std::cerr << "Unable to compress: ";
            std::cerr << e.what();
            return -1;
        }
        finish = clock();
        std::cerr << "Successfully compressed in " + std::to_string(finish-start) + " ms";
        return 0;
    } else if (mode == "-d") {
        std::cerr << "Decompressing " + src + "\n";
        start = clock();
        try {
            file_decompressor decompressor(src);
            decompressor.decompress(dst);
        } catch (std::runtime_error &e) {
            std::cerr << "Unable to decompress: ";
            std::cerr << e.what();
            return -1;
        }
        finish = clock();
        std::cerr << "Successfully decompressed in " + std::to_string(finish-start) + " ms";
        return 0;

    } else {
        std::cerr << "Incorrect mode. Expected -c (compress) or -d (decompress)";
        return -1;
    }
}