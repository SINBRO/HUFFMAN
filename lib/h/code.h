//
// Created by andrey on 13.10.18.
//

#ifndef HUFFMAN_CODE_WORD_H
#define HUFFMAN_CODE_WORD_H

#include "types_consts.h"
#include <cstdint>

struct code {
    code();

    code(uint64_t c, uint8_t b);

    code add_bit(bool val) const;

    uint64_t value;
    uint8_t bits;
};


#endif //HUFFMAN_CODE_WORD_H
