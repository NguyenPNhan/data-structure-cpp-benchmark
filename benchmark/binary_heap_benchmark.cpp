#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<BinaryHeap>("Binary Heap");
}

/*
random: Binary Heap - 1.066ms
increasing: Binary Heap - 0.925ms
small shuffle: Binary Heap - 0.888ms
remove: Binary Heap - 0.525ms
search all: Binary Heap - 0.715ms
small search large insert: Binary Heap - 0.106ms
large search small insert: Binary Heap - 0.249ms

size: 10000
random: Binary Heap - 114.352ms
increasing: Binary Heap - 110.027ms
small shuffle: Binary Heap - 91.101ms
remove: Binary Heap - 55.869ms
search all: Binary Heap - 72.992ms
small search large insert: Binary Heap - 6.865ms
large search small insert: Binary Heap - 13.074ms

size: 20000
random: Binary Heap - 355.856ms
increasing: Binary Heap - 305.276ms
small shuffle: Binary Heap - 317.014ms
remove: Binary Heap - 137.042ms
search all: Binary Heap - 265.826ms
small search large insert: Binary Heap - 26.075ms
large search small insert: Binary Heap - 58.054ms

size: 50000
random: Binary Heap - 1786.387ms
increasing: Binary Heap - 1766.701ms
small shuffle: Binary Heap - 1659.293ms
remove: Binary Heap - 822.321ms
search all: Binary Heap - 1619.099ms
small search large insert: Binary Heap - 154.020ms
large search small insert: Binary Heap - 311.854ms

size: 100000
random: Binary Heap - 6625.843ms
increasing: Binary Heap - 6528.300ms
small shuffle: Binary Heap - 6636.951ms
remove: Binary Heap - 3537.029ms
search all: Binary Heap - 12889.077ms
small search large insert: Binary Heap - 1476.098ms
large search small insert: Binary Heap - 2882.314ms

size: 200000
random: Binary Heap - 49268.174ms
increasing: Binary Heap - 26365.471ms
small shuffle: Binary Heap - 46907.010ms
remove: Binary Heap - 23781.746ms
search all: Binary Heap - 49491.568ms
small search large insert: Binary Heap - 3108.333ms
large search small insert: Binary Heap - 5866.317ms
*/