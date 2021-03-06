//
// Created by andrey on 11.10.18.
//

#ifndef HUFFMAN_FILE_DECOMPRESSOR_H
#define HUFFMAN_FILE_DECOMPRESSOR_H

#include "../../lib/h/data_decompressor.h"
#include "file_reader.h"
#include "file_writer.h"

struct file_decompressor {

    file_decompressor() = delete;

    explicit file_decompressor(std::string const &file_name);

    void decompress(std::string const &dst);

    uint64_t file_bytes_cnt();

private:
    uint64_t symbols_in_file = 0;
    data_decompressor decompressor;
    file_reader reader;
    file_writer writer;
};

void decompress(std::string const &src, std::string const &dst);


#endif //HUFFMAN_FILE_DECOMPRESSOR_H
