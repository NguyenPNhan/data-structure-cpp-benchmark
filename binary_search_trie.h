#pragma once

#include <cstdint>
#include "data_structure.h"

class BinarySearchTrie : public DataStructure {
private:
    struct Node {
        Node* child[2];
        bool isTerminal;

        Node()
            : child{nullptr, nullptr},
              isTerminal(false) {}
    };

    static constexpr int highestValueBit = 30;
    Node* root;

    static bool hasChildren(const Node* node) {
        return node->child[0] != nullptr ||
               node->child[1] != nullptr;
    }

    static bool removeNode(
        Node* node,
        std::uint32_t value,
        int bit
    ) {
        if (node == nullptr) {
            return false;
        }

        if (bit < 0) {
            if (!node->isTerminal) {
                return false;
            }

            node->isTerminal = false;
            return !hasChildren(node);
        }

        const int childIndex = static_cast<int>((value >> bit) & 1u);

        Node* next = node->child[childIndex];

        if (next == nullptr) {
            return false;
        }

        const bool shouldDeleteChild =
            removeNode(next, value, bit - 1);

        if (shouldDeleteChild) {
            delete next;
            node->child[childIndex] = nullptr;
        }

        return !node->isTerminal && !hasChildren(node);
    }

    static void destroy(Node* node) {
        if (node == nullptr) {
            return;
        }

        destroy(node->child[0]);
        destroy(node->child[1]);
        delete node;
    }

public:
    BinarySearchTrie()
        : root(new Node()) {}

    ~BinarySearchTrie() override {
        destroy(root);
    }

    BinarySearchTrie(const BinarySearchTrie&) = delete;
    BinarySearchTrie& operator=(const BinarySearchTrie&) = delete;

    void insert(int value) override {
        const std::uint32_t unsignedValue =
            static_cast<std::uint32_t>(value);
        Node* current = root;

        for (int bit = highestValueBit; bit >= 0; --bit) {
            const int childIndex =
                static_cast<int>((unsignedValue >> bit) & 1u);

            if (current->child[childIndex] == nullptr) {
                current->child[childIndex] = new Node();
            }

            current = current->child[childIndex];
        }

        current->isTerminal = true;
    }

    void remove(int value) override {
        removeNode(
            root,
            static_cast<std::uint32_t>(value),
            highestValueBit
        );
    }

    bool search(int value) const override {
        const std::uint32_t unsignedValue =
            static_cast<std::uint32_t>(value);
        const Node* current = root;

        for (int bit = highestValueBit; bit >= 0; --bit) {
            const int childIndex =
                static_cast<int>((unsignedValue >> bit) & 1u);

            current = current->child[childIndex];

            if (current == nullptr) {
                return false;
            }
        }

        return current->isTerminal;
    }
};
