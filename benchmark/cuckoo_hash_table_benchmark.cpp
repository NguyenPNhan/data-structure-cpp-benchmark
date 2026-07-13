#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<CuckooHashTable>(
        "Cuckoo Hash Table"
    );
}
