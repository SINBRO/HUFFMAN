#include <iostream>
#include "h/file_compressor.h"
#include "h/file_decompressor.h"

int main(int argc, char *argv[]) {
    if (argc != 4) {
        std::cerr << "Incorrect arguments. Expected: -mode(-c/-d) SRC DST";
        return -1;
    }
    std::string mode, src, dst;
    mode = argv[1];
    src = argv[2];
    dst = argv[3];
    clock_t start, finish;
    size_t file_size;

    if (mode == "-c") {
        std::cerr << "Compressing \"" + src + "\" in \""+ dst + "\" ...\n";
        start = clock();
        try {
            file_compressor compressor(src);
            file_size = compressor.file_bytes_cnt();
            compressor.compress(dst);
        } catch (std::runtime_error &e) {
            std::cerr << "Unable to compress: ";
            std::cerr << e.what();
            return -1;
        }
        finish = clock();
        std::cerr << "Successfully compressed " << double(file_size) / (1 << 20)
                  << " mb in " + std::to_string((finish - start) * 1000 / CLOCKS_PER_SEC) + " ms ("
                  << double(file_size) / (1 << 20) / (double(finish - start) / CLOCKS_PER_SEC) << " mb/s)";
        return 0;
    } else if (mode == "-d") {
        std::cerr << "Decompressing \"" + src + "\" in \""+ dst + "\" ...\n";
        start = clock();
        try {
            file_decompressor decompressor(src);
            file_size = decompressor.file_bytes_cnt();
            decompressor.decompress(dst);
        } catch (std::runtime_error &e) {
            std::cerr << "Unable to decompress: ";
            std::cerr << e.what();
            return -1;
        }
        finish = clock();
        std::cerr << "Successfully decompressed " << double(file_size) / (1 << 20)
                  << " mb in " + std::to_string((finish - start) * 1000 / CLOCKS_PER_SEC) + " ms ("
                  << double(file_size) / (1 << 20) / (double(finish - start) / CLOCKS_PER_SEC) << " mb/s)";
        return 0;

    } else {
        std::cerr << "Incorrect mode. Expected -c (compress) or -d (decompress)";
        return -1;
    }
}