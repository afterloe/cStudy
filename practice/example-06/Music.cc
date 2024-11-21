//
// Created by afterloe on 2024/11/20.
//

#include "include/Music.hpp"

string Music::getFilepath() {
    return filepath;
}

Music::Music(string filepath, const string &filename) {
    this->filepath = std::move(filepath);
    string::size_type lastFlag = filename.find_last_of('.');
    this->suffix = filename.substr(lastFlag + 1);
    this->filename = filename.substr(0, lastFlag);
    lastFlag = this->filename.find_last_of('-');
    this->author = this->filename.substr(0, lastFlag);
    this->filename = this->filename.substr(lastFlag + 1);
}

Music::~Music() = default;
