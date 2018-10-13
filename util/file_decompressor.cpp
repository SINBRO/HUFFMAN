//
// Created by andrey on 11.10.18.
//

#include "h/file_decompressor.h"

file_decompressor::file_decompressor(std::string file_name) : reader(file_name) {
    try {
        auto converted_tree_size = static_cast<uint32_t>(reader.get_n_bytes(4));
        auto converted_tree = std::vector<std::pair<int32_t, int32_t>>();
        for (int i = 0; i < converted_tree_size; ++i) {
            converted_tree.emplace_back(reader.get_n_bytes(4), reader.get_n_bytes(4));
        }
        decompressor.set_tree(code_tree(converted_tree));
    } catch (...) {
        throw std::runtime_error("Unable to get correct code tree");
    }


}

void file_decompressor::decompress(std::string dst) {
    writer.set_file(dst);

}
