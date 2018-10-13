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

symbol code_tree::decode(uint64_t code_piece) {
    node* x = &head;
    code_pos = 0;
    while (x->sym == NONE) {
        x = x->child[1 & (code_piece >> code_pos++)];
    }
    return static_cast<symbol>(x->sym);
}
