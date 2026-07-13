#pragma once

#include "../adelson_velsky_landis_tree.h"
#include "../binary_heap.h"
#include "../binary_search_tree.h"
#include "../binary_search_trie.h"
#include "../cuckoo_hash_table.h"
#include "../hash_table.h"
#include "../linked_list.h"
#include "../red_black_tree.h"
#include "../sorted_array.h"
#include "../splay_tree.h"
#include "../treap.h"

#include <algorithm>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <iomanip>
#include <iostream>
#include <memory>
#include <numeric>
#include <random>
#include <stdexcept>
#include <string>
#include <vector>

namespace benchmark {

typedef DataStructure* (*CreateDataStructure)();

struct Target {
    const char* name;
    CreateDataStructure create;
};

template <typename Structure>
DataStructure* createDataStructure() {
    return new Structure();
}

inline const std::vector<std::size_t>& sizes() {
    static const std::vector<std::size_t> allSizes{
        1000,
        10000,
        20000,
        50000,
        100000,
        200000
    };

    return allSizes;
}

inline std::uint32_t seedFor(std::size_t size, std::uint32_t salt) {
    std::uint32_t value = static_cast<std::uint32_t>(size);
    value ^= salt + 0x9e3779b9u + (value << 6) + (value >> 2);
    return value;
}

inline std::vector<int> increasingValues(std::size_t size) {
    std::vector<int> values(size);
    std::iota(values.begin(), values.end(), 1);
    return values;
}

inline std::vector<int> randomValues(
    std::size_t size,
    std::uint32_t salt
) {
    std::vector<int> values = increasingValues(size);
    std::mt19937 generator(seedFor(size, salt));
    std::shuffle(values.begin(), values.end(), generator);
    return values;
}

inline std::vector<int> smallShuffleValues(
    std::size_t size,
    std::uint32_t salt
) {
    std::vector<int> values = increasingValues(size);
    std::vector<std::size_t> positions(size);
    std::iota(positions.begin(), positions.end(), 0);

    std::mt19937 generator(seedFor(size, salt));
    std::shuffle(positions.begin(), positions.end(), generator);

    const std::size_t shuffleCount = size / 10;
    positions.resize(shuffleCount);

    std::vector<int> shuffledValues(shuffleCount);

    for (std::size_t index = 0; index < shuffleCount; ++index) {
        shuffledValues[index] = values[positions[index]];
    }

    std::shuffle(shuffledValues.begin(), shuffledValues.end(), generator);

    for (std::size_t index = 0; index < shuffleCount; ++index) {
        values[positions[index]] = shuffledValues[index];
    }

    return values;
}

template <typename Operation>
double elapsedMilliseconds(Operation operation) {
    const std::chrono::steady_clock::time_point start =
        std::chrono::steady_clock::now();

    operation();

    const std::chrono::steady_clock::time_point finish =
        std::chrono::steady_clock::now();

    return std::chrono::duration<double, std::milli>(finish - start).count();
}

inline void printSize(std::size_t size) {
    std::cout << "size: " << size << '\n';
}

inline void printResult(
    const char* testName,
    const char* structureName,
    double milliseconds
) {
    std::cout << testName << ": "
              << structureName << " - "
              << std::fixed << std::setprecision(3)
              << milliseconds << "ms\n";
}

inline void verifyInserted(
    DataStructure& structure,
    const std::vector<int>& values,
    const char* structureName
) {
    const std::size_t middle = values.size() >> 1;

    if (!structure.search(values.front()) ||
        !structure.search(values[middle]) ||
        !structure.search(values.back())) {
        throw std::runtime_error(
            std::string(structureName) + " failed insertion validation"
        );
    }
}

inline void runInsertCase(
    const Target& target,
    const char* caseName,
    const std::vector<int>& values
) {
    std::unique_ptr<DataStructure> structure(target.create());

    const double milliseconds = elapsedMilliseconds([&]() {
        for (std::size_t index = 0; index < values.size(); ++index) {
            structure->insert(values[index]);
        }
    });

    verifyInserted(*structure, values, target.name);
    printResult(caseName, target.name, milliseconds);
}

inline void runRemoveCase(
    const Target& target,
    const std::vector<int>& insertedValues,
    const std::vector<int>& removedValues
) {
    std::unique_ptr<DataStructure> structure(target.create());

    for (std::size_t index = 0;
         index < insertedValues.size();
         ++index) {
        structure->insert(insertedValues[index]);
    }

    const double milliseconds = elapsedMilliseconds([&]() {
        for (std::size_t index = 0;
             index < removedValues.size();
             ++index) {
            structure->remove(removedValues[index]);
        }
    });

    if (structure->search(removedValues.front()) ||
        structure->search(removedValues[removedValues.size() >> 1]) ||
        structure->search(removedValues.back())) {
        throw std::runtime_error(
            std::string(target.name) + " failed removal validation"
        );
    }

    printResult("remove", target.name, milliseconds);
}

inline void runSearchCase(
    const Target& target,
    const char* caseName,
    const std::vector<int>& insertedValues,
    const std::vector<int>& searchedValues,
    std::size_t expectedMatches
) {
    std::unique_ptr<DataStructure> structure(target.create());

    for (std::size_t index = 0;
         index < insertedValues.size();
         ++index) {
        structure->insert(insertedValues[index]);
    }

    std::size_t matchCount = 0;

    const double milliseconds = elapsedMilliseconds([&]() {
        for (std::size_t index = 0;
             index < searchedValues.size();
             ++index) {
            if (structure->search(searchedValues[index])) {
                ++matchCount;
            }
        }
    });

    if (matchCount != expectedMatches) {
        throw std::runtime_error(
            std::string(target.name) + " failed search validation"
        );
    }

    printResult(caseName, target.name, milliseconds);
}

inline void runAllBenchmarks(const Target& target) {
    const std::vector<std::size_t>& allSizes = sizes();

    for (std::size_t sizeIndex = 0;
         sizeIndex < allSizes.size();
         ++sizeIndex) {
        const std::size_t size = allSizes[sizeIndex];
        const std::vector<int> random =
            randomValues(size, 0x13579bdfu);
        const std::vector<int> increasing = increasingValues(size);
        const std::vector<int> smallShuffle =
            smallShuffleValues(size, 0x2468ace0u);
        const std::vector<int> removedValues =
            randomValues(size, 0x50607080u);
        const std::vector<int> searchValues =
            randomValues(size, 0x89abcdefu);
        const std::size_t reducedSize = size / 10;
        const std::vector<int> reducedSearchValues(
            searchValues.begin(),
            searchValues.begin() + reducedSize
        );

        printSize(size);
        runInsertCase(target, "random", random);
        runInsertCase(target, "increasing", increasing);
        runInsertCase(target, "small shuffle", smallShuffle);
        runRemoveCase(target, random, removedValues);
        runSearchCase(target, "search all", searchValues, searchValues, size);
        runSearchCase(
            target,
            "small search large insert",
            searchValues,
            reducedSearchValues,
            reducedSize
        );
        runSearchCase(
            target,
            "large search small insert",
            reducedSearchValues,
            searchValues,
            reducedSize
        );
        std::cout << '\n';
    }
}

template <typename Structure>
int runAllBenchmarks(const char* structureName) {
    try {
        const Target target{
            structureName,
            &createDataStructure<Structure>
        };

        runAllBenchmarks(target);
    } catch (const std::exception& error) {
        std::cerr << "benchmark failed: " << error.what() << '\n';
        return 1;
    }

    return 0;
}

}
