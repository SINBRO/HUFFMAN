//
// Created by andrey on 11.10.18.
//

#include "h/file_reader.h"

file_reader::file_reader(std::string const &file_name) : in(file_name, std::ifstream::binary),
                                                         file(file_name), cur_symbol(0), s_in_buff(0) {
    if (in.fail()) {
        in.close();
        throw std::runtime_error("Unable to open file " + file_name);
    }
}

symbol file_reader::get_symbol() {
    if (cur_symbol == s_in_buff) {
        in.read(reinterpret_cast<char *>(buffer), BUFFER_SIZE);
        cur_symbol = 0;
        s_in_buff = static_cast<size_t>(in.gcount());
    }
    return buffer[cur_symbol++];
}

void file_reader::restart() {
    in.close();
    in.open(file);
    if (in.fail()) {
        in.close();
        throw std::runtime_error("Lost access to file " + file);
    }
}

bool file_reader::eof() {
    return cur_symbol == s_in_buff && in.eof();
}

std::pair<symbol *, size_t> file_reader::get_block() {
    auto res = std::pair<symbol *, size_t>(&buffer[cur_symbol], s_in_buff - cur_symbol);
    in.read(reinterpret_cast<char *>(buffer), BUFFER_SIZE);
    cur_symbol = 0;
    s_in_buff = static_cast<size_t>(in.gcount());
    return res;
}

uint64_t file_reader::get_n_bytes(uint8_t n) { // effective n <= 8
    uint64_t res = 0;
    for (int i = 0; i < n; ++i) {
        res <<= 8;
        res += get_symbol();
    }
    return res;
}

void file_reader::make_n_bits_used(int8_t n) {
    cur_code_piece >>= n;
    useful_bits -= n;  // should not be < 0
    refill_useful_bits();
}

uint64_t file_reader::get_next_code_piece() {
    refill_useful_bits();
    return cur_code_piece; //  last 7 bits can be wrong, but 57 bits is enough
}

inline void file_reader::refill_useful_bits() {
    while (useful_bits <= static_cast<uint8_t>(64 - sizeof(symbol) * 8)) {
        cur_code_piece <<= sizeof(symbol) * 8;
        cur_code_piece += get_symbol();
        useful_bits += sizeof(symbol) * 8;
    }
}
