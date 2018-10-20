//
// Created by andrey on 06.10.18.
//

#include <queue>
#include "h/code_tree.h"

code_tree::code_tree(std::unique_ptr<size_t[]> &freq) {
    struct node_cmp {
        bool operator()(node *lhs, node *rhs) const {
            return lhs->cnt < rhs->cnt;
        }
    };

    auto queue = std::priority_queue<node *, std::vector<node *>, node_cmp>();

    for (size_t i = 0; i < SYMBOL_CNT; ++i) {
        if (freq[i] != 0) {
            queue.push(new node(static_cast<uint16_t>(i), freq[i]));
        }
    }
    node const *node1, *node2;
    while (queue.size() > 1) {
        node1 = queue.top();
        queue.pop();
        node2 = queue.top();
        queue.pop();
        queue.push(new node(node1, node2, NONE, node1->cnt + node2->cnt));
    }
    head = queue.top();
}

code_tree::code_tree(std::vector<std::pair<int32_t, int32_t>> &init_data) {
    head = make_node(init_data, init_data.size() - 1);
}

symbol code_tree::decode(uint64_t code_piece) {
    node const *x = head;
    code_pos = 0;
    while (x->sym == NONE) {
        x = x->child[static_cast<uint32_t>(1) & (code_piece >> code_pos++)];
    }
    return static_cast<symbol>(x->sym);
}

code_tree::node *
code_tree::make_node(std::vector<std::pair<int32_t, int32_t>> &init_data, size_t i) { //!!! MB INFINITE RECURSION
    node *res, *ch1, *ch2;
    if (init_data[i].first == -1) {
        res = new node(static_cast<uint16_t>(init_data[i].first));
    } else {
        ch1 = make_node(init_data, static_cast<size_t>(init_data[i].first));
        ch2 = make_node(init_data, static_cast<size_t>(init_data[i].second));
        res = new node(ch1, ch2, NONE);
    }
    return res;
}

std::vector<std::pair<int32_t, int32_t>> code_tree::convert() {
    auto res = std::vector<std::pair<int32_t, int32_t>>();
    convert_dfs(res, head);
    return res;
}

int32_t code_tree::convert_dfs(std::vector<std::pair<int32_t, int32_t>> &v, code_tree::node const *x) {
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

void code_tree::fill_codes(code *codes) {
    fill_codes(codes, head, code());
}

void code_tree::fill_codes(code *codes, const code_tree::node *x, code c) {
    if (x->sym != NONE) {
        codes[x->sym] = c;
    } else {
        fill_codes(codes, x->child[0], c.add_bit(false));
        fill_codes(codes, x->child[1], c.add_bit(true));
    }
}

code_tree::~code_tree() {
    delete head;
}
