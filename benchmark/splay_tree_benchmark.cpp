#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<SplayTree>("Splay Tree");
}
/*
size: 1000
random: Splay Tree - 0.233ms
increasing: Splay Tree - 0.096ms
small shuffle: Splay Tree - 0.082ms
remove: Splay Tree - 0.173ms
search all: Splay Tree - 0.154ms
small search large insert: Splay Tree - 0.015ms
large search small insert: Splay Tree - 0.098ms

size: 10000
random: Splay Tree - 2.659ms
increasing: Splay Tree - 0.487ms
small shuffle: Splay Tree - 0.829ms
remove: Splay Tree - 4.514ms
search all: Splay Tree - 5.625ms
small search large insert: Splay Tree - 0.437ms
large search small insert: Splay Tree - 4.285ms

size: 20000
random: Splay Tree - 7.578ms
increasing: Splay Tree - 1.090ms
small shuffle: Splay Tree - 2.942ms
remove: Splay Tree - 7.003ms
search all: Splay Tree - 5.774ms
small search large insert: Splay Tree - 0.583ms
large search small insert: Splay Tree - 3.380ms

size: 50000
random: Splay Tree - 23.421ms
increasing: Splay Tree - 4.062ms
small shuffle: Splay Tree - 5.067ms
remove: Splay Tree - 20.973ms
search all: Splay Tree - 15.226ms
small search large insert: Splay Tree - 1.504ms
large search small insert: Splay Tree - 12.225ms

size: 100000
random: Splay Tree - 64.253ms
increasing: Splay Tree - 7.324ms
small shuffle: Splay Tree - 11.777ms
remove: Splay Tree - 74.083ms
search all: Splay Tree - 40.970ms
small search large insert: Splay Tree - 3.840ms
large search small insert: Splay Tree - 23.539ms

size: 200000
random: Splay Tree - 152.234ms
increasing: Splay Tree - 38.274ms
small shuffle: Splay Tree - 66.842ms
remove: Splay Tree - 238.230ms
search all: Splay Tree - 119.834ms
small search large insert: Splay Tree - 20.303ms
large search small insert: Splay Tree - 76.031ms
*/