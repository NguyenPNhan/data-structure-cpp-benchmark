#include "benchmark_common.h"

int main() {
    return benchmark::runAllBenchmarks<AdelsonVelskyLandisTree>(
        "Adelson-Velsky-Landis Tree"
    );
}
