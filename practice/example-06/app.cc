#include <iostream>

#include <unistd.h>
#include "include/BiTree.hpp"

using namespace std;

//
// const string IGNORE_SUFFIX_FLAC = ".lrc";
//
//
// class MusicBiTNode {
// public:
//     string filepath;
//     string filename;
//     string suffix;
//     string author;
//
//     MusicBiTNode *lchild;
//     MusicBiTNode *rchild;
//
//     explicit MusicBiTNode(string filepath, const string& filename);
//
//     ~MusicBiTNode();
// };
//
//
// class MusicBSTree {
//     MusicBiTNode *root;
//     int size;
//
// public:
//
//     bool InsertBST(const string& filepath, const string& filename);
//
//     MusicBSTree() {
//         root = nullptr;
//         size = 0;
//     };
//
//     ~MusicBSTree();
// };
//
// MusicBiTNode::MusicBiTNode(string filepath, const string& filename): lchild(nullptr), rchild(nullptr) {
//     this->filepath = std::move(filepath);
//     string::size_type lastFlag = filename.find_last_of('.');
//     this->suffix = filename.substr(lastFlag + 1);
//     this->filename = filename.substr(0, lastFlag);
//     lastFlag = this->filename.find_last_of('-');
//     this->author = this->filename.substr(0, lastFlag);
//     this->filename = this->filename.substr(lastFlag + 1);
// }
//
// MusicBiTNode::~MusicBiTNode() {
//     delete this->lchild;
//     delete this->rchild;
//     this->rchild = nullptr;
//     this->lchild = nullptr;
// }
//
// MusicBSTree::~MusicBSTree() {
//     delete this->root;
// }
//
//
// static bool SearchBST(MusicBiTNode *current, const string& filepath, MusicBiTNode *node, MusicBiTNode **result){
//     if (current == nullptr) {
//         *result = node;
//         return false;
//     }
//     if (filepath == current->filepath) {
//         *result = current;
//         // 查询成功
//         return true;
//     }
//     if (filepath < current->filepath) {
//         return SearchBST(current->lchild, filepath, current, result);
//     }
//     return SearchBST(current->rchild, filepath, current, result);
// }
//
// bool MusicBSTree::InsertBST(const string& filepath, const string& filename) {
//     if (filename.find(IGNORE_SUFFIX_FLAC) != string::npos) {
//         return false;
//     }
//     MusicBiTNode *ptr = nullptr;
//     if (!SearchBST(this->root, filepath, nullptr, &ptr)) {
//         auto *node = new MusicBiTNode(filepath, filename);
//         if (ptr == nullptr) {
//             this->root = node;
//         }else if (filepath < ptr->filepath) {
//             ptr->lchild = node;
//         } else {
//             ptr->rchild = node;
//         }
//         this->size++;
//         return true;
//     }
//
//     return false;
// }
//
//
// void readDir(const string &dirPath, MusicBSTree &tree) {
//     DIR *dir = opendir(dirPath.c_str());
//     if (dir == nullptr) {
//         perror("opendir");
//         throw runtime_error("opendir");
//     }
//     const dirent *ptr = nullptr;
//     while ((ptr = readdir(dir)) != nullptr) {
//         string d_name = ptr->d_name;
//         string filepath = dirPath + "/" + d_name;
//         if (d_name == "." || d_name == "..") {
//             continue;
//         }
//         if (ptr->d_type == DT_DIR) {
//             readDir(filepath, tree);
//         }
//         if (ptr->d_type == DT_REG) {
//             tree.InsertBST(filepath, d_name);
//         }
//     }
//     closedir(dir);
// }

int main(int argc, const char **argv) {
    // if (argc != 2) {
    //     cerr << "Usage: ./app <path_to_file>" << endl;
    //     exit(EXIT_FAILURE);
    // }

    // auto* musicBSTree = new MusicBSTree();
    // const string dirpath = "/home/afterloe/音乐";
    // cout << "load folder : " << dirpath << endl;
    // readDir(dirpath, *musicBSTree);
    // delete musicBSTree;

    const auto tree = new BiTree::Tree<int>();

    tree->Insert(10);
    tree->Insert(11);
    tree->Insert(3);
    tree->Insert(13);
    tree->Insert(8);

    tree->Insert(14);

    return EXIT_SUCCESS;
}
