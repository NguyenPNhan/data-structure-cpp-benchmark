#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<Treap>("Treap");
}
/*
size: 1000
random: Treap - 0.228ms
increasing: Treap - 0.160ms
small shuffle: Treap - 0.152ms
remove: Treap - 0.155ms
search all: Treap - 0.123ms
small search large insert: Treap - 0.013ms
large search small insert: Treap - 0.088ms

size: 10000
random: Treap - 3.850ms
increasing: Treap - 2.740ms
small shuffle: Treap - 4.759ms
remove: Treap - 5.625ms
search all: Treap - 4.088ms
small search large insert: Treap - 0.543ms
large search small insert: Treap - 1.273ms

size: 20000
random: Treap - 6.055ms
increasing: Treap - 3.321ms
small shuffle: Treap - 5.790ms
remove: Treap - 8.608ms
search all: Treap - 4.261ms
small search large insert: Treap - 0.298ms
large search small insert: Treap - 2.913ms

size: 50000
random: Treap - 20.060ms
increasing: Treap - 4.971ms
small shuffle: Treap - 10.472ms
remove: Treap - 20.176ms
search all: Treap - 16.205ms
small search large insert: Treap - 1.019ms
large search small insert: Treap - 6.378ms

size: 100000
random: Treap - 59.728ms
increasing: Treap - 12.414ms
small shuffle: Treap - 25.387ms
remove: Treap - 62.580ms
search all: Treap - 50.772ms
small search large insert: Treap - 3.808ms
large search small insert: Treap - 16.288ms

size: 200000
random: Treap - 212.087ms
increasing: Treap - 23.595ms
small shuffle: Treap - 62.130ms
remove: Treap - 212.377ms
search all: Treap - 137.778ms
small search large insert: Treap - 9.841ms
large search small insert: Treap - 44.332ms
*/