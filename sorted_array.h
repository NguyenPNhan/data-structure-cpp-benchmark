#pragma once

#include <cstddef>
#include "data_structure.h"

class SortedArray : public DataStructure {
private:
    int* data_;
    std::size_t size_;
    std::size_t capacity_;

    void resize(std::size_t new_capacity) {
        int* new_data = new int[new_capacity];

        for (std::size_t index = 0; index < size_; ++index) {
            new_data[index] = data_[index];
        }

        delete[] data_;
        data_ = new_data;
        capacity_ = new_capacity;
    }

    std::size_t lowerBound(int value) const {
        std::size_t left = 0;
        std::size_t right = size_;

        while (left < right) {
            const std::size_t middle = left + ((right - left) >> 1);

            if (data_[middle] < value) {
                left = middle + 1;
            } else {
                right = middle;
            }
        }

        return left;
    }

public:
    explicit SortedArray(std::size_t initial_capacity = 8)
        : data_(nullptr),
          size_(0),
          capacity_(initial_capacity == 0 ? 1 : initial_capacity) {
        data_ = new int[capacity_];
    }

    ~SortedArray() override {
        delete[] data_;
    }

    SortedArray(const SortedArray&) = delete;
    SortedArray& operator=(const SortedArray&) = delete;

    void insert(int value) override {
        const std::size_t position = lowerBound(value);

        if (position < size_ && data_[position] == value) {
            return;
        }

        if (size_ == capacity_) {
            resize(capacity_ << 1);
        }

        for (std::size_t index = size_; index > position; --index) {
            data_[index] = data_[index - 1];
        }

        data_[position] = value;
        ++size_;
    }

    void remove(int value) override {
        const std::size_t position = lowerBound(value);

        if (position == size_ || data_[position] != value) {
            return;
        }

        for (std::size_t index = position; index + 1 < size_; ++index) {
            data_[index] = data_[index + 1];
        }

        --size_;

        if (capacity_ > 8 && size_ <= (capacity_ >> 2)) {
            resize(capacity_ >> 1);
        }
    }

    bool search(int value) const override {
        const std::size_t position = lowerBound(value);
        return position < size_ && data_[position] == value;
    }

    std::size_t size() const {
        return size_;
    }
};
