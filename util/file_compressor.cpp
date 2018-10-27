//
// Created by andrey on 11.10.18.
//

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

    std::pair<symbol const *, size_t> block;

    for (uint64_t j = 0; j < symbols_in_file; ++j) {
        block = reader.get_block();
        writer.print_code_block(compressor.compress(block));
    }
}

std::unique_ptr<size_t[]> file_compressor::count_symbols() {
    std::unique_ptr<size_t[]> res(new size_t[SYMBOL_CNT]);
    //memset(res.get(), 0, SYMBOL_CNT * sizeof(size_t));
    for (size_t i = 0; i < SYMBOL_CNT; ++i) {
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

void file_compressor::compress(std::string const &src, std::string const &dst) {
    file_compressor compressor(src);
    compressor.compress(dst);
}

uint64_t file_compressor::file_bytes_cnt() {
    return symbols_in_file * sizeof(symbol);
}
