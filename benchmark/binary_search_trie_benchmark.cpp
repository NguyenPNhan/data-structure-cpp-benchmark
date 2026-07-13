#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<BinarySearchTrie>(
        "Binary Search Trie"
    );
}
