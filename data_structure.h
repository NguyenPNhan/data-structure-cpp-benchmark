#pragma once

class DataStructure {
public:
    virtual ~DataStructure() = default;

    virtual void insert(int value) = 0;
    virtual void remove(int value) = 0;
    virtual bool search(int value) const = 0;
};
