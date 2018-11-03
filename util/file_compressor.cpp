//
// Created by andrey on 11.10.18.
//

#include <iostream>
#include "h/file_compressor.h"

file_compressor::file_compressor(std::string const &file_name) : reader(file_name), compressor(
        count_symbols()) {
}

void file_compressor::compress(std::string const &dst) {
    writer.set_file(dst);

    auto converted_tree = compressor.tree.convert();

    writer.print_n_bytes(8, symbols_in_file);
    writer.print_number(static_cast<int32_t>(converted_tree.size()));

    for (auto &i : converted_tree) {
        writer.print_number(i.first);
        writer.print_number(i.second);
    }                                       // TREE PRINTED

    while (!reader.eof()) {
        writer.print_code_block(compressor.compress(reader.get_block()));
    }

    writer.flush();
}

std::unique_ptr<uint64_t[]> file_compressor::count_symbols() {
    std::unique_ptr<uint64_t[]> res(new uint64_t[SYMBOL_CNT]);
    for (uint64_t i = 0; i < SYMBOL_CNT; ++i) {
        res[i] = 0;
    }
    reader.upload();
    while (!reader.eof()) {
        ++res[reader.get_symbol()];
        ++symbols_in_file;
    }

    reader.restart();
    return res;
}

void compress(std::string const &src, std::string const &dst) {
    {
        file_compressor compressor(src);
        compressor.compress(dst);
    }
}

uint64_t file_compressor::file_bytes_cnt() {
    return symbols_in_file * sizeof(symbol);
}
