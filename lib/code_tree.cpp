//
// Created by andrey on 06.10.18.
//

#include <queue>
#include "h/code_tree.h"

code_tree::code_tree() {
    decode_num = &code_tree::decode_by_tree;
}

code_tree::code_tree(std::unique_ptr<uint64_t[]> &freq) {
    decode_num = &code_tree::decode_by_tree;
    struct node_cmp {
        bool operator()(node *lhs, node *rhs) const {
            return lhs->cnt > rhs->cnt;
        }
    };

    auto queue = std::priority_queue<node *, std::vector<node *>, node_cmp>();

    for (uint64_t i = 0; i < SYMBOL_CNT; ++i) {
        if (freq[i] != 0) {
            queue.push(new node(static_cast<uint16_t>(i), freq[i]));
        }
    }
    if (queue.empty()) {
        head = new node(0);
        return;
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

code_tree::code_tree(std::vector<std::pair<int32_t, int32_t>> const &init_data) {
    decode_num = &code_tree::decode_by_tree;
    size_t recursion = 0;
    try {
        head = make_node(init_data, init_data.size() - 1, recursion);
    } catch (...) {
        throw std::runtime_error("Compressed file is incorrect or damaged (unable to get correct code tree)");
    }
}

symbol code_tree::decode_by_tree(uint64_t code_piece) {
    node const *x = head;
    code_pos = 0;
    while (x->sym == NONE) {
        x = x->child[static_cast<uint32_t>(1) & (code_piece >> code_pos++)];
    }
    return static_cast<symbol>(x->sym);
}

code_tree::node *
code_tree::make_node(std::vector<std::pair<int32_t, int32_t>> const &init_data,
                     uint64_t i, size_t &recursion_deepness) {
    node *res, *ch1, *ch2;
    recursion_deepness++;
    if (recursion_deepness > 4 * SYMBOL_CNT) {
        throw std::runtime_error("Compressed file is incorrect or damaged (unable to get correct code tree)");
    }
    if (init_data[i].second == -1) {
        res = new node(static_cast<uint16_t>(init_data[i].first));
    } else {
        ch1 = make_node(init_data, static_cast<uint64_t>(init_data[i].first), recursion_deepness);
        ch2 = make_node(init_data, static_cast<uint64_t>(init_data[i].second), recursion_deepness);
        res = new node(ch2, ch1);
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

void code_tree::fill_codes(code codes[SYMBOL_CNT]) {
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
    delete[] cheat_table;
}

symbol code_tree::decode_by_table(uint64_t code_piece) {
    if ((code_pos = cheat_table[static_cast<uint16_t>(code_piece)].second) > MAX_CODE_LENGTH) {
        return decode_by_tree(code_piece);
    }
    return cheat_table[static_cast<uint16_t>(code_piece)].first;
}

symbol code_tree::decode_by_table_only(uint64_t code_piece) {
    code_pos = cheat_table[static_cast<uint16_t>(code_piece)].second;
    return cheat_table[static_cast<uint16_t>(code_piece)].first;
}

bool code_tree::in_table_mode() {
    return decode_num == &code_tree::decode_by_table;
}

bool code_tree::in_tree_mode() {
    return decode_num == &code_tree::decode_by_tree;
}

void code_tree::switch_to_tree_mode() {
    if (in_table_mode()) {
        decode_num = &code_tree::decode_by_tree;
    }
}

void code_tree::switch_to_table_mode() {
    if (in_tree_mode()) {
        uint8_t max_code_length = 0;
        if (cheat_table == nullptr) {
            cheat_table = new std::pair<symbol, uint8_t>[CHEAT_TABLE_LENGTH];
            for (uint64_t i = 0; i < CHEAT_TABLE_LENGTH; ++i) {
                cheat_table[i].first = decode_by_tree(i);
                cheat_table[i].second = code_pos;
                max_code_length = std::max(max_code_length, code_pos);
            }
        }
        if (max_code_length <= MAX_CODE_LENGTH) {
            decode_num = &code_tree::decode_by_table_only;
        } else {
            decode_num = &code_tree::decode_by_table;
        }
    }
}
