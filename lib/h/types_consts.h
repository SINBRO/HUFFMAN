//
// Created by andrey on 06.10.18.
//

#pragma once

#ifndef HUFFMAN_TYPES_CONSTS_H
#define HUFFMAN_TYPES_CONSTS_H

#include <memory>

typedef uint8_t symbol;

const uint8_t MAX_CODE_LENGTH = 16;
const uint64_t CHEAT_TABLE_LENGTH = 1 << MAX_CODE_LENGTH;
const uint64_t SYMBOL_CNT = (uint64_t) 1 << static_cast<uint8_t>(sizeof(symbol) * 8);
const uint16_t NONE = UINT16_MAX;
const uint64_t BUFFER_SIZE = (uint64_t) 1 << static_cast<uint8_t>(10);
const uint64_t SYMBOLS_TO_SWITCH = 2 << 1;

#endif //HUFFMAN_TYPES_CONSTS_H
