#pragma once

#include "data_structure.h"

class LinkedList : public DataStructure {
private:
    struct Node {
        int value;
        Node* next;

        explicit Node(int nodeValue)
            : value(nodeValue),
              next(nullptr) {}
    };

    Node* head;

    void clear() {
        while (head != nullptr) {
            Node* nodeToDelete = head;
            head = head->next;
            delete nodeToDelete;
        }
    }

public:
    LinkedList()
        : head(nullptr) {}

    LinkedList(const LinkedList&) = delete;
    LinkedList& operator=(const LinkedList&) = delete;

    ~LinkedList() override {
        clear();
    }

    void insert(int value) override {
        if (head == nullptr) {
            head = new Node(value);
            return;
        }

        Node* current = head;

        while (true) {
            if (current->value == value) {
                return;
            }

            if (current->next == nullptr) {
                current->next = new Node(value);
                return;
            }

            current = current->next;
        }
    }

    void remove(int value) override {
        Node* previous = nullptr;
        Node* current = head;

        while (current != nullptr) {
            if (current->value == value) {
                if (previous == nullptr) {
                    head = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    bool search(int value) const override {
        const Node* current = head;

        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }

            current = current->next;
        }

        return false;
    }
};
