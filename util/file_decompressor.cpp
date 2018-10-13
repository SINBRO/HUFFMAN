//
// Created by andrey on 11.10.18.
//

#include "h/file_decompressor.h"

file_decompressor::file_decompressor(std::string file_name) : reader(file_name) {

    try {

    } catch (...) {
        throw std::runtime_error("Unable to get code tree");
    }

}

void file_decompressor::decompress(std::string dst) {
    writer.set_file(dst);

}
