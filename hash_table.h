#pragma once

#include <cstddef>
#include "data_structure.h"

class HashTable : public DataStructure {
private:
    struct Node {
        int value;
        Node* next;

        explicit Node(int nodeValue, Node* nextNode = nullptr)
            : value(nodeValue), next(nextNode) {}
    };

    static constexpr std::size_t minimumCapacity = 8;

    Node** buckets;
    std::size_t capacity;
    std::size_t elementCount;

    static std::size_t normalizeCapacity(std::size_t requestedCapacity) {
        std::size_t normalizedCapacity = minimumCapacity;

        while (normalizedCapacity < requestedCapacity) {
            normalizedCapacity <<= 1;
        }

        return normalizedCapacity;
    }

    std::size_t bucketIndex(int value) const {
        return static_cast<std::size_t>(value) & (capacity - 1);
    }

    void initializeBuckets() {
        buckets = new Node*[capacity];

        for (std::size_t index = 0; index < capacity; ++index) {
            buckets[index] = nullptr;
        }
    }

    void rehash() {
        const std::size_t oldCapacity = capacity;
        Node** oldBuckets = buckets;

        capacity <<= 1;
        initializeBuckets();

        for (std::size_t index = 0; index < oldCapacity; ++index) {
            Node* current = oldBuckets[index];

            while (current != nullptr) {
                Node* nextNode = current->next;

                const std::size_t newIndex = bucketIndex(current->value);
                current->next = buckets[newIndex];
                buckets[newIndex] = current;

                current = nextNode;
            }
        }

        delete[] oldBuckets;
    }

public:
    explicit HashTable(std::size_t initialCapacity = minimumCapacity)
        : buckets(nullptr),
          capacity(normalizeCapacity(initialCapacity)),
          elementCount(0) {
        initializeBuckets();
    }

    ~HashTable() override {
        for (std::size_t index = 0; index < capacity; ++index) {
            Node* current = buckets[index];

            while (current != nullptr) {
                Node* nextNode = current->next;
                delete current;
                current = nextNode;
            }
        }

        delete[] buckets;
    }

    HashTable(const HashTable&) = delete;
    HashTable& operator=(const HashTable&) = delete;

    void insert(int value) override {
        if (search(value)) {
            return;
        }

        if (((elementCount + 1) << 2) >
            capacity + (capacity << 1)) {
            rehash();
        }

        const std::size_t index = bucketIndex(value);

        buckets[index] = new Node(value, buckets[index]);
        ++elementCount;
    }

    void remove(int value) override {
        const std::size_t index = bucketIndex(value);

        Node* current = buckets[index];
        Node* previous = nullptr;

        while (current != nullptr) {
            if (current->value == value) {
                if (previous == nullptr) {
                    buckets[index] = current->next;
                } else {
                    previous->next = current->next;
                }

                delete current;
                --elementCount;
                return;
            }

            previous = current;
            current = current->next;
        }
    }

    bool search(int value) const override {
        const std::size_t index = bucketIndex(value);
        const Node* current = buckets[index];

        while (current != nullptr) {
            if (current->value == value) {
                return true;
            }

            current = current->next;
        }

        return false;
    }

    std::size_t size() const {
        return elementCount;
    }
};
