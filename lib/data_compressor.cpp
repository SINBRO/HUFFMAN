//
// Created by andrey on 13.10.18.
//

#include "h/data_compressor.h"

data_compressor::data_compressor(std::unique_ptr<size_t[]> freq) : tree(freq) {
    tree.fill_codes(codes);
}

std::vector<code> data_compressor::compress(symbol const *data, size_t cnt) {
    auto res = std::vector<code>();
    res.reserve(cnt);
    for (size_t i = 0; i < cnt; ++i) {
        res.push_back(codes[data[i]]);
    }
    return res;
}

