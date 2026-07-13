#include "benchmark_common.h"

int main() {
    try {
        const std::vector<std::size_t>& allSizes = benchmark::sizes();

        for (std::size_t index = 0; index < allSizes.size(); ++index) {
            const std::size_t size = allSizes[index];
            const std::vector<int> insertedValues =
                benchmark::randomValues(size, 0x10203040u);
            const std::vector<int> removedValues =
                benchmark::randomValues(size, 0x50607080u);

            benchmark::printSize(size);
            benchmark::runRemoveCase(insertedValues, removedValues);
            std::cout << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "benchmark failed: " << error.what() << '\n';
        return 1;
    }
}
