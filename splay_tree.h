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
        if (node == nullptr || node->value == value) {
            return node;
        }

        if (value < node->value) {
            if (node->left == nullptr) {
                return node;
            }

            if (value < node->left->value) {
                node->left->left =
                    splay(node->left->left, value);

                node = rotateRight(node);
            }
            else if (value > node->left->value) {
                node->left->right =
                    splay(node->left->right, value);

                if (node->left->right != nullptr) {
                    node->left = rotateLeft(node->left);
                }
            }

            if (node->left == nullptr) {
                return node;
            }

            return rotateRight(node);
        }

        if (node->right == nullptr) {
            return node;
        }

        if (value < node->right->value) {
            node->right->left =
                splay(node->right->left, value);

            if (node->right->left != nullptr) {
                node->right = rotateRight(node->right);
            }
        }
        else if (value > node->right->value) {
            node->right->right =
                splay(node->right->right, value);

            node = rotateLeft(node);
        }

        if (node->right == nullptr) {
            return node;
        }

        return rotateLeft(node);
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
