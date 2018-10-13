//
// Created by andrey on 06.10.18.
//

#ifndef HUFFMAN_CODE_TREE_H
#define HUFFMAN_CODE_TREE_H


#include "types_consts.h"
#include "code.h"
#include <vector>
#include <cstdint>

struct code_tree {
    code_tree() = default;

    explicit code_tree(size_t *freq); // SYMBOL_CNT elements

    //code_tree(...) CONSTRUCTOR TO READ A TREE

    symbol decode(uint64_t code_piece);

    struct node {
        uint16_t sym;
        node* child[2];
        size_t cnt = 0;

        node() : child(), sym(NONE) {
            child[0] = nullptr;
            child[1] = nullptr;
        };

        explicit node(uint16_t s) : child(), sym(s) {
            child[0] = nullptr;
            child[1] = nullptr;
        };

        node(uint16_t s, size_t count) : child(), sym(s), cnt(count) {
            child[0] = nullptr;
            child[1] = nullptr;
        };

        node(node* ch1, node* ch2) : child(), sym(NONE) {
            child[0] = ch1;
            child[1] = ch2;
        };

        node(node* ch1, node* ch2, uint16_t s) : child(), sym(s) {
            child[0] = ch1;
            child[1] = ch2;
        };

        node(node* ch1, node* ch2, uint16_t s, size_t count) : child(), sym(s), cnt(count) {
            child[0] = ch1;
            child[1] = ch2;
        };
    };

    uint8_t code_pos = 0;

private:

    node head;
};


#endif //HUFFMAN_CODE_TREE_H
