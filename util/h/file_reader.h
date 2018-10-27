//
// Created by andrey on 11.10.18.
//

#ifndef HUFFMAN_FILE_READER_H
#define HUFFMAN_FILE_READER_H

#include "../../lib/h/types_consts.h"
#include <fstream>

struct file_reader {
    file_reader() = delete;

    explicit file_reader(std::string const &file_name);

    void restart();

    void upload();

    symbol get_symbol();

    uint64_t get_n_bytes(uint8_t n);

    uint64_t get_n_bytes_r(uint8_t n);

    uint64_t get_next_code_piece();

    void make_n_bits_used(int8_t n);

    std::pair<symbol const *, uint64_t> get_block();

    bool eof() const;

    bool has_useful_bits() const;

private:
    void refill_useful_bits();

    std::ifstream in;
    std::string file;
    symbol buffer[BUFFER_SIZE];
    uint64_t cur_symbol = 0;
    uint64_t s_in_buff = 0;
    uint64_t cur_code_piece = 0;
    int8_t useful_bits = 0;
};


#endif //HUFFMAN_FILE_READER_H
