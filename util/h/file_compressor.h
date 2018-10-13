//
// Created by andrey on 11.10.18.
//

#ifndef HUFFMAN_FILE_COMPRESSOR_H
#define HUFFMAN_FILE_COMPRESSOR_H

#include "../../lib/h/types_consts.h"
#include "../../lib/h/code_tree.h"
#include "file_reader.h"
#include "file_writer.h"
#include "../../lib/h/data_compressor.h"
#include <string>

struct file_compressor {
    file_compressor() = delete;

    explicit file_compressor(std::string const &file_name);

    void compress(std::string dst);

private:
    size_t *count_symbols();

    file_reader reader;
    file_writer writer;
    data_compressor compressor;
};


#endif //HUFFMAN_FILE_COMPRESSOR_H