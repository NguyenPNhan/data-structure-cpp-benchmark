# Data Structure Benchmark in C++

This project implements several data structures behind one set-like interface and compares their running time for insertion, removal, and search workloads.

Every structure implements [`DataStructure`](data_structure.h):

```cpp
virtual void insert(int value) = 0;
virtual void remove(int value) = 0;
virtual bool search(int value) const = 0;
```

The benchmark uses unique positive integers from `1` to `N`. It is intended as an educational comparison of these implementations, not as a replacement for production containers or a statistically rigorous benchmark suite.

## Implemented data structures

| Data structure | Header | Expected operation cost |
|---|---|---|
| Adelson-Velsky-Landis (AVL) tree | [`adelson_velsky_landis_tree.h`](adelson_velsky_landis_tree.h) | `O(log N)` insert, remove, and search |
| Binary heap | [`binary_heap.h`](binary_heap.h) | `O(N)` for this interface because duplicate checks, arbitrary removal, and search scan the heap |
| Binary search tree | [`binary_search_tree.h`](binary_search_tree.h) | Average `O(log N)`, worst-case `O(N)` |
| Binary search trie | [`binary_search_trie.h`](binary_search_trie.h) | `O(W)`, where `W` is the fixed integer bit width |
| Cuckoo hash table | [`cuckoo_hash_table.h`](cuckoo_hash_table.h) | Average `O(1)`; insertion may trigger a rebuild |
| Hash table with separate chaining | [`hash_table.h`](hash_table.h) | Average `O(1)`, worst-case `O(N)` |
| Linked list | [`linked_list.h`](linked_list.h) | `O(N)` insert, remove, and search |
| Red-black tree | [`red_black_tree.h`](red_black_tree.h) | `O(log N)` insert, remove, and search |
| Sorted array | [`sorted_array.h`](sorted_array.h) | `O(N)` insert/remove and `O(log N)` search |
| Splay tree | [`splay_tree.h`](splay_tree.h) | Amortized `O(log N)`, worst-case `O(N)` per operation |
| Treap | [`treap.h`](treap.h) | Expected `O(log N)`, worst-case `O(N)` |

## Benchmark methodology

The shared harness is in [`benchmark/benchmark_common.h`](benchmark/benchmark_common.h). Each structure is tested at `1,000`, `10,000`, `20,000`, `50,000`, `100,000`, and `200,000` elements.

The workloads are:

- **Random:** insert a deterministic random permutation of `1..N`.
- **Increasing:** insert `1..N` in sorted order.
- **Small shuffle:** start with increasing values and shuffle values at 10% of the positions.
- **Remove:** build from a random permutation, then remove all values in a different random order.
- **Search all:** insert and search all `N` values; every search is a hit.
- **Small search, large insert:** insert `N` values and search for `N / 10` present values.
- **Large search, small insert:** insert `N / 10` values, then search `N` values; `N / 10` searches are hits.

Input generation, structure setup for remove/search tests, and correctness validation are outside the timed regions. Only the operation loop is measured with `std::chrono::steady_clock`. Random inputs use fixed seeds, so the ordering is reproducible for a given size.

## Recorded results

The following table summarizes the recorded results at `N = 200,000`. Times are milliseconds; lower is better. The fastest recorded time in each column is bold.

| Data structure | Random insert | Increasing insert | Small-shuffle insert | Remove all | Search all | Search 20K after insert 200K | Search 200K after insert 20K |
|---|---:|---:|---:|---:|---:|---:|---:|
| AVL tree | 209.581 | 125.422 | 140.832 | 193.093 | 60.978 | 4.495 | 40.908 |
| Binary heap | 49,268.174 | 26,365.471 | 46,907.010 | 23,781.746 | 49,491.568 | 3,108.333 | 5,866.317 |
| Binary search tree | 100.055 | 80,650.451 | 109.879 | 75.925 | 66.792 | 4.068 | 55.263 |
| Binary search trie | 135.799 | 60.664 | 66.421 | 196.225 | 68.526 | 3.692 | 58.553 |
| Cuckoo hash table | 100.413 | 46.978 | 52.721 | **7.049** | **7.673** | 0.991 | **6.419** |
| Hash table | **45.156** | 34.262 | **38.824** | 46.434 | 9.057 | **0.941** | 6.690 |
| Linked list | 239,096.158 | 189,989.965 | 203,731.769 | 149,494.633 | 192,294.934 | 1,556.710 | 30,639.021 |
| Red-black tree | 103.976 | 82.447 | 51.298 | 150.760 | 92.733 | 9.013 | 42.202 |
| Sorted array | 16,057.895 | **17.308** | 1,814.581 | 33,198.501 | 57.103 | 3.404 | 36.153 |
| Splay tree | 152.234 | 38.274 | 66.842 | 238.230 | 119.834 | 20.303 | 76.031 |
| Treap | 212.087 | 23.595 | 62.130 | 212.377 | 137.778 | 9.841 | 44.332 |

The complete recorded output for every tested size is stored at the bottom of each `benchmark/*_benchmark.cpp` file.

### Observations

- The regular hash table recorded the fastest random and small-shuffle insert times at `N = 200,000`.
- The cuckoo hash table recorded the fastest full removal and full search times.
- The sorted array is especially fast for increasing insertion because each new value is appended, but arbitrary insertion and removal require shifting elements.
- Increasing input degenerates the unbalanced binary search tree into a chain, increasing its recorded insertion time to about 80.7 seconds.
- A heap is designed for efficient access to its minimum element. The common benchmark instead requires arbitrary membership search and removal, both of which need a linear scan in this implementation.

Timings depend on the compiler, optimization flags, operating system, CPU, memory, and background load. These values came from one recorded run and are not averaged across repetitions, so compare results measured on the same machine and toolchain.

## Build and run

A C++17-compatible compiler is sufficient. No external libraries are required.

Compile and run one benchmark with MinGW/GCC from the project root:

```powershell
g++ -std=c++17 -O2 benchmark\treap_benchmark.cpp -o benchmark\treap_benchmark.exe
.\benchmark\treap_benchmark.exe
```

To compile every benchmark in PowerShell:

```powershell
Get-ChildItem benchmark\*_benchmark.cpp | ForEach-Object {
    $output = Join-Path $_.DirectoryName ($_.BaseName + ".exe")
    g++ -std=c++17 -O2 $_.FullName -o $output
}
```

Run all compiled benchmarks:

```powershell
Get-ChildItem benchmark\*_benchmark.exe | ForEach-Object {
    & $_.FullName
}
```

Some `N = 200,000` tests take several minutes, particularly the linked-list workloads.

## Project layout

```text
.
|-- data_structure.h          # Common interface
|-- *.h                       # Header-only data structure implementations
`-- benchmark/
    |-- benchmark_common.h    # Shared data generation and timing harness
    `-- *_benchmark.cpp       # One executable and recorded output per structure
```

