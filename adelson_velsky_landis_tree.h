#pragma once

#include <algorithm>
#include "data_structure.h"

class AdelsonVelskyLandisTree : public DataStructure {
private:
    struct Node {
        int value;
        int height;
        Node* left;
        Node* right;

        explicit Node(int nodeValue)
            : value(nodeValue),
              height(1),
              left(nullptr),
              right(nullptr) {}
    };

    Node* root;

    static int getHeight(const Node* node) {
        return node == nullptr ? 0 : node->height;
    }

    static int getBalance(const Node* node) {
        if (node == nullptr) {
            return 0;
        }

        return getHeight(node->left) - getHeight(node->right);
    }

    static void updateHeight(Node* node) {
        if (node != nullptr) {
            node->height =
                1 + std::max(getHeight(node->left), getHeight(node->right));
        }
    }

    static Node* rotateRight(Node* node) {
        Node* newRoot = node->left;
        Node* transferredSubtree = newRoot->right;

        newRoot->right = node;
        node->left = transferredSubtree;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    static Node* rotateLeft(Node* node) {
        Node* newRoot = node->right;
        Node* transferredSubtree = newRoot->left;

        newRoot->left = node;
        node->right = transferredSubtree;

        updateHeight(node);
        updateHeight(newRoot);

        return newRoot;
    }

    static Node* rebalance(Node* node) {
        if (node == nullptr) {
            return nullptr;
        }

        updateHeight(node);

        const int balance = getBalance(node);

        if (balance > 1) {
            if (getBalance(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }

            return rotateRight(node);
        }

        if (balance < -1) {
            if (getBalance(node->right) > 0) {
                node->right = rotateRight(node->right);
            }

            return rotateLeft(node);
        }

        return node;
    }

    static Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->value) {
            node->left = insertNode(node->left, value);
        } else if (value > node->value) {
            node->right = insertNode(node->right, value);
        } else {
            return node;
        }

        return rebalance(node);
    }

    static Node* findMinimum(Node* node) {
        Node* current = node;

        while (current->left != nullptr) {
            current = current->left;
        }

        return current;
    }

    static Node* removeNode(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->value) {
            node->left = removeNode(node->left, value);
        } else if (value > node->value) {
            node->right = removeNode(node->right, value);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            if (node->left == nullptr) {
                Node* replacement = node->right;
                delete node;
                return replacement;
            }

            if (node->right == nullptr) {
                Node* replacement = node->left;
                delete node;
                return replacement;
            }

            Node* successor = findMinimum(node->right);
            node->value = successor->value;
            node->right = removeNode(node->right, successor->value);
        }

        return rebalance(node);
    }

    static bool searchNode(const Node* node, int value) {
        const Node* current = node;

        while (current != nullptr) {
            if (value == current->value) {
                return true;
            }

            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return false;
    }

    static void destroyTree(Node* node) {
        if (node == nullptr) {
            return;
        }

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    AdelsonVelskyLandisTree()
        : root(nullptr) {}

    ~AdelsonVelskyLandisTree() override {
        destroyTree(root);
    }

    AdelsonVelskyLandisTree(const AdelsonVelskyLandisTree&) = delete;
    AdelsonVelskyLandisTree& operator=(const AdelsonVelskyLandisTree&) = delete;

    void insert(int value) override {
        root = insertNode(root, value);
    }

    void remove(int value) override {
        root = removeNode(root, value);
    }

    bool search(int value) const override {
        return searchNode(root, value);
    }
};
