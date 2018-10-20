//
// Created by andrey on 13.10.18.
//

#include "h/code.h"

code::code(uint64_t c, uint8_t b) : value(c), bits(b) {

}

code code::add_bit(bool val) const {
    code res = *this;
    res.value |= (static_cast<uint64_t>(val) << res.bits++);
    return res;
}

code::code() : value(0), bits(0) {

}
