//
// Created by andrey on 06.10.18.
//

#ifndef HUFFMAN_TYPES_CONSTS_H
#define HUFFMAN_TYPES_CONSTS_H

#include <cstdlib>
#include <cstdint>
#include <memory>

// for debug:
#include <iostream>

using std::cout;
//

typedef uint8_t symbol;

const symbol SYMBOL_MAX_VALUE = UINT8_MAX;
const size_t SYMBOL_CNT = (size_t) 1 << static_cast<uint8_t>(sizeof(symbol) * 8);
const uint16_t NONE = UINT16_MAX;
const size_t BUFFER_SIZE = (size_t) 1 << static_cast<uint8_t>(10);
const int16_t TOO_SHORT_CODE = -1;


#endif //HUFFMAN_TYPES_CONSTS_H
