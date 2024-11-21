//
// Created by afterloe on 2024/11/20.
//
#ifndef BITREE_H
#define BITREE_H

#include <functional>

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

        void DLR(const Node *current, std::function<void(Music *)> callback);

        void LDR(const Node *current, std::function<void(Music *)> callback);

        void LRD(const Node *current, std::function<void(Music *)> callback);

    public:
        [[nodiscard]] int getSize() const;

        bool Contain(Music *data, Node **result);

        bool Insert(Music *data);

        void Traverse(std::function<void(Music *)> callback, int opt = 0);

        explicit Tree();

        ~Tree();
    };
}
#endif //BITREE_H
