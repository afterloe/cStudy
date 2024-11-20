//
// Created by afterloe on 2024/11/20.
//
#ifndef BITREE_H
#define BITREE_H

namespace BiTree {
    template<typename T>
    class Node {
        T &data;
        Node &left;
        Node &right;

    public:
        explicit Node(const T &data);

        ~Node();
    };

    template<typename T>
    class Tree {
        Tree &root;
        int size;

        bool Contain(Node<T> &current, T &data, Node<T> &find, Node<T> &result);
    public:
        bool Contain(T &data, Node<T> &result);

        bool Insert(T data);

        explicit Tree();

        ~Tree();
    };
}
#endif //BITREE_H
