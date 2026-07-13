#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<SortedArray>("Sorted Array");
}
/*
size: 1000
random: Sorted Array - 0.571ms
increasing: Sorted Array - 0.036ms
small shuffle: Sorted Array - 0.092ms
remove: Sorted Array - 0.496ms
search all: Sorted Array - 0.101ms
small search large insert: Sorted Array - 0.010ms
large search small insert: Sorted Array - 0.061ms

size: 10000
random: Sorted Array - 36.562ms
increasing: Sorted Array - 0.558ms
small shuffle: Sorted Array - 5.337ms
remove: Sorted Array - 36.920ms
search all: Sorted Array - 1.261ms
small search large insert: Sorted Array - 0.132ms
large search small insert: Sorted Array - 0.950ms

size: 20000
random: Sorted Array - 157.016ms
increasing: Sorted Array - 1.915ms
small shuffle: Sorted Array - 24.032ms
remove: Sorted Array - 151.002ms
search all: Sorted Array - 5.627ms
small search large insert: Sorted Array - 0.276ms
large search small insert: Sorted Array - 1.989ms

size: 50000
random: Sorted Array - 1037.721ms
increasing: Sorted Array - 4.156ms
small shuffle: Sorted Array - 131.914ms
remove: Sorted Array - 1120.423ms
search all: Sorted Array - 11.089ms
small search large insert: Sorted Array - 0.879ms
large search small insert: Sorted Array - 8.052ms

size: 100000
random: Sorted Array - 3868.145ms
increasing: Sorted Array - 6.024ms
small shuffle: Sorted Array - 483.297ms
remove: Sorted Array - 4258.419ms
search all: Sorted Array - 17.726ms
small search large insert: Sorted Array - 2.480ms
large search small insert: Sorted Array - 14.431ms

size: 200000
random: Sorted Array - 16057.895ms
increasing: Sorted Array - 17.308ms
small shuffle: Sorted Array - 1814.581ms
remove: Sorted Array - 33198.501ms
search all: Sorted Array - 57.103ms
small search large insert: Sorted Array - 3.404ms
large search small insert: Sorted Array - 36.153ms
*/