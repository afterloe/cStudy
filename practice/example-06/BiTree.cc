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

int Tree::getSize() const {
    return size;
}

Tree::~Tree() = default;


bool Tree::Contain(Music *data, Node **result) {
    if (this->size == 0) {
        return false;
    }
    return Contain(nullptr, data, this->root, result);
}

void Tree::LDR(const Node *current, const std::function<void(Music *)>& callback) {
    if (current == nullptr) {
        return;
    }
    LDR(current->left, callback);
    callback(current->data);
    LDR(current->right, callback);
}

void Tree::DLR(const Node *current, const std::function<void(Music *)>& callback) {
    if (current == nullptr) {
        return;
    }
    callback(current->data);
    DLR(current->left, callback);
    DLR(current->right, callback);
}

void Tree::LRD(const Node *current, const std::function<void(Music *)>& callback) {
    if (current == nullptr) {
        return;
    }
    LRD(current->left, callback);
    LRD(current->right, callback);
    callback(current->data);
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

void Tree::Traverse(const std::function<void(Music *)>& callback, int opt) throw(std::exception) {
    if (nullptr == callback) {
        return;
    }
    if (nullptr == this->root || 0 == this->size) {
        throw std::runtime_error("Tree is empty");
    }
    switch (opt) {
        case 1:
            this->LDR(this->root, callback);
            break;
        case 2:
            this->LRD(this->root, callback);
            break;
        case 0:
        default:
            this->LDR(this->root, callback);
    }
}
