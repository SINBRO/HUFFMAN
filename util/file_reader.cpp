//
// Created by andrey on 11.10.18.
//

#include <iostream>
#include "h/file_reader.h"

file_reader::file_reader(std::string const &file_name) : in(file_name, std::ifstream::binary),
                                                         file(file_name), res(0), cur_symbol(0), s_in_buff(0),
                                                         cur_code_piece(0), useful_bits(0) {
    if (in.fail()) {
        in.close();
        throw std::runtime_error("Unable to open file \"" + file_name + "\"");
    }
    upload();
}


symbol file_reader::get_symbol() {
    res = buffer[cur_symbol++];
    upload();
    return res;
}

void file_reader::restart() {
    in.close();
    in.open(file);
    cur_symbol = s_in_buff = 0;
    if (in.fail()) {
        in.close();
        throw std::runtime_error("Lost access to file \"" + file + "\"\n");
    }
}

bool file_reader::eof() const {
    return cur_symbol >= s_in_buff && in.eof();
}

void file_reader::upload() {
    if (cur_symbol >= s_in_buff) {
        in.read(reinterpret_cast<char *>(buffer), BUFFER_SIZE * sizeof(symbol) / sizeof(char));
        cur_symbol = 0;
        s_in_buff = static_cast<uint64_t>(in.gcount()) * sizeof(char) / sizeof(symbol);

        if (s_in_buff == 0) {
            in.read(reinterpret_cast<char *>(buffer), BUFFER_SIZE * sizeof(symbol) / sizeof(char));
            s_in_buff = static_cast<uint64_t>(in.gcount()) * sizeof(char) / sizeof(symbol);
        }
    }
}

std::pair<symbol const *, uint64_t> file_reader::get_block() {
    upload();
    auto res = std::pair<symbol const *, uint64_t>(buffer + cur_symbol, s_in_buff - cur_symbol);
    cur_symbol = s_in_buff;

    return res;
}

uint64_t file_reader::get_n_bytes(uint8_t n) { // correct n <= 8
    uint64_t res = 0;
    for (uint8_t i = 0; i != n; ++i) {
        res = (res << 8) | get_symbol();
    }
    return res;
}

uint64_t file_reader::get_n_bytes_r(uint8_t n) {
    uint64_t res = 0;
    for (uint8_t i = 0; i != n * 8; i += 8) {
        res |= static_cast<uint64_t>(get_symbol()) << (i);
    }
    return res;
}

void file_reader::make_n_bits_used(int8_t n) {
    cur_code_piece >>= n;
    useful_bits -= n;
}

uint64_t file_reader::get_next_code_piece() {
    refill_useful_bits();
    return cur_code_piece; //  last 7 bits can be wrong, but 57 bits is enough
}

inline void file_reader::refill_useful_bits() {
    while ((useful_bits <= static_cast<uint8_t>(64 - sizeof(symbol) * 8)) && !eof()) {
        cur_code_piece += static_cast<uint64_t>(get_symbol()) << useful_bits;
        useful_bits += sizeof(symbol) * 8;
    }
}

bool file_reader::has_useful_bits() const {
    return useful_bits > 0;
}

file_reader::~file_reader() {
    in.close();
}
