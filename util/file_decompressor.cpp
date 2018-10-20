//
// Created by andrey on 11.10.18.
//

#include "h/file_decompressor.h"

file_decompressor::file_decompressor(std::string file_name) : reader(file_name) {
    try {
        auto converted_tree_size = static_cast<uint32_t>(reader.get_n_bytes(4));
        if (converted_tree_size > SYMBOL_CNT*4) {
            throw;
        }
        auto converted_tree = std::vector<std::pair<int32_t, int32_t>>();
        for (uint32_t i = 0; i < converted_tree_size; ++i) {
            converted_tree.emplace_back(static_cast<int32_t>(reader.get_n_bytes(4)), static_cast<int32_t>(reader.get_n_bytes(4)));
        }
        decompressor.set_tree(new code_tree(converted_tree));
    } catch (...) {
        throw std::runtime_error("Compressed file is incorrect or damaged (unable to get correct code tree)");
    }
}

void file_decompressor::decompress(std::string dst) {
    writer.set_file(dst);
    while (!reader.eof()) {
        writer.print(decompressor.decode(reader.get_next_code_piece()));
        reader.make_n_bits_used(decompressor.code_pos()); // code_pos() seems to be ok
    }
}
