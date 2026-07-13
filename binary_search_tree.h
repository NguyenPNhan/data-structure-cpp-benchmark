#pragma once

#include "data_structure.h"

class BinarySearchTree : public DataStructure {
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

    Node* root;

    static void destroyTree(Node* node) {
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
    BinarySearchTree()
        : root(nullptr) {}

    BinarySearchTree(const BinarySearchTree&) = delete;
    BinarySearchTree& operator=(const BinarySearchTree&) = delete;

    ~BinarySearchTree() override {
        destroyTree(root);
    }

    void insert(int value) override {
        if (root == nullptr) {
            root = new Node(value);
            return;
        }

        Node* current = root;

        while (true) {
            if (value == current->value) {
                return;
            }

            if (value < current->value) {
                if (current->left == nullptr) {
                    current->left = new Node(value);
                    return;
                }

                current = current->left;
            } else {
                if (current->right == nullptr) {
                    current->right = new Node(value);
                    return;
                }

                current = current->right;
            }
        }
    }

    void remove(int value) override {
        Node* parent = nullptr;
        Node* current = root;

        while (current != nullptr && current->value != value) {
            parent = current;

            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        if (current == nullptr) {
            return;
        }

        if (current->left == nullptr || current->right == nullptr) {
            Node* child;

            if (current->left != nullptr) {
                child = current->left;
            } else {
                child = current->right;
            }

            if (parent == nullptr) {
                root = child;
            } else if (parent->left == current) {
                parent->left = child;
            } else {
                parent->right = child;
            }

            delete current;
            return;
        }

        Node* successorParent = current;
        Node* successor = current->right;

        while (successor->left != nullptr) {
            successorParent = successor;
            successor = successor->left;
        }

        current->value = successor->value;

        if (successorParent->left == successor) {
            successorParent->left = successor->right;
        } else {
            successorParent->right = successor->right;
        }

        delete successor;
    }

    bool search(int value) const override {
        const Node* current = root;

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
};
