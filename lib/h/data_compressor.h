//
// Created by andrey on 13.10.18.
//

#ifndef HUFFMAN_DATA_COMPRESSOR_H
#define HUFFMAN_DATA_COMPRESSOR_H

#include "code_tree.h"

struct data_compressor {
    data_compressor() = delete;

    //~data_compressor();

    explicit data_compressor(std::unique_ptr<size_t[]> freq); // SYMBOL_CNT elements

    std::vector<code> compress(std::pair<symbol const *, size_t> const &);

    code_tree tree;
private:
    code codes[SYMBOL_CNT];
};


#endif //HUFFMAN_DATA_COMPRESSOR_H
