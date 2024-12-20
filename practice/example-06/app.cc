#include <iostream>

#include <unistd.h>
#include <sys/types.h>

#include <dirent.h>
#include "include/Music.hpp"
#include "include/BiTree.hpp"

extern "C" {
#include <libavcodec/avcodec.h>
}

using namespace std;

void readDir(const string &dirPath, BiTree::Tree &tree) {
    DIR *dir = opendir(dirPath.c_str());
    if (dir == nullptr) {
        perror("opendir");
        throw runtime_error("opendir");
    }
    const dirent *ptr = nullptr;
    while ((ptr = readdir(dir)) != nullptr) {
        string d_name = ptr->d_name;
        string filepath = dirPath + "/" + d_name;
        if (d_name == "." || d_name == "..") {
            continue;
        }
        if (ptr->d_type == DT_DIR) {
            readDir(filepath, tree);
        }
        if (ptr->d_type == DT_REG) {
            tree.Insert( new Music(filepath, d_name));
        }
    }
    closedir(dir);
}

int main(int argc, const char **argv) {
    if (argc != 2) {
        cerr << "Usage: ./app <path_to_file>" << endl;
        exit(EXIT_FAILURE);
    }

    auto *tree = new BiTree::Tree();
    const string dirpath = "/home/afterloe/音乐";
    cout << "load folder : " << dirpath << endl;
    readDir(dirpath, *tree);
    //
    // auto *result = new BiTree::Tree();
    // tree->Traverse([&](Music *music)->void {
    //     if (music->getFilepath().find("我") != string::npos) {
    //         result->Insert(music);
    //     }
    // });
    // cout << result->getSize() << endl;
    // result->Traverse([](Music *music)->void {
    //     cout << music << endl;
    // });
    //
    // delete result;
    // delete tree;

    cout << "Hello, FFmpeg " << endl;

    string config = avcodec_configuration();
    cout << "config: " << config << endl;
    string license = avcodec_license();
    cout << "license: " << license << endl;

    return EXIT_SUCCESS;
}
