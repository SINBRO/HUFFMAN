//
// Created by andrey on 11.10.18.
//

#ifndef HUFFMAN_FILE_DECOMPRESSOR_H
#define HUFFMAN_FILE_DECOMPRESSOR_H


#include <string>
#include "file_reader.h"
#include "file_writer.h"
#include "../../lib/h/data_decompressor.h"

struct file_decompressor {
    file_decompressor() = delete;

    explicit file_decompressor(std::string file_name);

    void decompress(std::string dst);

private:
    size_t symbols_in_file = 0;
    data_decompressor decompressor;
    file_reader reader;
    file_writer writer;
};


#endif //HUFFMAN_FILE_DECOMPRESSOR_H
