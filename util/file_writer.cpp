//
// Created by andrey on 11.10.18.
//

#include <iostream>
#include "h/file_writer.h"


file_writer::file_writer() : cur_symbol(0) {
}

file_writer::file_writer(std::string const &dst) : out(dst, std::ofstream::binary), cur_symbol(0) {
    if (out.fail()) {
        out.close();
        throw std::runtime_error("Unable to create file \"" + dst + "\"");
    }
}

void file_writer::set_file(std::string const &dst) {
    out = std::ofstream(dst, std::ofstream::binary);
    if (out.fail()) {
        out.close();
        throw std::runtime_error("Unable to create file \"" + dst + "\"");
    }
}

void file_writer::print(symbol s) {
    if (cur_symbol == BUFFER_SIZE) {
        out.write(reinterpret_cast<const char *>(buffer), BUFFER_SIZE * sizeof(symbol) / sizeof(char));
        cur_symbol = 0;
    }
    buffer[cur_symbol++] = s;
}

void file_writer::print_code(code const &x) {
    cur_part |= x.value << cur_bits;
    if (cur_bits + x.bits >= 64) {
        print_n_bytes(8, cur_part);
        cur_part = x.value >> static_cast<uint8_t >(64 - cur_bits);
        cur_bits -= 64 - x.bits; // x.bits <= 64?
    } else {
        cur_bits += x.bits;
    }
}

void file_writer::print_code_block(std::vector<code> const &block) {
    for (auto &i : block) {
        print_code(i);
    }
}

file_writer::~file_writer() {
    if (cur_bits != 0) {
        print_n_bytes(8, cur_part); //static_cast<uint8_t>((cur_bits + 7) / 8)
    }
    out.write(reinterpret_cast<const char *>(buffer), cur_symbol * sizeof(symbol) / sizeof(char));
    out.close();
}

void file_writer::print_number(int32_t x) {
    uint8_t shift = 8 * (sizeof(int32_t) - sizeof(symbol));
    for (uint8_t i = 0; i < sizeof(int32_t) / sizeof(symbol); ++i) {
        print(static_cast<symbol>(x >> shift));
        shift -= 8 * sizeof(symbol);
    }
}

void file_writer::print_n_bytes(uint8_t n, uint64_t val) {
    for (uint8_t i = 0; i != n; ++i) {
        print(static_cast<symbol>(val));
        val >>= 8 * sizeof(symbol);
    }
}

void file_writer::flush() {
    if (cur_bits != 0) {
        print_n_bytes(8, cur_part); //static_cast<uint8_t>((cur_bits + 7) / 8)
    }
    out.write(reinterpret_cast<const char *>(buffer), cur_symbol * sizeof(symbol) / sizeof(char));
    cur_symbol = 0;
}
