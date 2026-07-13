#pragma once

#include <cstddef>
#include <cstdint>
#include "data_structure.h"

class CuckooHashTable : public DataStructure {
private:
    static constexpr std::size_t minimumCapacity = 8;

    int* firstTable;
    int* secondTable;
    std::size_t capacity;
    std::size_t elementCount;
    std::uint32_t seedState;
    std::uint32_t firstSeed;
    std::uint32_t secondSeed;

    static std::size_t normalizeCapacity(std::size_t requestedCapacity) {
        std::size_t normalizedCapacity = minimumCapacity;

        while (normalizedCapacity < requestedCapacity) {
            normalizedCapacity <<= 1;
        }

        return normalizedCapacity;
    }

    static std::uint32_t mix(
        std::uint32_t value,
        std::uint32_t seed
    ) {
        value ^= seed;
        value ^= value >> 16;
        value *= 0x7feb352du;
        value ^= value >> 15;
        value *= 0x846ca68bu;
        value ^= value >> 16;
        return value;
    }

    static std::size_t tableIndex(
        int value,
        std::size_t tableCapacity,
        std::uint32_t seed
    ) {
        return static_cast<std::size_t>(
            mix(static_cast<std::uint32_t>(value), seed)
        ) & (tableCapacity - 1);
    }

    static bool placeValue(
        int value,
        int* candidateFirstTable,
        int* candidateSecondTable,
        std::size_t candidateCapacity,
        std::uint32_t candidateFirstSeed,
        std::uint32_t candidateSecondSeed,
        int& displacedValue
    ) {
        int currentValue = value;
        bool useFirstTable = true;
        const std::size_t maximumDisplacements = candidateCapacity << 1;

        for (
            std::size_t displacementCount = 0;
            displacementCount < maximumDisplacements;
            ++displacementCount
        ) {
            int* currentTable =
                useFirstTable ? candidateFirstTable : candidateSecondTable;
            const std::uint32_t currentSeed =
                useFirstTable ? candidateFirstSeed : candidateSecondSeed;
            const std::size_t index = tableIndex(
                currentValue,
                candidateCapacity,
                currentSeed
            );

            if (currentTable[index] == 0) {
                currentTable[index] = currentValue;
                return true;
            }

            const int nextValue = currentTable[index];
            currentTable[index] = currentValue;
            currentValue = nextValue;
            useFirstTable = !useFirstTable;
        }

        displacedValue = currentValue;
        return false;
    }

    std::uint32_t nextSeed() {
        seedState ^= seedState << 13;
        seedState ^= seedState >> 17;
        seedState ^= seedState << 5;
        return seedState;
    }

    void rebuild(int additionalValue, std::size_t requestedCapacity) {
        const std::size_t rebuiltElementCount = elementCount + 1;
        int* values = new int[rebuiltElementCount];
        std::size_t valueIndex = 0;

        for (std::size_t index = 0; index < capacity; ++index) {
            if (firstTable[index] != 0) {
                values[valueIndex] = firstTable[index];
                ++valueIndex;
            }

            if (secondTable[index] != 0) {
                values[valueIndex] = secondTable[index];
                ++valueIndex;
            }
        }

        values[valueIndex] = additionalValue;

        std::size_t rebuiltCapacity = normalizeCapacity(requestedCapacity);

        while (true) {
            int* rebuiltFirstTable = new int[rebuiltCapacity]();
            int* rebuiltSecondTable = new int[rebuiltCapacity]();
            const std::uint32_t rebuiltFirstSeed = nextSeed();
            const std::uint32_t rebuiltSecondSeed = nextSeed();
            bool rebuildSucceeded = true;

            for (std::size_t index = 0; index < rebuiltElementCount; ++index) {
                int displacedValue = 0;

                if (!placeValue(
                        values[index],
                        rebuiltFirstTable,
                        rebuiltSecondTable,
                        rebuiltCapacity,
                        rebuiltFirstSeed,
                        rebuiltSecondSeed,
                        displacedValue
                    )) {
                    rebuildSucceeded = false;
                    break;
                }
            }

            if (rebuildSucceeded) {
                delete[] firstTable;
                delete[] secondTable;

                firstTable = rebuiltFirstTable;
                secondTable = rebuiltSecondTable;
                capacity = rebuiltCapacity;
                elementCount = rebuiltElementCount;
                firstSeed = rebuiltFirstSeed;
                secondSeed = rebuiltSecondSeed;

                delete[] values;
                return;
            }

            delete[] rebuiltFirstTable;
            delete[] rebuiltSecondTable;
            rebuiltCapacity <<= 1;
        }
    }

public:
    explicit CuckooHashTable(std::size_t initialCapacity = minimumCapacity)
        : firstTable(nullptr),
          secondTable(nullptr),
          capacity(normalizeCapacity(initialCapacity)),
          elementCount(0),
          seedState(0x9e3779b9u),
          firstSeed(nextSeed()),
          secondSeed(nextSeed()) {
        firstTable = new int[capacity]();
        secondTable = new int[capacity]();
    }

    ~CuckooHashTable() override {
        delete[] firstTable;
        delete[] secondTable;
    }

    CuckooHashTable(const CuckooHashTable&) = delete;
    CuckooHashTable& operator=(const CuckooHashTable&) = delete;

    void insert(int value) override {
        if (search(value)) {
            return;
        }

        if (elementCount + 1 > capacity) {
            rebuild(value, capacity << 1);
            return;
        }

        int displacedValue = 0;

        if (placeValue(
                value,
                firstTable,
                secondTable,
                capacity,
                firstSeed,
                secondSeed,
                displacedValue
            )) {
            ++elementCount;
            return;
        }

        rebuild(displacedValue, capacity);
    }

    void remove(int value) override {
        const std::size_t firstIndex = tableIndex(
            value,
            capacity,
            firstSeed
        );

        if (firstTable[firstIndex] == value) {
            firstTable[firstIndex] = 0;
            --elementCount;
            return;
        }

        const std::size_t secondIndex = tableIndex(
            value,
            capacity,
            secondSeed
        );

        if (secondTable[secondIndex] == value) {
            secondTable[secondIndex] = 0;
            --elementCount;
        }
    }

    bool search(int value) const override {
        const std::size_t firstIndex = tableIndex(
            value,
            capacity,
            firstSeed
        );

        if (firstTable[firstIndex] == value) {
            return true;
        }

        const std::size_t secondIndex = tableIndex(
            value,
            capacity,
            secondSeed
        );

        return secondTable[secondIndex] == value;
    }

    std::size_t size() const {
        return elementCount;
    }

    bool empty() const {
        return elementCount == 0;
    }
};
