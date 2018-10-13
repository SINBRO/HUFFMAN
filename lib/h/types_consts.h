//
// Created by andrey on 06.10.18.
//

#ifndef HUFFMAN_TYPES_CONSTS_H
#define HUFFMAN_TYPES_CONSTS_H

#include <cstdlib>
#include <cstdint>

typedef uint8_t symbol;

const size_t SYMBOL_CNT = 1 << sizeof(symbol);
const uint16_t NONE = UINT16_MAX;
const size_t BUFFER_SIZE = 1<<10;


#endif //HUFFMAN_TYPES_CONSTS_H
