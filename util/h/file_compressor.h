//
// Created by andrey on 11.10.18.
//

#ifndef HUFFMAN_FILE_COMPRESSOR_H
#define HUFFMAN_FILE_COMPRESSOR_H

#include "../../lib/h/data_compressor.h"
#include "file_reader.h"
#include "file_writer.h"

struct file_compressor {
    file_compressor() = delete;

    explicit file_compressor(std::string const &file_name);

    void compress(std::string const &dst);

    uint64_t file_bytes_cnt();

    static void compress(std::string const & src, std::string const & dst);

private:
    std::unique_ptr<size_t[]> count_symbols();

    size_t symbols_in_file = 0;
    file_reader reader;
    file_writer writer;
    data_compressor compressor;
};



#endif //HUFFMAN_FILE_COMPRESSOR_H