#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<BinarySearchTree>(
        "Binary Search Tree"
    );
}
/*
size: 1000
random: Binary Search Tree - 0.287ms
increasing: Binary Search Tree - 1.389ms
small shuffle: Binary Search Tree - 0.224ms
remove: Binary Search Tree - 0.216ms
search all: Binary Search Tree - 0.114ms
small search large insert: Binary Search Tree - 0.011ms
large search small insert: Binary Search Tree - 0.330ms

size: 10000
random: Binary Search Tree - 3.705ms
increasing: Binary Search Tree - 203.907ms
small shuffle: Binary Search Tree - 3.761ms
remove: Binary Search Tree - 2.542ms
search all: Binary Search Tree - 1.498ms
small search large insert: Binary Search Tree - 0.182ms
large search small insert: Binary Search Tree - 1.284ms

size: 20000
random: Binary Search Tree - 5.310ms
increasing: Binary Search Tree - 981.886ms
small shuffle: Binary Search Tree - 8.040ms
remove: Binary Search Tree - 6.736ms
search all: Binary Search Tree - 5.321ms
small search large insert: Binary Search Tree - 0.289ms
large search small insert: Binary Search Tree - 3.340ms

size: 50000
random: Binary Search Tree - 25.526ms
increasing: Binary Search Tree - 4920.155ms
small shuffle: Binary Search Tree - 42.271ms
remove: Binary Search Tree - 30.780ms
search all: Binary Search Tree - 19.591ms
small search large insert: Binary Search Tree - 0.683ms
large search small insert: Binary Search Tree - 16.747ms

size: 100000
random: Binary Search Tree - 47.997ms
increasing: Binary Search Tree - 19560.315ms
small shuffle: Binary Search Tree - 53.581ms
remove: Binary Search Tree - 36.607ms
search all: Binary Search Tree - 33.983ms
small search large insert: Binary Search Tree - 2.046ms
large search small insert: Binary Search Tree - 21.095ms

size: 200000
random: Binary Search Tree - 100.055ms
increasing: Binary Search Tree - 80650.451ms
small shuffle: Binary Search Tree - 109.879ms
remove: Binary Search Tree - 75.925ms
search all: Binary Search Tree - 66.792ms
small search large insert: Binary Search Tree - 4.068ms
large search small insert: Binary Search Tree - 55.263ms
*/