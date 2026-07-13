#pragma once

#include <cstdint>
#include "data_structure.h"

class Treap : public DataStructure {
private:
    struct Node {
        int value;
        std::uint32_t priority;
        Node* left;
        Node* right;

        Node(int nodeValue, std::uint32_t nodePriority)
            : value(nodeValue),
              priority(nodePriority),
              left(nullptr),
              right(nullptr) {}
    };

    Node* root;
    std::uint32_t randomState;

    std::uint32_t nextRandom() {
        std::uint32_t randomValue = randomState;

        randomValue ^= randomValue << 13;
        randomValue ^= randomValue >> 17;
        randomValue ^= randomValue << 5;

        randomState = randomValue;
        return randomValue;
    }

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

    Node* insertNode(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value, nextRandom());
        }

        if (value < node->value) {
            node->left = insertNode(node->left, value);

            if (node->left->priority < node->priority) {
                node = rotateRight(node);
            }
        } else if (value > node->value) {
            node->right = insertNode(node->right, value);

            if (node->right->priority < node->priority) {
                node = rotateLeft(node);
            }
        }

        return node;
    }

    static Node* removeNode(Node* node, int value) {
        if (node == nullptr) {
            return nullptr;
        }

        if (value < node->value) {
            node->left = removeNode(node->left, value);
            return node;
        }

        if (value > node->value) {
            node->right = removeNode(node->right, value);
            return node;
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

        if (node->left->priority <
            node->right->priority) {
            node = rotateRight(node);
            node->right = removeNode(node->right, value);
        } else {
            node = rotateLeft(node);
            node->left = removeNode(node->left, value);
        }

        return node;
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

    static void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }

        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    explicit Treap(
        std::uint32_t seed = 2463534242u
    )
        : root(nullptr),
          randomState(seed == 0 ? 2463534242u : seed) {}

    ~Treap() override {
        destroy(root);
    }

    Treap(const Treap&) = delete;
    Treap& operator=(const Treap&) = delete;

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
