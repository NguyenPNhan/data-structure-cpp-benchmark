#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<AdelsonVelskyLandisTree>(
        "Adelson-Velsky-Landis Tree"
    );
}
/*
size: 1000
random: Adelson-Velsky-Landis Tree - 0.415ms
increasing: Adelson-Velsky-Landis Tree - 0.354ms
small shuffle: Adelson-Velsky-Landis Tree - 0.363ms
remove: Adelson-Velsky-Landis Tree - 0.383ms
search all: Adelson-Velsky-Landis Tree - 0.135ms
small search large insert: Adelson-Velsky-Landis Tree - 0.013ms
large search small insert: Adelson-Velsky-Landis Tree - 0.087ms

size: 10000
random: Adelson-Velsky-Landis Tree - 6.269ms
increasing: Adelson-Velsky-Landis Tree - 5.298ms
small shuffle: Adelson-Velsky-Landis Tree - 6.986ms
remove: Adelson-Velsky-Landis Tree - 5.008ms
search all: Adelson-Velsky-Landis Tree - 1.840ms
small search large insert: Adelson-Velsky-Landis Tree - 0.117ms
large search small insert: Adelson-Velsky-Landis Tree - 1.370ms

size: 20000
random: Adelson-Velsky-Landis Tree - 11.726ms
increasing: Adelson-Velsky-Landis Tree - 13.469ms
small shuffle: Adelson-Velsky-Landis Tree - 10.813ms
remove: Adelson-Velsky-Landis Tree - 14.064ms
search all: Adelson-Velsky-Landis Tree - 3.755ms
small search large insert: Adelson-Velsky-Landis Tree - 0.267ms
large search small insert: Adelson-Velsky-Landis Tree - 2.920ms

size: 50000
random: Adelson-Velsky-Landis Tree - 37.101ms
increasing: Adelson-Velsky-Landis Tree - 26.823ms
small shuffle: Adelson-Velsky-Landis Tree - 37.630ms
remove: Adelson-Velsky-Landis Tree - 34.161ms
search all: Adelson-Velsky-Landis Tree - 13.565ms
small search large insert: Adelson-Velsky-Landis Tree - 1.242ms
large search small insert: Adelson-Velsky-Landis Tree - 11.540ms

size: 100000
random: Adelson-Velsky-Landis Tree - 118.988ms
increasing: Adelson-Velsky-Landis Tree - 75.040ms
small shuffle: Adelson-Velsky-Landis Tree - 103.462ms
remove: Adelson-Velsky-Landis Tree - 123.518ms
search all: Adelson-Velsky-Landis Tree - 33.435ms
small search large insert: Adelson-Velsky-Landis Tree - 4.460ms
large search small insert: Adelson-Velsky-Landis Tree - 37.146ms

size: 200000
random: Adelson-Velsky-Landis Tree - 209.581ms
increasing: Adelson-Velsky-Landis Tree - 125.422ms
small shuffle: Adelson-Velsky-Landis Tree - 140.832ms
remove: Adelson-Velsky-Landis Tree - 193.093ms
search all: Adelson-Velsky-Landis Tree - 60.978ms
small search large insert: Adelson-Velsky-Landis Tree - 4.495ms
large search small insert: Adelson-Velsky-Landis Tree - 40.908ms
*/