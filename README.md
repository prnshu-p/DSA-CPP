# DSA-C++

My personal collection of data structures, algorithms, and competitive programming solutions in C++. Built over time as I work through topics — from fundamentals to contest-level problems.

This isn't a library or a framework. It's a working notebook: the kind of repo you actually use during practice, not one designed to look good on a portfolio.

## What's in here

### Templates and implementations

| Directory | What it covers |
|-----------|---------------|
| `Graphs/` | BFS, DFS, cycle detection, topological sort, Dijkstra, Bellman-Ford, Prim's, Kruskal's, DSU (standard + parity) |
| `Trees/` | Binary tree traversals, height, subtree operations, top view, sum tree |
| `dynamic_programming/` | Knapsack (0/1 and unbounded), LIS, LCS, coin change, subset sum, rod cutting, frog problems |
| `practise(functions)/` | Number base conversions, GCD, bitwise operations |
| `String/` | String basics, case conversion |

Standalone template files at root level:

- `BIT.cpp` — Binary Indexed Tree (Fenwick Tree)
- `segment_trees.cpp` — Segment tree with point update and range query
- `segment_trees_2.cpp` — Generic segment tree with custom node type and merge
- `binary_lifting.cpp` — K-th ancestor queries in O(log N)
- `LCA_BinaryLifting.cpp` — Lowest Common Ancestor via binary lifting
- `MonotonicStack.cpp` — Monotonic stack template for next greater/smaller element

### Solved problems

| Directory | What's there |
|-----------|-------------|
| `cses_problems/` | ~35 problems from the CSES Problem Set |
| `USACO_ques/` | USACO contest problems — Cow Checkups, Email Filing, Redistributing Gifts, Robot Instructions, Sleeping in Class, etc. |
| `codeforces_problems/` | Codeforces specific problems — Tree with Maximum Cost, Roads not only in Berland, etc. |
| `atcoder_dp/` | AtCoder Educational DP Contest problems |
| `questions/` | Miscellaneous problems from SPOJ, UVa, POJ, and general practice |

### Topics covered so far

- Graphs (traversal, shortest paths, MST, DSU, bipartite checking)
- Trees (Euler tour, subtree/path queries with BIT, binary lifting, LCA)
- Segment trees (point update, range queries, walk, max subarray, prefix max)
- Fenwick trees (range sum, range update, coordinate compression, inversion count)
- Dynamic programming (classical problems, optimization patterns)
- Disjoint Set Union (standard, parity/bipartite, weighted, reverse-time)

## Structure

```
.
├── Graphs/                  # Graph algorithm templates
├── Trees/                   # Binary tree implementations
├── dynamic_programming/     # DP problems and patterns
├── practise(functions)/     # Math and utility functions
├── String/                  # String operations
├── cses_problems/           # CSES Problem Set solutions
├── USACO_ques/              # USACO contest solutions
├── codeforces_problems/     # Codeforces specific solutions
├── atcoder_dp/              # AtCoder Educational DP Contest solutions
├── questions/               # Miscellaneous & general practice problems
├── BIT.cpp                  # Fenwick tree template
├── segment_trees.cpp        # Segment tree template
├── segment_trees_2.cpp      # Advanced segment tree template
├── binary_lifting.cpp       # K-th ancestor template
├── LCA_BinaryLifting.cpp    # LCA template
└── MonotonicStack.cpp       # Monotonic stack template
```

## Running

These are standalone `.cpp` files. Compile and run any of them directly:

```bash
g++ -std=c++17 -O2 -o solution questions/SalaryQueries.cpp
./solution < input.txt
```

No build system, no dependencies, no setup. Just a compiler.

## Status

This is an active repo — I add to it as I learn new topics and solve new problems. It's not "complete" and probably never will be.
