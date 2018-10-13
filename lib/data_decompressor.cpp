//
// Created by andrey on 13.10.18.
//

#include "h/data_decompressor.h"

data_decompressor::data_decompressor() {

}

void data_decompressor::set_tree(code_tree another_tree) {
    tree = another_tree;
}

symbol data_decompressor::decode(uint64_t code_piece) {
    return tree.decode(code_piece); // code_pos in tree
}
