#include "benchmark_common.h"

int main() {
    try {
        const std::vector<std::size_t>& allSizes = benchmark::sizes();

        for (std::size_t index = 0; index < allSizes.size(); ++index) {
            const std::size_t size = allSizes[index];
            const std::vector<int> searchedValues =
                benchmark::randomValues(size, 0x27182818u);
            const std::size_t insertCount = size / 10;
            const std::vector<int> insertedValues(
                searchedValues.begin(),
                searchedValues.begin() + insertCount
            );

            benchmark::printSize(size);
            benchmark::runSearchCase(
                "large search small insert",
                insertedValues,
                searchedValues,
                insertCount
            );
            std::cout << '\n';
        }
    } catch (const std::exception& error) {
        std::cerr << "benchmark failed: " << error.what() << '\n';
        return 1;
    }
}
