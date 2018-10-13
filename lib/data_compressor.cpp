//
// Created by andrey on 13.10.18.
//

#include "h/data_compressor.h"

data_compressor::data_compressor(size_t *freq) : tree(freq) {

}

std::vector<code> data_compressor::compress(symbol *data, size_t cnt) {
    auto res = *new std::vector<code>();
    res.reserve(cnt);
    for (int i = 0; i < cnt; ++i) {
        res.push_back(codes[data[i]]);
    }
    return res;
}
