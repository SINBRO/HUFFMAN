//
// Created by andrey on 11.10.18.
//

#include "h/file_writer.h"

file_writer::file_writer() : cur_symbol(0) {}

file_writer::file_writer(std::string const &dst) : out(dst, std::ofstream::binary), cur_symbol(0) {
    if (out.fail()) {
        out.close();
        throw std::runtime_error("Unable to create file " + dst);
    }
}

void file_writer::set_file(std::string const &dst) {
    out = std::ofstream(dst, std::ofstream::binary);
    if (out.fail()) {
        out.close();
        throw std::runtime_error("Unable to create file " + dst);
    }
}

void file_writer::print(symbol s) {
    if (cur_symbol == BUFFER_SIZE) {
        out.write(reinterpret_cast<const char *>(buffer), BUFFER_SIZE);
        cur_symbol = 0;
    }
    buffer[cur_symbol++] = s;
}

void file_writer::print_code(code x) {
    cur_part += x.value << cur_bits;
    if (cur_bits + x.bits > 64) {
        print_number(static_cast<int32_t>(cur_part));
        cur_part = x.value >> (64 - cur_bits);
        cur_bits -= 64 - x.bits;
    } else {
        cur_bits += x.bits;
    }
}

void file_writer::print_code_block(std::vector<code> block) {
    for (auto &i : block) {
        print_code(i);
    }
}

file_writer::~file_writer() {
    out.write(reinterpret_cast<const char *>(buffer), cur_symbol);
    out.close();
}

void file_writer::print_number(int32_t x) {
    for (int i = 0; i < sizeof(int32_t) / sizeof(symbol); ++i) {
        print(static_cast<symbol>(SYMBOL_MAX_VALUE & x));
        x >>= 8 * sizeof(symbol);
    }
}

