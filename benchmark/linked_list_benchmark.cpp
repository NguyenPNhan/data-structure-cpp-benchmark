#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<LinkedList>("Linked List");
}
/*
size: 1000
random: Linked List - 1.233ms
increasing: Linked List - 1.156ms
small shuffle: Linked List - 1.122ms
remove: Linked List - 0.617ms
search all: Linked List - 1.421ms
small search large insert: Linked List - 0.015ms
large search small insert: Linked List - 0.372ms

size: 10000
random: Linked List - 249.070ms
increasing: Linked List - 350.038ms
small shuffle: Linked List - 252.094ms
remove: Linked List - 146.455ms
search all: Linked List - 254.887ms
small search large insert: Linked List - 1.545ms
large search small insert: Linked List - 28.031ms

size: 20000
random: Linked List - 1014.816ms
increasing: Linked List - 939.239ms
small shuffle: Linked List - 943.689ms
remove: Linked List - 548.423ms
search all: Linked List - 870.487ms
small search large insert: Linked List - 6.829ms
large search small insert: Linked List - 182.954ms

size: 50000
random: Linked List - 5748.831ms
increasing: Linked List - 5506.992ms
small shuffle: Linked List - 5511.159ms
remove: Linked List - 3406.459ms
search all: Linked List - 5850.960ms
small search large insert: Linked List - 57.319ms
large search small insert: Linked List - 1054.662ms

size: 100000
random: Linked List - 23708.533ms
increasing: Linked List - 25519.185ms
small shuffle: Linked List - 48591.745ms
remove: Linked List - 35064.993ms
search all: Linked List - 39822.952ms
small search large insert: Linked List - 421.506ms
large search small insert: Linked List - 14638.014ms

size: 200000
random: Linked List - 239096.158ms
increasing: Linked List - 189989.965ms
small shuffle: Linked List - 203731.769ms
remove: Linked List - 149494.633ms
search all: Linked List - 192294.934ms
small search large insert: Linked List - 1556.710ms
large search small insert: Linked List - 30639.021ms
*/