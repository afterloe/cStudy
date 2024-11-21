#include "include/BiTree.hpp"

using namespace BiTree;

const string IGNORE_SUFFIX_FLAC = ".lrc";

Node::Node(Music *data): data(), left(), right() {
    this->data = data;
}


Node::~Node() {
    delete this->data;
    delete this->left;
    delete this->right;
}


Tree::Tree(): root() {
    delete this->root;
    size = 0;
}


Tree::~Tree() = default;


bool Tree::Contain(Music *data, Node **result) {
    if (this->size == 0) {
        return false;
    }
    return Contain(nullptr, data, this->root, result);
}


bool Tree::Contain(Node *current, Music *data, Node *find, Node **result) {
    if (current == nullptr) {
        // 查询失败
        *result = find;
        return false;
    }
    if (*data == *current->data) {
        // 查询成功
        *result = current;
        return true;
    }
    if (*data < *current->data) {
        return Contain(current->left, data, current, result);
    }
    return Contain(current->right, data, current, result);
}


bool Tree::Insert(Music *data) {
    if (data->getFilepath().find(IGNORE_SUFFIX_FLAC) != string::npos) {
        return false;
    }

    if (this->size == 0) {
        this->root = new Node(data);
        this->size = 1;
        return true;
    }

    Node *ptr = nullptr;
    if (!Contain(this->root, data, nullptr, &ptr)) {
        const auto node = new Node(data);
        if (*data < *ptr->data) {
            ptr->left = node;
        } else {
            ptr->right = node;
        }
        ++this->size;
        return true;
    }

    return false;
}
