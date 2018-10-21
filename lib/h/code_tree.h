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
    code_tree();

    explicit code_tree(std::unique_ptr<size_t[]> &freq); // SYMBOL_CNT elements

    explicit code_tree(std::vector<std::pair<int32_t, int32_t>> &init_data);

    ~code_tree();

    symbol decode_by_tree(uint64_t code_piece);

    symbol decode_by_table(uint64_t code_piece);

    void fill_codes(code codes[SYMBOL_CNT]);

    typedef symbol (code_tree::*Decode) (uint64_t);

    bool in_table_mode();

    bool in_tree_mode();

    void switch_to_table_mode();

    void switch_to_tree_mode();

    Decode decode_num;

    std::vector<std::pair<int32_t, int32_t>> convert();

    struct node {
        uint16_t sym;
        node const *child[2];
        size_t cnt = 0;

        node() : sym(NONE), child{nullptr, nullptr} {};

        explicit node(uint16_t s) : sym(s), child{nullptr, nullptr} {};

        node(uint16_t s, size_t count) : sym(s), child{nullptr, nullptr}, cnt(count) {};

        node(node const *ch1, node const *ch2) : sym(NONE), child{ch1, ch2} {};

        node(node const *ch1, node const *ch2, uint16_t s, size_t count) : sym(s), child{ch1, ch2}, cnt(count) {};

        ~node() {
            if (sym == NONE) {
                delete child[0];
                delete child[1];
            }
        }
    };


    uint8_t code_pos = 0;

private:
    int32_t convert_dfs(std::vector<std::pair<int32_t, int32_t>> &v, node const *x);

    node *make_node(std::vector<std::pair<int32_t, int32_t>> &init_data, size_t i);

    void fill_codes(code codes[SYMBOL_CNT], node const *x, code c);

    std::pair<symbol, uint8_t> * cheat_table = nullptr;

    node *head = nullptr;
};


#endif //HUFFMAN_CODE_TREE_H
