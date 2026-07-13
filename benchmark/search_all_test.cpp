#include "benchmark_common.h"

int main() {
    try {
        const std::vector<std::size_t>& allSizes = benchmark::sizes();

        for (std::size_t index = 0; index < allSizes.size(); ++index) {
            const std::size_t size = allSizes[index];
            const std::vector<int> values =
                benchmark::randomValues(size, 0x89abcdefu);

            benchmark::printSize(size);
            benchmark::runSearchCase("search all", values, values, size);
            std::cout << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "benchmark failed: " << error.what() << '\n';
        return 1;
    }
}
