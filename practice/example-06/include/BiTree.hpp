//
// Created by afterloe on 2024/11/20.
//
#ifndef BITREE_H
#define BITREE_H

#include "Music.hpp"

namespace BiTree {
    class Node {
    public:
        Music *data;
        Node *left;
        Node *right;

        explicit Node(Music *data);

        ~Node();
    };


    class Tree {
        Node *root;
        int size;

        bool Contain(Node *current, Music *data, Node *find, Node **result);

        void DLR(const Node *current, void callback(Music &data));

        void LDR(const Node *current, void callback(Music &data));

        void LRD(const Node *current, void callback(Music &data));

    public:
        bool Contain(Music *data, Node **result);

        bool Insert(Music *data);

        void Traverse(void (*callback)(Music *));

        explicit Tree();

        ~Tree();
    };
}
#endif //BITREE_H
