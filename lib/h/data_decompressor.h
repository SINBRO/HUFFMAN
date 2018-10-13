//
// Created by andrey on 13.10.18.
//

#ifndef HUFFMAN_DATA_DECOMPRESSOR_H
#define HUFFMAN_DATA_DECOMPRESSOR_H

#include "types_consts.h"
#include "code_tree.h"

struct data_decompressor {
    data_decompressor();

    void set_tree(code_tree another_tree);


private:
    code_tree tree;
};


#endif //HUFFMAN_DATA_DECOMPRESSOR_H
