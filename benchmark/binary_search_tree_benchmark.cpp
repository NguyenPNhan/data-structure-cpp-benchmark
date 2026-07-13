#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<BinarySearchTree>(
        "Binary Search Tree"
    );
}
