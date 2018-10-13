//
// Created by andrey on 11.10.18.
//

#ifndef HUFFMAN_FILE_READER_H
#define HUFFMAN_FILE_READER_H

#include "../../lib/h/types_consts.h"
#include <string>
#include <fstream>

struct file_reader {
    file_reader() = delete;

    explicit file_reader(std::string const &file_name);

    void restart();

    symbol get_symbol();

    uint64_t get_n_bytes(uint8_t n);

    std::pair<symbol*, size_t> get_block();

    bool eof();

private:
    std::ifstream in;
    std::string file;
    symbol buffer[BUFFER_SIZE];
    size_t cur_symbol;
    size_t s_in_buff;
};


#endif //HUFFMAN_FILE_READER_H
