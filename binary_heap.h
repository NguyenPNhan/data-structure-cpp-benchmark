#pragma once

#include <cstddef>
#include "data_structure.h"

class BinaryHeap : public DataStructure {
private:
    int* data;
    std::size_t heapSize;
    std::size_t capacity;

    static std::size_t parent(std::size_t index) {
        return (index - 1) >> 1;
    }

    static std::size_t leftChild(std::size_t index) {
        return (index << 1) + 1;
    }

    static std::size_t rightChild(std::size_t index) {
        return (index << 1) + 2;
    }

    static void swap(int& firstValue, int& secondValue) {
        const int temporaryValue = firstValue;
        firstValue = secondValue;
        secondValue = temporaryValue;
    }

    void resize(std::size_t newCapacity) {
        int* newData = new int[newCapacity];

        for (std::size_t index = 0; index < heapSize; ++index) {
            newData[index] = data[index];
        }

        delete[] data;
        data = newData;
        capacity = newCapacity;
    }

    void heapifyUp(std::size_t index) {
        while (index > 0) {
            std::size_t parentIndex = parent(index);

            if (data[parentIndex] <= data[index]) {
                break;
            }

            swap(data[parentIndex], data[index]);
            index = parentIndex;
        }
    }

    void heapifyDown(std::size_t index) {
        while (true) {
            std::size_t smallest = index;
            std::size_t left = leftChild(index);
            std::size_t right = rightChild(index);

            if (left < heapSize && data[left] < data[smallest]) {
                smallest = left;
            }

            if (right < heapSize && data[right] < data[smallest]) {
                smallest = right;
            }

            if (smallest == index) {
                break;
            }

            swap(data[index], data[smallest]);
            index = smallest;
        }
    }

    std::size_t findIndex(int value) const {
        for (std::size_t index = 0; index < heapSize; ++index) {
            if (data[index] == value) {
                return index;
            }
        }

        return heapSize;
    }

public:
    explicit BinaryHeap(std::size_t initialCapacity = 8)
        : data(nullptr),
          heapSize(0),
          capacity(initialCapacity == 0 ? 8 : initialCapacity) {
        data = new int[capacity];
    }

    ~BinaryHeap() override {
        delete[] data;
    }

    BinaryHeap(const BinaryHeap&) = delete;
    BinaryHeap& operator=(const BinaryHeap&) = delete;

    void insert(int value) override {
        if (search(value)) {
            return;
        }

        if (heapSize == capacity) {
            resize(capacity << 1);
        }

        data[heapSize] = value;
        heapifyUp(heapSize);
        ++heapSize;
    }

    void remove(int value) override {
        std::size_t index = findIndex(value);

        if (index == heapSize) {
            return;
        }

        data[index] = data[heapSize - 1];
        --heapSize;

        if (index < heapSize) {
            if (index > 0 && data[index] < data[parent(index)]) {
                heapifyUp(index);
            } else {
                heapifyDown(index);
            }
        }

        if (capacity > 8 && heapSize <= (capacity >> 2)) {
            resize(capacity >> 1);
        }
    }

    bool search(int value) const override {
        return findIndex(value) != heapSize;
    }

    int getMinimum() const {
        if (heapSize == 0) {
            throw "Heap is empty";
        }

        return data[0];
    }

    void removeMinimum() {
        if (heapSize == 0) {
            return;
        }

        data[0] = data[heapSize - 1];
        --heapSize;

        if (heapSize > 0) {
            heapifyDown(0);
        }

        if (capacity > 8 && heapSize <= (capacity >> 2)) {
            resize(capacity >> 1);
        }
    }

    std::size_t size() const {
        return heapSize;
    }

    bool empty() const {
        return heapSize == 0;
    }
};
