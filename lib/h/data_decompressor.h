//
// Created by andrey on 13.10.18.
//

#ifndef HUFFMAN_DATA_DECOMPRESSOR_H
#define HUFFMAN_DATA_DECOMPRESSOR_H

#include "code_tree.h"

struct data_decompressor {
    data_decompressor();

    ~data_decompressor();

    void set_tree(code_tree *another_tree);

    symbol decode(uint64_t code_piece); // MUST MANAGE WITH %8 BITS

    uint8_t code_pos();

    code_tree *tree;
};


#endif //HUFFMAN_DATA_DECOMPRESSOR_H
