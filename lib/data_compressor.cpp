//
// Created by andrey on 13.10.18.
//

#include "h/data_compressor.h"

data_compressor::data_compressor(std::unique_ptr<uint64_t[]> freq) : tree(freq) {
    tree.fill_codes(codes);
}

std::vector<code> data_compressor::compress(std::pair<symbol const *, uint64_t> const &block) {
    auto res = std::vector<code>();
    res.reserve(block.second);
    for (uint64_t i = 0; i != block.second; ++i) {
        res.push_back(codes[block.first[i]]);
    }
    return res;
}

