#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<RedBlackTree>("Red-Black Tree");
}
/*
size: 1000
random: Red-Black Tree - 0.545ms
increasing: Red-Black Tree - 0.410ms
small shuffle: Red-Black Tree - 0.470ms
remove: Red-Black Tree - 0.518ms
search all: Red-Black Tree - 0.314ms
small search large insert: Red-Black Tree - 0.027ms
large search small insert: Red-Black Tree - 0.126ms

size: 10000
random: Red-Black Tree - 4.912ms
increasing: Red-Black Tree - 1.691ms
small shuffle: Red-Black Tree - 5.903ms
remove: Red-Black Tree - 7.073ms
search all: Red-Black Tree - 4.092ms
small search large insert: Red-Black Tree - 0.210ms
large search small insert: Red-Black Tree - 1.573ms

size: 20000
random: Red-Black Tree - 6.005ms
increasing: Red-Black Tree - 4.210ms
small shuffle: Red-Black Tree - 3.930ms
remove: Red-Black Tree - 4.225ms
search all: Red-Black Tree - 3.215ms
small search large insert: Red-Black Tree - 0.306ms
large search small insert: Red-Black Tree - 3.301ms

size: 50000
random: Red-Black Tree - 19.748ms
increasing: Red-Black Tree - 8.997ms
small shuffle: Red-Black Tree - 12.560ms
remove: Red-Black Tree - 20.135ms
search all: Red-Black Tree - 14.456ms
small search large insert: Red-Black Tree - 0.922ms
large search small insert: Red-Black Tree - 6.644ms

size: 100000
random: Red-Black Tree - 41.055ms
increasing: Red-Black Tree - 19.234ms
small shuffle: Red-Black Tree - 26.899ms
remove: Red-Black Tree - 55.254ms
search all: Red-Black Tree - 47.631ms
small search large insert: Red-Black Tree - 3.015ms
large search small insert: Red-Black Tree - 24.746ms

size: 200000
random: Red-Black Tree - 103.976ms
increasing: Red-Black Tree - 82.447ms
small shuffle: Red-Black Tree - 51.298ms
remove: Red-Black Tree - 150.760ms
search all: Red-Black Tree - 92.733ms
small search large insert: Red-Black Tree - 9.013ms
large search small insert: Red-Black Tree - 42.202ms
*/