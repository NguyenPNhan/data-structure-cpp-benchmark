#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<HashTable>("Hash Table");
}
/*
size: 1000
random: Hash Table - 0.154ms
increasing: Hash Table - 0.108ms
small shuffle: Hash Table - 0.493ms
remove: Hash Table - 0.040ms
search all: Hash Table - 0.018ms
small search large insert: Hash Table - 0.002ms
large search small insert: Hash Table - 0.024ms

size: 10000
random: Hash Table - 1.795ms
increasing: Hash Table - 1.377ms
small shuffle: Hash Table - 0.914ms
remove: Hash Table - 0.403ms
search all: Hash Table - 0.156ms
small search large insert: Hash Table - 0.024ms
large search small insert: Hash Table - 0.209ms

size: 20000
random: Hash Table - 2.493ms
increasing: Hash Table - 1.593ms
small shuffle: Hash Table - 2.431ms
remove: Hash Table - 0.868ms
search all: Hash Table - 0.304ms
small search large insert: Hash Table - 0.048ms
large search small insert: Hash Table - 0.646ms

size: 50000
random: Hash Table - 7.749ms
increasing: Hash Table - 7.409ms
small shuffle: Hash Table - 8.649ms
remove: Hash Table - 5.704ms
search all: Hash Table - 1.493ms
small search large insert: Hash Table - 0.095ms
large search small insert: Hash Table - 1.347ms

size: 100000
random: Hash Table - 28.015ms
increasing: Hash Table - 22.793ms
small shuffle: Hash Table - 20.937ms
remove: Hash Table - 10.570ms
search all: Hash Table - 3.052ms
small search large insert: Hash Table - 1.183ms
large search small insert: Hash Table - 3.901ms

size: 200000
random: Hash Table - 45.156ms
increasing: Hash Table - 34.262ms
small shuffle: Hash Table - 38.824ms
remove: Hash Table - 46.434ms
search all: Hash Table - 9.057ms
small search large insert: Hash Table - 0.941ms
large search small insert: Hash Table - 6.690ms
*/