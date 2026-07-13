#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<CuckooHashTable>(
        "Cuckoo Hash Table"
    );
}
/*
size: 1000
random: Cuckoo Hash Table - 0.240ms
increasing: Cuckoo Hash Table - 0.180ms
small shuffle: Cuckoo Hash Table - 0.248ms
remove: Cuckoo Hash Table - 0.043ms
search all: Cuckoo Hash Table - 0.040ms
small search large insert: Cuckoo Hash Table - 0.005ms
large search small insert: Cuckoo Hash Table - 0.044ms

size: 10000
random: Cuckoo Hash Table - 2.278ms
increasing: Cuckoo Hash Table - 1.899ms
small shuffle: Cuckoo Hash Table - 2.569ms
remove: Cuckoo Hash Table - 0.424ms
search all: Cuckoo Hash Table - 0.386ms
small search large insert: Cuckoo Hash Table - 0.035ms
large search small insert: Cuckoo Hash Table - 0.276ms

size: 20000
random: Cuckoo Hash Table - 3.502ms
increasing: Cuckoo Hash Table - 6.888ms
small shuffle: Cuckoo Hash Table - 4.200ms
remove: Cuckoo Hash Table - 0.873ms
search all: Cuckoo Hash Table - 1.194ms
small search large insert: Cuckoo Hash Table - 0.060ms
large search small insert: Cuckoo Hash Table - 0.465ms

size: 50000
random: Cuckoo Hash Table - 12.284ms
increasing: Cuckoo Hash Table - 10.995ms
small shuffle: Cuckoo Hash Table - 14.216ms
remove: Cuckoo Hash Table - 3.028ms
search all: Cuckoo Hash Table - 1.871ms
small search large insert: Cuckoo Hash Table - 0.171ms
large search small insert: Cuckoo Hash Table - 1.173ms

size: 100000
random: Cuckoo Hash Table - 18.970ms
increasing: Cuckoo Hash Table - 18.855ms
small shuffle: Cuckoo Hash Table - 23.320ms
remove: Cuckoo Hash Table - 4.023ms
search all: Cuckoo Hash Table - 5.426ms
small search large insert: Cuckoo Hash Table - 0.359ms
large search small insert: Cuckoo Hash Table - 2.522ms

size: 200000
random: Cuckoo Hash Table - 100.413ms
increasing: Cuckoo Hash Table - 46.978ms
small shuffle: Cuckoo Hash Table - 52.721ms
remove: Cuckoo Hash Table - 7.049ms
search all: Cuckoo Hash Table - 7.673ms
small search large insert: Cuckoo Hash Table - 0.991ms
large search small insert: Cuckoo Hash Table - 6.419ms
*/