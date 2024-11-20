#include <iostream>

#include <unistd.h>
#include <cstring>
#include <dirent.h>

using namespace std;


class MusicBiTNode {
public:
    string filepath;
    string filename;
    MusicBiTNode *lchild;
    MusicBiTNode *rchild;

    explicit MusicBiTNode(string filepath);

    ~MusicBiTNode();
};


class MusicBSTree {
    MusicBiTNode *root;
    int size;

public:

    bool InsertBST(const string& filepath);

    MusicBSTree() {
        root = NULL;
        size = 0;
    };

    ~MusicBSTree();
};

MusicBiTNode::MusicBiTNode(string filepath): lchild(nullptr), rchild(nullptr) {
    this->filepath = std::move(filepath);
}

MusicBiTNode::~MusicBiTNode() {
    delete this->lchild;
    delete this->rchild;
    this->rchild = nullptr;
    this->lchild = nullptr;
}

MusicBSTree::~MusicBSTree() {
    delete this->root;
}


static bool SearchBST(MusicBiTNode *curtent, const string& filepath, MusicBiTNode *node, MusicBiTNode **result){
    if (curtent == nullptr) {
        *result = node;
        return false;
    }
    if (filepath == curtent->filepath) {
        *result = curtent;
        // 查询成功
        return true;
    }
    if (filepath < curtent->filepath) {
        return SearchBST(curtent->lchild, filepath, curtent, result);
    }
    return SearchBST(curtent->rchild, filepath, curtent, result);
}

bool MusicBSTree::InsertBST(const string& filepath) {
    MusicBiTNode *ptr = nullptr;
    if (!SearchBST(this->root, filepath, nullptr, &ptr)) {
        auto *node = new MusicBiTNode(filepath);
        if (ptr == nullptr) {
            this->root = node;
        }else if (filepath < ptr->filepath) {
            ptr->lchild = node;
        } else {
            ptr->rchild = node;
        }
        this->size++;
        return true;
    }

    return false;
}


void readDir(const string &dirPath, MusicBSTree &tree) {
    DIR *dir = opendir(dirPath.c_str());
    if (dir == nullptr) {
        perror("opendir");
        throw runtime_error("opendir");
    }
    dirent *ptr = nullptr;
    char newpath[PATH_MAX] = {0};
    while ((ptr = readdir(dir)) != nullptr) {
        if (strcmp(ptr->d_name, ".") == 0 || strcmp(ptr->d_name, "..") == 0) {
            continue;
        }
        if (ptr->d_type == DT_DIR) {
            sprintf(newpath, "%s/%s", dirPath.c_str(), ptr->d_name);
            readDir(newpath, tree);
        }
        if (ptr->d_type == DT_REG) {
            tree.InsertBST(dirPath + "/" + ptr->d_name);
        }
    }
    closedir(dir);
}

int main(int argc, const char **argv) {
    // if (argc != 2) {
    //     cerr << "Usage: ./app <path_to_file>" << endl;
    //     exit(EXIT_FAILURE);
    // }
    auto* musicBSTree = new MusicBSTree();
    const string dirpath = "/home/afterloe/音乐";
    cout << "load folder : " << dirpath << endl;
    readDir(dirpath, *musicBSTree);
    delete musicBSTree;
    return EXIT_SUCCESS;
}
