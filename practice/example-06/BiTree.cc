#include "include/BiTree.hpp"

using namespace BiTree;

template Node<int>;
template Tree<int>;

template<typename T>
Node<T>::Node(const T &data): data(data), left(), right() {
    this->data = data;
}

template<typename T>
Node<T>::~Node() {
    delete this->data;
    this->data = nullptr;
}

template<typename T>
Tree<T>::Tree(): root() {
    size = 0;
}

template<typename T>
Tree<T>::~Tree() = default;

template<typename T>
bool Tree<T>::Contain(T &data, Node<T> &result) {
    if (this->size == 0) {
        return false;
    }
    return Contain(nullptr, data, this->root, result);
}

template<typename T>
bool Tree<T>::Contain(Node<T> &current, T &data, Node<T> &find, Node<T> &result) {
    if (current == nullptr) {
        // 查询失败
        result = find;
        return false;
    }
    if (data == current->data) {
        // 查询成功
        result = current;
        return true;
    }
    if (data < current->data) {
        return Contain(current.left, data, current, result);
    }
    return Contain(current.right, data, current, result);
}

template<typename T>
bool Tree<T>::Insert(T data) {
    if (this->size == 0) {
        this->root = new Node<T>(data);
        this->size = 1;
        return true;
    }

    Node<T> *ptr = nullptr;
    if (!Contain(this->root, data, nullptr, &ptr)) {
        auto node = new Node<T>(data);
        if (data < ptr->data) {
            ptr->left = node;
        }
        else {
            ptr->right = node;
        }
        ++this->size;
        return true;
    }

    return false;
}