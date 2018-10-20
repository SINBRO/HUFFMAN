//
// Created by andrey on 11.10.18.
//

#include "h/file_compressor.h"
#include <cstring>

file_compressor::file_compressor(std::string const &file_name) : reader(file_name), compressor(
        count_symbols()) {
}

void file_compressor::compress(std::string dst) {
    writer.set_file(dst);

    auto converted_tree = compressor.tree.convert();

    writer.print_number(static_cast<int32_t>(converted_tree.size()));

    for (auto &i : converted_tree) {
        writer.print_number(i.first);
        writer.print_number(i.second);
    }                                       // TREE PRINTED

    std::pair<symbol const *, size_t> block;

    while (!reader.eof()) {
        block = reader.get_block();
        writer.print_code_block(compressor.compress(block.first, block.second));
    }
}

std::unique_ptr<size_t[]> file_compressor::count_symbols() {
    std::unique_ptr<size_t[]> res(new size_t[SYMBOL_CNT]);
    //memset(res.get(), 0, SYMBOL_CNT * sizeof(size_t));
    for (size_t i = 0; i < SYMBOL_CNT; ++i) {
        res[i] = 0;
    }
    while (!reader.eof()) {
        ++res[reader.get_symbol()];
    }

    reader.restart();
    return res;
}
