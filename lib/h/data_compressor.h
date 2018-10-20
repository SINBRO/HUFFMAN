//
// Created by andrey on 13.10.18.
//

#ifndef HUFFMAN_DATA_COMPRESSOR_H
#define HUFFMAN_DATA_COMPRESSOR_H

#include "types_consts.h"
#include "code_tree.h"
#include "code.h"

struct data_compressor {
    data_compressor() = delete;

    //~data_compressor();

    explicit data_compressor(std::unique_ptr<size_t[]> freq); // SYMBOL_CNT elements

    std::vector<code> compress(symbol const *data, size_t cnt);

    code_tree tree;
private:
    code codes[SYMBOL_CNT];
};


#endif //HUFFMAN_DATA_COMPRESSOR_H
