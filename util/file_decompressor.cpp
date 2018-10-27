//
// Created by andrey on 11.10.18.
//

#include "h/file_decompressor.h"

file_decompressor::file_decompressor(std::string const &file_name) : reader(file_name) {
    try {
        symbols_in_file = reader.get_n_bytes_r(8);

        auto converted_tree_size = static_cast<uint32_t>(reader.get_n_bytes(4));
        if (converted_tree_size > SYMBOL_CNT * 4) {
            throw std::runtime_error("");
        }
        auto converted_tree = std::vector<std::pair<int32_t, int32_t>>();
        for (uint32_t i = 0; i < converted_tree_size; ++i) {
            converted_tree.emplace_back(static_cast<int32_t>(reader.get_n_bytes(4)),
                                        static_cast<int32_t>(reader.get_n_bytes(4)));
        }
        decompressor.set_tree(new code_tree(converted_tree));

        ///
        decompressor.tree->switch_to_table_mode();
        ///

    } catch (...) {
        throw std::runtime_error("Compressed file is incorrect or damaged (unable to get correct code tree)");
    }
}

void file_decompressor::decompress(std::string const &dst) {
    writer.set_file(dst);
    //while (!reader.eof() || reader.has_useful_bits()) {
    for (uint64_t i = 0; i < symbols_in_file; ++i) {
        writer.print(decompressor.decode(reader.get_next_code_piece()));
        reader.make_n_bits_used(decompressor.code_pos()); // code_pos() seems to be ok
    }
}

void file_decompressor::decompress(std::string const &src, std::string const &dst) {
    file_decompressor decompressor(src);
    decompressor.decompress(dst);
}

uint64_t file_decompressor::file_bytes_cnt() {
    return symbols_in_file * sizeof(symbol);
}