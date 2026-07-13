#include "benchmark_common.h"

int main() {
    try {
        const std::vector<std::size_t>& allSizes = benchmark::sizes();

        for (std::size_t index = 0; index < allSizes.size(); ++index) {
            const std::size_t size = allSizes[index];
            const std::vector<int> insertedValues =
                benchmark::randomValues(size, 0x31415926u);
            const std::size_t searchCount = size / 10;
            const std::vector<int> searchedValues(
                insertedValues.begin(),
                insertedValues.begin() + searchCount
            );

            benchmark::printSize(size);
            benchmark::runSearchCase(
                "small search large insert",
                insertedValues,
                searchedValues,
                searchCount
            );
            std::cout << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "benchmark failed: " << error.what() << '\n';
        return 1;
    }
}
