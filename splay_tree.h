#pragma once

#include "data_structure.h"

class SplayTree : public DataStructure {
private:
    struct Node {
        int value;
        Node* left;
        Node* right;

        explicit Node(int nodeValue)
            : value(nodeValue),
              left(nullptr),
              right(nullptr) {}
    };

    mutable Node* root;

    static Node* rotateRight(Node* node) {
        Node* newRoot = node->left;

        node->left = newRoot->right;
        newRoot->right = node;

        return newRoot;
    }

    static Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;

        node->right = newRoot->left;
        newRoot->left = node;

        return newRoot;
    }

    static Node* splay(Node* node, int value) {
        if (node == nullptr) {
            return node;
        }

        Node temporaryRoot(value);
        Node* leftTreeMaximum = &temporaryRoot;
        Node* rightTreeMinimum = &temporaryRoot;

        while (true) {
            if (value < node->value) {
                if (node->left == nullptr) {
                    break;
                }

                if (value < node->left->value) {
                    node = rotateRight(node);

                    if (node->left == nullptr) {
                        break;
                    }
                }

                rightTreeMinimum->left = node;
                rightTreeMinimum = node;
                node = node->left;
            } else if (value > node->value) {
                if (node->right == nullptr) {
                    break;
                }

                if (value > node->right->value) {
                    node = rotateLeft(node);

                    if (node->right == nullptr) {
                        break;
                    }
                }

                leftTreeMaximum->right = node;
                leftTreeMaximum = node;
                node = node->right;
            } else {
                break;
            }
        }

        leftTreeMaximum->right = node->left;
        rightTreeMinimum->left = node->right;
        node->left = temporaryRoot.right;
        node->right = temporaryRoot.left;

        return node;
    }

    static void destroy(Node* node) {
        while (node != nullptr) {
            if (node->left != nullptr) {
                Node* leftChild = node->left;
                node->left = leftChild->right;
                leftChild->right = node;
                node = leftChild;
            } else {
                Node* rightChild = node->right;
                delete node;
                node = rightChild;
            }
        }
    }

public:
    SplayTree()
        : root(nullptr) {}

    ~SplayTree() override {
        destroy(root);
    }

    SplayTree(const SplayTree&) = delete;
    SplayTree& operator=(const SplayTree&) = delete;

    void insert(int value) override {
        if (root == nullptr) {
            root = new Node(value);
            return;
        }

        root = splay(root, value);

        if (root->value == value) {
            return;
        }

        Node* newNode = new Node(value);

        if (value < root->value) {
            newNode->left = root->left;
            newNode->right = root;
            root->left = nullptr;
        } else {
            newNode->right = root->right;
            newNode->left = root;
            root->right = nullptr;
        }

        root = newNode;
    }

    void remove(int value) override {
        if (root == nullptr) {
            return;
        }

        root = splay(root, value);

        if (root->value != value) {
            return;
        }

        Node* oldRoot = root;

        if (root->left == nullptr) {
            root = root->right;
        } else {
            Node* rightSubtree = root->right;

            root = root->left;

            root = splay(root, value);
            root->right = rightSubtree;
        }

        delete oldRoot;
    }

    bool search(int value) const override {
        root = splay(root, value);

        return root != nullptr &&
               root->value == value;
    }
};
