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

    friend ostream &operator<<(ostream &os, const Music *m);

    friend ostream &operator<<(ostream &os, const Music &m);

public:
    Music(string filepath, const string &filename);

    ~Music();

    string getFilepath();

    string getFilename();

    string getSuffix();

    string getAuthor();

    bool operator>(const Music &m) const;

    bool operator<(const Music &m) const;

    bool operator==(const Music &m) const;
};

#endif //MUSIC_HPP
