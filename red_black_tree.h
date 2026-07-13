#pragma once

#include "data_structure.h"

class RedBlackTree : public DataStructure {
private:
    enum class Color {
        RED,
        BLACK
    };

    struct Node {
        int value;
        Color color;
        Node* parent;
        Node* left;
        Node* right;

        Node()
            : value(0),
              color(Color::BLACK),
              parent(nullptr),
              left(nullptr),
              right(nullptr) {}

        Node(int nodeValue, Node* sentinel)
            : value(nodeValue),
              color(Color::RED),
              parent(sentinel),
              left(sentinel),
              right(sentinel) {}
    };

    Node* root;
    Node* sentinel;

    void rotateLeft(Node* node) {
        Node* newRoot = node->right;
        node->right = newRoot->left;

        if (newRoot->left != sentinel) {
            newRoot->left->parent = node;
        }

        newRoot->parent = node->parent;

        if (node->parent == sentinel) {
            root = newRoot;
        } else if (node == node->parent->left) {
            node->parent->left = newRoot;
        } else {
            node->parent->right = newRoot;
        }

        newRoot->left = node;
        node->parent = newRoot;
    }

    void rotateRight(Node* node) {
        Node* newRoot = node->left;
        node->left = newRoot->right;

        if (newRoot->right != sentinel) {
            newRoot->right->parent = node;
        }

        newRoot->parent = node->parent;

        if (node->parent == sentinel) {
            root = newRoot;
        } else if (node == node->parent->right) {
            node->parent->right = newRoot;
        } else {
            node->parent->left = newRoot;
        }

        newRoot->right = node;
        node->parent = newRoot;
    }

    void fixInsert(Node* node) {
        while (node->parent->color == Color::RED) {
            if (node->parent == node->parent->parent->left) {
                Node* uncle = node->parent->parent->right;

                if (uncle->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->right) {
                        node = node->parent;
                        rotateLeft(node);
                    }

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rotateRight(node->parent->parent);
                }
            } else {
                Node* uncle = node->parent->parent->left;

                if (uncle->color == Color::RED) {
                    node->parent->color = Color::BLACK;
                    uncle->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    node = node->parent->parent;
                } else {
                    if (node == node->parent->left) {
                        node = node->parent;
                        rotateRight(node);
                    }

                    node->parent->color = Color::BLACK;
                    node->parent->parent->color = Color::RED;
                    rotateLeft(node->parent->parent);
                }
            }
        }

        root->color = Color::BLACK;
        root->parent = sentinel;
    }

    Node* findNode(int value) const {
        Node* current = root;

        while (current != sentinel) {
            if (value == current->value) {
                return current;
            }

            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        return sentinel;
    }

    Node* minimum(Node* node) const {
        while (node->left != sentinel) {
            node = node->left;
        }

        return node;
    }

    void transplant(Node* oldNode, Node* newNode) {
        if (oldNode->parent == sentinel) {
            root = newNode;
        } else if (oldNode == oldNode->parent->left) {
            oldNode->parent->left = newNode;
        } else {
            oldNode->parent->right = newNode;
        }

        newNode->parent = oldNode->parent;
    }

    void fixRemove(Node* node) {
        while (node != root && node->color == Color::BLACK) {
            if (node == node->parent->left) {
                Node* sibling = node->parent->right;

                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    rotateLeft(node->parent);
                    sibling = node->parent->right;
                }

                if (sibling->left->color == Color::BLACK &&
                    sibling->right->color == Color::BLACK) {
                    sibling->color = Color::RED;
                    node = node->parent;
                } else {
                    if (sibling->right->color == Color::BLACK) {
                        sibling->left->color = Color::BLACK;
                        sibling->color = Color::RED;
                        rotateRight(sibling);
                        sibling = node->parent->right;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    sibling->right->color = Color::BLACK;
                    rotateLeft(node->parent);
                    node = root;
                }
            } else {
                Node* sibling = node->parent->left;

                if (sibling->color == Color::RED) {
                    sibling->color = Color::BLACK;
                    node->parent->color = Color::RED;
                    rotateRight(node->parent);
                    sibling = node->parent->left;
                }

                if (sibling->right->color == Color::BLACK &&
                    sibling->left->color == Color::BLACK) {
                    sibling->color = Color::RED;
                    node = node->parent;
                } else {
                    if (sibling->left->color == Color::BLACK) {
                        sibling->right->color = Color::BLACK;
                        sibling->color = Color::RED;
                        rotateLeft(sibling);
                        sibling = node->parent->left;
                    }

                    sibling->color = node->parent->color;
                    node->parent->color = Color::BLACK;
                    sibling->left->color = Color::BLACK;
                    rotateRight(node->parent);
                    node = root;
                }
            }
        }

        node->color = Color::BLACK;
    }

    void destroyTree(Node* node) {
        if (node == sentinel) {
            return;
        }

        destroyTree(node->left);
        destroyTree(node->right);
        delete node;
    }

public:
    RedBlackTree() {
        sentinel = new Node();
        sentinel->parent = sentinel;
        sentinel->left = sentinel;
        sentinel->right = sentinel;

        root = sentinel;
    }

    ~RedBlackTree() override {
        destroyTree(root);
        delete sentinel;
    }

    RedBlackTree(const RedBlackTree&) = delete;
    RedBlackTree& operator=(const RedBlackTree&) = delete;

    void insert(int value) override {
        Node* parent = sentinel;
        Node* current = root;

        while (current != sentinel) {
            parent = current;

            if (value == current->value) {
                return;
            }

            if (value < current->value) {
                current = current->left;
            } else {
                current = current->right;
            }
        }

        Node* newNode = new Node(value, sentinel);
        newNode->parent = parent;

        if (parent == sentinel) {
            root = newNode;
        } else if (value < parent->value) {
            parent->left = newNode;
        } else {
            parent->right = newNode;
        }

        fixInsert(newNode);
    }

    void remove(int value) override {
        Node* target = findNode(value);

        if (target == sentinel) {
            return;
        }

        Node* replacement = target;
        Color originalColor = replacement->color;
        Node* movedNode;

        if (target->left == sentinel) {
            movedNode = target->right;
            transplant(target, target->right);
        } else if (target->right == sentinel) {
            movedNode = target->left;
            transplant(target, target->left);
        } else {
            replacement = minimum(target->right);
            originalColor = replacement->color;
            movedNode = replacement->right;

            if (replacement->parent == target) {
                movedNode->parent = replacement;
            } else {
                transplant(replacement, replacement->right);

                replacement->right = target->right;
                replacement->right->parent = replacement;
            }

            transplant(target, replacement);

            replacement->left = target->left;
            replacement->left->parent = replacement;
            replacement->color = target->color;
        }

        delete target;

        if (originalColor == Color::BLACK) {
            fixRemove(movedNode);
        }

        if (root != sentinel) {
            root->parent = sentinel;
        }
    }

    bool search(int value) const override {
        return findNode(value) != sentinel;
    }
};
