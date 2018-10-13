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

    explicit code_tree(std::vector<std::pair<int32_t, int32_t>> &init_data);

    symbol decode(uint64_t code_piece);

    std::vector<std::pair<int32_t, int32_t>> convert();

    struct node {
        uint16_t sym;
        node *child[2];
        size_t cnt = 0;

        node() : sym(NONE), child() {
            child[0] = nullptr;
            child[1] = nullptr;
        };

        explicit node(uint16_t s) : sym(s), child() {
            child[0] = nullptr;
            child[1] = nullptr;
        };

        node(uint16_t s, size_t count) : sym(s), child(), cnt(count) {
            child[0] = nullptr;
            child[1] = nullptr;
        };

        node(node *ch1, node *ch2) : sym(NONE), child() {
            child[0] = ch1;
            child[1] = ch2;
        };

        node(node *ch1, node *ch2, uint16_t s) : sym(s), child() {
            child[0] = ch1;
            child[1] = ch2;
        };

        node(node *ch1, node *ch2, uint16_t s, size_t count) : sym(s), child(), cnt(count) {
            child[0] = ch1;
            child[1] = ch2;
        };
    };

    uint8_t code_pos = 0;

private:
    int32_t convert_dfs(std::vector<std::pair<int32_t, int32_t>> v, node *x);
    node* make_node(std::vector<std::pair<int32_t, int32_t>> &init_data, size_t i);

    node head;
};


#endif //HUFFMAN_CODE_TREE_H
