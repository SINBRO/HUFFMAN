//
// Created by andrey on 11.10.18.
//

#include "h/file_writer.h"

file_writer::file_writer() : cur_symbol(0) {}

file_writer::file_writer(std::string const &dst) : out(dst, std::ofstream::binary), cur_symbol(0) {
    if (out.fail()) {
        out.close();
        throw std::runtime_error("Unable to create file " + dst);
    }
}

void file_writer::set_file(std::string const &dst) {
    out = std::ofstream(dst, std::ofstream::binary);
    if (out.fail()) {
        out.close();
        throw std::runtime_error("Unable to create file " + dst);
    }
}

void file_writer::print(symbol s) {
    if (cur_symbol == BUFFER_SIZE) {
        out.write(reinterpret_cast<const char *>(buffer), BUFFER_SIZE);
        cur_symbol = 0;
    }
    buffer[cur_symbol++] = s;
}

void file_writer::print_code_block(std::vector<code> block) {

}

file_writer::~file_writer() {
    out.write(reinterpret_cast<const char *>(buffer), BUFFER_SIZE);
    out.close();
}
