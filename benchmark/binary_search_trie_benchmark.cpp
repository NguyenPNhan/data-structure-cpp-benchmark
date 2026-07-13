#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<BinarySearchTrie>(
        "Binary Search Trie"
    );
}
/*
size: 1000
random: Binary Search Trie - 0.410ms
increasing: Binary Search Trie - 0.379ms
small shuffle: Binary Search Trie - 0.332ms
remove: Binary Search Trie - 0.464ms
search all: Binary Search Trie - 0.098ms
small search large insert: Binary Search Trie - 0.017ms
large search small insert: Binary Search Trie - 0.203ms

size: 10000
random: Binary Search Trie - 4.636ms
increasing: Binary Search Trie - 2.811ms
small shuffle: Binary Search Trie - 2.437ms
remove: Binary Search Trie - 3.712ms
search all: Binary Search Trie - 1.452ms
small search large insert: Binary Search Trie - 0.142ms
large search small insert: Binary Search Trie - 1.172ms

size: 20000
random: Binary Search Trie - 9.251ms
increasing: Binary Search Trie - 4.090ms
small shuffle: Binary Search Trie - 7.748ms
remove: Binary Search Trie - 10.720ms
search all: Binary Search Trie - 3.950ms
small search large insert: Binary Search Trie - 0.167ms
large search small insert: Binary Search Trie - 3.333ms

size: 50000
random: Binary Search Trie - 26.100ms
increasing: Binary Search Trie - 18.480ms
small shuffle: Binary Search Trie - 13.757ms
remove: Binary Search Trie - 27.567ms
search all: Binary Search Trie - 7.856ms
small search large insert: Binary Search Trie - 0.916ms
large search small insert: Binary Search Trie - 8.701ms

size: 100000
random: Binary Search Trie - 67.497ms
increasing: Binary Search Trie - 35.683ms
small shuffle: Binary Search Trie - 45.822ms
remove: Binary Search Trie - 131.213ms
search all: Binary Search Trie - 45.883ms
small search large insert: Binary Search Trie - 1.539ms
large search small insert: Binary Search Trie - 21.476ms

size: 200000
random: Binary Search Trie - 135.799ms
increasing: Binary Search Trie - 60.664ms
small shuffle: Binary Search Trie - 66.421ms
remove: Binary Search Trie - 196.225ms
search all: Binary Search Trie - 68.526ms
small search large insert: Binary Search Trie - 3.692ms
large search small insert: Binary Search Trie - 58.553ms
*/