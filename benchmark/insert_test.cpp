#include "benchmark_common.h"

int main() {
    try {
        const std::vector<std::size_t>& allSizes = benchmark::sizes();

        for (std::size_t index = 0; index < allSizes.size(); ++index) {
            const std::size_t size = allSizes[index];
            const std::vector<int> random =
                benchmark::randomValues(size, 0x13579bdfu);
            const std::vector<int> increasing =
                benchmark::increasingValues(size);
            const std::vector<int> smallShuffle =
                benchmark::smallShuffleValues(size, 0x2468ace0u);

            benchmark::printSize(size);
            benchmark::runInsertCase("random", random);
            benchmark::runInsertCase("increasing", increasing);
            benchmark::runInsertCase("small shuffle", smallShuffle);
            std::cout << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "benchmark failed: " << error.what() << '\n';
        return 1;
    }
}
