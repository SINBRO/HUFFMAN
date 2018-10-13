//
// Created by andrey on 06.10.18.
//

#include <queue>
#include "h/code_tree.h"

code_tree::code_tree(size_t *freq) {
    struct node_cmp {
        bool operator()(node* lhs, node* rhs ) const {
            return lhs->cnt < rhs->cnt;
        }
    };
    auto queue = std::priority_queue<node*, std::vector<node*>, node_cmp>();
    for (size_t i = 0; i < SYMBOL_CNT; ++i) {
        if (freq[i] != 0) {
            queue.push(new node(static_cast<uint16_t>(i), freq[i]));
        }
    }
    node *node1, *node2;
    while (queue.size() > 1) {
        node1 = queue.top();
        queue.pop();
        node2 = queue.top();
        queue.pop();
        queue.push(new node(node1, node2, NONE, node1->cnt + node2->cnt));
    }
    head = *queue.top();
}

code_tree::code_tree(std::vector<std::pair<int32_t, int32_t>> &init_data) {
    
}

symbol code_tree::decode(uint64_t code_piece) {
    node* x = &head;
    code_pos = 0;
    while (x->sym == NONE) {
        x = x->child[1 & (code_piece >> code_pos++)];
    }
    return static_cast<symbol>(x->sym);
}

code_tree::node code_tree::make_node(std::vector<std::pair<int32_t, int32_t>> &init_data, size_t i) {

    return code_tree::node();
}

std::vector<std::pair<int32_t, int32_t>> code_tree::convert() {
    auto res = std::vector<std::pair<int32_t, int32_t>>();
    convert_dfs(res, &head);
    return res;
}

int32_t code_tree::convert_dfs(std::vector<std::pair<int32_t, int32_t>> v, code_tree::node *x) {
    int32_t l, r;
    if (x->sym == NONE) {
        l = convert_dfs(v, x->child[0]);
        r = convert_dfs(v, x->child[1]);
    } else {
        l = -1;
        r = x->sym;
    }
    v.emplace_back(l, r);
    return static_cast<int32_t>(v.size() - 1);
}
