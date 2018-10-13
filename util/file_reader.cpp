//
// Created by andrey on 11.10.18.
//

#include "h/file_reader.h"

file_reader::file_reader(std::string const &file_name) : in(file_name, std::ifstream::binary),
                                                         cur_symbol(0), s_in_buff(0), file(file_name) {
    if (in.fail()) {
        in.close();
        throw std::runtime_error("Unable to open file " + file_name);
    }
}

symbol file_reader::get_symbol() {
    if (cur_symbol == s_in_buff) {
        in.read(reinterpret_cast<char *>(buffer), BUFFER_SIZE);
        cur_symbol = 0;
        s_in_buff = static_cast<size_t>(in.gcount());
    }
    return buffer[cur_symbol++];
}

void file_reader::restart() {
    in.close();
    in.open(file);
    if (in.fail()) {
        in.close();
        throw std::runtime_error("Lost access to file " + file);
    }
}

bool file_reader::eof() {
    return cur_symbol == s_in_buff && in.eof();
}

std::pair<symbol *, size_t> file_reader::get_block() {
    auto res = std::pair<symbol *, size_t>(&buffer[cur_symbol], s_in_buff - cur_symbol);
    in.read(reinterpret_cast<char *>(buffer), BUFFER_SIZE);
    cur_symbol = 0;
    s_in_buff = static_cast<size_t>(in.gcount());
    return res;
}
