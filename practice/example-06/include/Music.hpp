//
// Created by afterloe on 2024/11/20.
//

#ifndef MUSIC_HPP
#define MUSIC_HPP

#include <iostream>

using namespace std;

class Music {
    string filepath;
    string filename;
    string suffix;
    string author;

    // friend ostream& operator<<(ostream& os, const Music& m);

public:
    Music(string filepath, const string &filename);

    ~Music();

    string getFilepath();

    // bool operator>(const Music& m);
    // bool operator<(const Music& m);
    // bool operator== (const Music& m);

    bool operator<(const Music &m) const {
        return this->filepath < m.filepath;
    }

    bool operator>(const Music &m) const {
        return this->filepath > m.filepath;
    }

    bool operator==(const Music &m) const {
        return this->filepath == m.filepath;
    }

    friend ostream &operator<<(ostream &os, const Music *m) {
        os << "[name: " << m->filename << " ,author: " << m->author;
        os << " ,filepath: " + m->filepath + "]" << endl;
        return os;
    }
};

#endif //MUSIC_HPP
