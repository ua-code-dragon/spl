# IEEEXtreme Handbook — algorithms in C

A compact guide to the algorithms that IEEEXtreme tasks require, written for
students who program in plain C. It goes with:

| Path | What it is |
|---|---|
| [`docs/en/tasks.md`](tasks.md), [`docs/en/tasks.csv`](tasks.csv) | All 252 archive tasks (IEEEXtreme 10.0–19.0) classified by topic, with links and solve rates |
| [`lib/`](../../lib) | The helper library: 29 small header files (< 100 kB), static memory only |
| [`examples/`](../../examples) | 23 complete, tested programs (`NAME.c` + `NAME.in` + `NAME.out`) |
| [`tools/bundle.py`](../../tools/bundle.py) | Turns a solution that `#include`s library headers into one file for submission |
| [`tests/`](../../tests) | Self-checks of the library and the examples |

## Contents

1. [The contest and this kit](#1-the-contest-and-this-kit)
2. [C for contests](#2-c-for-contests)
3. [Sorting and searching](#3-sorting-and-searching)
4. [Greedy algorithms](#4-greedy-algorithms)
5. [Prefix sums, two pointers, sliding windows](#5-prefix-sums-two-pointers-sliding-windows)
6. [Data structures](#6-data-structures)
7. [Dynamic programming](#7-dynamic-programming)
8. [Graphs](#8-graphs)
9. [Trees](#9-trees)
10. [Strings](#10-strings)
11. [Math and number theory](#11-math-and-number-theory)
12. [Combinatorics and probability](#12-combinatorics-and-probability)
13. [Geometry](#13-geometry)
14. [Game theory](#14-game-theory)
15. [Bit manipulation](#15-bit-manipulation)
16. [Interactive problems](#16-interactive-problems)
17. [Text processing (the Xplore tasks)](#17-text-processing-the-xplore-tasks)
18. [Reverse engineering and emulation](#18-reverse-engineering-and-emulation)
19. [Brute force and backtracking](#19-brute-force-and-backtracking)
20. [Library reference](#20-library-reference)
21. [References](#21-references)

---

## 1. The contest and this kit

IEEEXtreme is a 24-hour programming contest for teams of up to three IEEE
student members. The tasks run on CS Academy; a submission is a single source
file that reads standard input and writes standard output. Every task has many
test cases and **each passed test gives points**, so a slow but correct
solution still scores. Several tasks are open-ended (output-only, optimisation,
code golf) and some are interactive.

What the archive asks for (primary topic of each of the 252 tasks; details in
[tasks.md](tasks.md)):

| Topic | Tasks | Topic | Tasks |
|---|---:|---|---:|
| Graphs | 30 | Brute force / backtracking | 9 |
| Math and number theory | 25 | Bit manipulation | 7 |
| Dynamic programming | 24 | Constructive | 7 |
| Trees | 23 | Text and data processing | 7 |
| Greedy and sorting | 19 | Interactive | 6 |
| Data structures | 19 | Reverse engineering | 6 |
| Strings | 18 | Game theory | 4 |
| Implementation and simulation | 17 | Binary search | 3 (+8 as a secondary tool) |
| Combinatorics and probability | 17 | Geometry | 11 |

Counting secondary topics too, DP (48 tasks), math (47), graphs (38) and data
structures (37) dominate. Combinatorics with modular arithmetic has become
common since 15.0.

**Working with the kit.** Write the solution with library includes, test
locally, then bundle:

```sh
cc -std=c11 -O2 -Wall -I lib solution.c -lm -o sol   # compile (-lm for math.h)
./sol < sample.in                                   # test
python3 tools/bundle.py solution.c > submit.c       # one file for submission
```

The library headers are meant to be read: each one starts with a list of its
functions, and every function has a comment saying what it does and its cost.

## 2. C for contests

### 2.1 A template

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef long long ll;

#define MAXN 200005
static int a[MAXN];              /* big arrays: global/static, never local */

int main(void) {
    int n;
    if (scanf("%d", &n) != 1) return 0;
    for (int i = 0; i < n; i++) scanf("%d", &a[i]);
    ll sum = 0;
    for (int i = 0; i < n; i++) sum += a[i];
    printf("%lld\n", sum);
    return 0;
}
```

[`lib/common.h`](../../lib/common.h) gives the same basics (`ll`, `MIN`, `MAX`,
`SWAP`, `INF`, `LINF`, `MOD`).

### 2.2 Input and output

- `scanf` returns how many items it read. Test cases until end of input:
  `while (scanf("%d %d", &a, &b) == 2) { ... }`.
- Whole lines: `fgets(buf, sizeof buf, stdin)` keeps the `'\n'`; remove it with
  `buf[strcspn(buf, "\r\n")] = 0;` (this also removes the `'\r'` of Windows files).
- Mixing `scanf("%d")` and `fgets`: the number leaves the end of its line unread,
  so the first `fgets` returns an empty line. Read and drop it.
- Formats: `%d` int, `%lld` long long, `%llu` unsigned long long, `%s` word,
  `%c` char (use `" %c"` to skip spaces), `%lf` for reading a double, `%.6f`
  for printing one.
- Big inputs (10^6 numbers and more): [`io.h`](../../lib/io.h) is about ten times
  faster than `scanf` (`read_int`, `read_ll`, `read_word`, `read_line`).
  Do not mix it with `scanf` and never use it in interactive tasks.

### 2.3 Integer sizes and overflow

| Type | Range | Typical use |
|---|---|---|
| `int` | ±2.1·10^9 | indices, counts |
| `long long` | ±9.2·10^18 | sums, products, answers |
| `unsigned long long` | 0 … 1.8·10^19 | hashes, bit masks of 64 elements |
| `__int128` (GCC/Clang) | ±1.7·10^38 | products of two 64-bit values |
| `double` | ~15 significant digits | geometry, probabilities |

- `int * int` overflows before it is assigned: write `(ll)a * b`.
- "Print the answer modulo 10^9+7": take `% MOD` after **every** addition and
  multiplication; after a subtraction add `MOD` before `%`: `((x - y) % MOD + MOD) % MOD`.
- `abs` is for `int`; use `llabs` for `long long`.
- `-7 / 2 == -3` and `-7 % 2 == -1` in C; [`util.h`](../../lib/util.h) has
  `floor_div` and `ceil_div`.

### 2.4 Memory and recursion

Local arrays live on the stack (often 1–8 MB): a local `int a[1000000]` crashes.
Declare big arrays `static` or global; they are zero-initialised. Deep
recursion (a DFS on a 10^5-vertex path) can overflow the stack too, so the
library's graph and tree algorithms are iterative. With many test cases in one
input, remember to clear global arrays between cases.

### 2.5 How fast is fast enough

Count about 10^8 simple operations per second. From the limits you can
guess the intended complexity:

| n up to | Feasible | Typical algorithm |
|---|---|---|
| 10 | O(n!) | try all permutations |
| 20–25 | O(2^n · n) | subsets, bitmask DP, meet in the middle (40) |
| 500 | O(n^3) | Floyd–Warshall, interval DP |
| 5 000 | O(n^2) | 2D DP, all pairs |
| 10^5 – 10^6 | O(n log n) | sorting, segment trees, Dijkstra |
| 10^7 – 10^8 | O(n) | linear scans, sieve |
| 10^18 | O(log n) or O(1) | formulas, binary search, fast exponentiation |

### 2.6 Floating point

Avoid it when integers work (compare `a*a < b` rather than `sqrt`). When you
must, compare with a tolerance `fabs(x - y) < 1e-9`, print with the precision
the task asks for, and remember `long double` for extra digits.

### 2.7 Testing like a pro

1. Run the samples, then corner cases: n = 1, all values equal, maximum values,
   negative values, empty lines.
2. Write a slow brute force and compare on random small inputs (stress test):

```sh
for i in $(seq 1 500); do
  python3 gen.py $i > in.txt                   # random small test
  ./fast < in.txt > out1; ./brute < in.txt > out2
  cmp -s out1 out2 || { echo "differs on test $i"; cat in.txt; break; }
done
```

3. Compile with checks while debugging: `cc -g -fsanitize=address,undefined ...`
   catches out-of-bounds accesses and overflows.

### 2.8 Strategy for 24 hours

Read every task early; the archive's solve rates ([tasks.md](tasks.md)) show
that some tasks look scary but are easy, and some short ones are very hard.
Submit a correct brute force first for partial points, then improve.
Split the work by topic inside the team, and keep one person fresh for the night.

## 3. Sorting and searching

### 3.1 Sorting with `qsort`

```c
int cmp_int(const void *a, const void *b) {        /* ascending ints */
    int x = *(const int *)a, y = *(const int *)b;
    return (x > y) - (x < y);                      /* never "return x - y": overflow */
}
qsort(arr, n, sizeof(int), cmp_int);
```

Sorting structures by several keys (from [`examples/intervals.c`](../../examples/intervals.c)):

```c
typedef struct { ll start, end; } Talk;

static int by_end(const void *a, const void *b) {
    const Talk *x = a, *y = b;
    if (x->end != y->end) return (x->end > y->end) - (x->end < y->end);
    return (x->start > y->start) - (x->start < y->start);
}
qsort(t, n, sizeof(Talk), by_end);
```

`qsort` is O(n log n) but not stable; add the original index as a last key if
the order of equal elements matters. Strings: sort an array of `char *` with
`strcmp` (`cmp_str` in [`sort.h`](../../lib/sort.h)).

Related tools in [`sort.h`](../../lib/sort.h): `unique_int` (drop duplicates),
`compress` (replace values by their rank 0..m-1 — needed before using values
as array indices), `count_inversions` (merge sort, O(n log n); also the
minimum number of adjacent swaps that sorts the array), `kth_smallest`
(quickselect, O(n) on average).

### 3.2 Binary search

In a sorted array, `lower_bound_int(a, n, x)` is the first index with
`a[i] >= x`, `upper_bound_int` the first with `a[i] > x`; their difference is
the number of copies of `x`. (Archive: *The Twin Occurrence Quest*.)

**Binary search on the answer** is the more important idea. If a yes/no
question `ok(x)` is monotone — false, …, false, true, …, true — the smallest
good `x` is found with O(log range) checks. Typical phrasing: "minimise the
maximum", "maximise the minimum", "the least time such that…". From
[`examples/bs_answer.c`](../../examples/bs_answer.c) (split an array into at most
k parts minimising the largest part sum):

```c
static int ok(ll limit) {              /* can we split with all parts <= limit? */
    int parts = 1;
    ll cur = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > limit) return 0;
        if (cur + a[i] > limit) { parts++; cur = 0; }
        cur += a[i];
    }
    return parts <= k;
}
...
printf("%lld\n", bs_first_true(0, total, ok));
```

For real numbers iterate a fixed number of times (`bs_real`, 100 halvings).
**Ternary search** finds the minimum of a function that decreases and then
increases (`ternary_min_int`, `ternary_min_real` in [`search.h`](../../lib/search.h)).

## 4. Greedy algorithms

A greedy algorithm makes the locally best choice and never reconsiders it. It
is correct only when an **exchange argument** works: take any optimal solution
and show that swapping in the greedy choice does not make it worse. Typical
patterns:

| Situation | Greedy rule |
|---|---|
| Most non-overlapping intervals | take the one that ends first ([`intervals.c`](../../examples/intervals.c)) |
| Cover a segment with fewest intervals | among those starting before the uncovered point take the one reaching furthest |
| Jobs with deadlines, unit time | sweep time, keep a heap of available jobs, serve the earliest deadline (*Doctor's Appointments*) |
| Minimise maximum lateness | sort by deadline |
| Split sorted values into K groups | cut at the K−1 largest gaps (*Dog Walking*) |
| Merge costs (Huffman) | always merge the two smallest (heap) |
| Make values distinct with ±1 steps | sort, then push each value just above the previous |

If you cannot prove a greedy rule, test it against a brute force on small
inputs before submitting.

## 5. Prefix sums, two pointers, sliding windows

**Prefix sums** answer "sum of a[l..r]" in O(1): `p[0] = 0, p[i+1] = p[i] + a[i]`,
sum = `p[r+1] - p[l]`. In 2D (`prefix2d_build`, `rect_sum` in
[`grid.h`](../../lib/grid.h)) the sum of any rectangle is four lookups.

**Difference arrays** do the opposite: many offline updates "add v to a[l..r]"
become `d[l] += v; d[r+1] -= v`, and one prefix-sum pass recovers the array.
On a tree the same trick works along paths with the LCA (*Tree Fun*).

**Two pointers.** When the condition is monotone in both ends of a window,
move the right end forward and pull the left end only forward — O(n) instead
of O(n²). From [`examples/two_pointers.c`](../../examples/two_pointers.c)
(longest block with sum ≤ budget, non-negative values):

```c
for (int l = 0, r = 0; r < n; r++) {
    sum += a[r];                        /* window is a[l..r] */
    while (sum > budget) sum -= a[l++];
    best = MAX(best, r - l + 1);
}
```

**Monotonic stack / deque** ([`linear.h`](../../lib/linear.h)): next greater
element, how many people a person sees in a line (*Long Lines*), largest
rectangle in a histogram (*Rectangles and arrays*), maximum of every window of
length k ([`examples/sliding_max.c`](../../examples/sliding_max.c)), DP
transitions over a window. Each index is pushed and popped once: O(n).

## 6. Data structures

| You need | Use | Cost | Library |
|---|---|---|---|
| LIFO / FIFO / both ends | array stack, circular queue / deque | O(1) | `linear.h` |
| Repeatedly the smallest (largest) item | binary heap | O(log n) | `heap.h` |
| "Have I seen x?", counting, ids for names | hash table | O(1) average | `hashmap.h` |
| Merge groups, "same group?" | disjoint set union | ~O(1) | `dsu.h` |
| Point update + prefix/range sum, k-th element | Fenwick tree | O(log n) | `fenwick.h` |
| Range add + range sum | two Fenwick trees | O(log n) | `fenwick.h` |
| Point update + range min/max/gcd/any associative op | segment tree | O(log n) | `segtree.h` |
| Range add / assign + range sum / max | lazy segment tree | O(log n) | `segtree.h` |
| Static range min / max / gcd | sparse table | O(1) query | `sparse.h` |
| Prefixes of words, max XOR pair | trie, binary trie | O(length) | `trie.h` |

**Heap.** `heap_push(&pq, key, id)` / `heap_pop(&pq)` returns the smallest key.
For a max-heap push `-key`. Declare the heap `static` (it is large).

**DSU** keeps a forest; `dsu_find` walks to the root (path halving) and
`dsu_union` hangs the smaller tree under the larger one. Variant with parity
(`pdsu_*`): stores whether two elements are "same" or "different" — detects odd
cycles online (*Odd Cycle Check*).

**Fenwick tree** (1-indexed): `fen_add(i, v)` and `fen_sum(i)` = a[1]+…+a[i].
With `a[v]` = how many times value `v` occurs, `fen_sum(v)` counts smaller
elements (inversions, ranks) and `fen_lower_bound(k)` finds the k-th smallest.

**Segment tree.** Leaves hold the array, each inner node combines its two
children. `segtree.h` uses the compact bottom-up form for any associative
operation, chosen with two macros before the include:

```c
#define SEG_OP(a, b) ((a) < (b) ? (a) : (b))   /* range minimum */
#define SEG_ID LINF                            /* identity: op(x, ID) = x */
#include "segtree.h"
```

The lazy tree (`lz_*`) postpones range updates: a node covering a whole update
range stores the pending operation and passes it to its children only when a
later operation needs them. [`examples/segtree_lazy.c`](../../examples/segtree_lazy.c)
handles "add", "assign", "sum" and "max" queries (archive: *Corporation*).

**Sqrt decomposition / Mo's algorithm** (not in the library): split the array
into blocks of √n; for offline range queries sort them by (block of l, r) and
move two pointers — O((n + q)√n) total.

## 7. Dynamic programming

DP = recursion + remembering answers of subproblems. Recipe:

1. **State**: what you need to know about a partial solution (index, remaining
   capacity, last choice, mask of used items…).
2. **Transition**: how a state is built from smaller states.
3. **Base cases**.
4. **Order**: compute a state after the states it depends on (loops), or use
   memoised recursion.
5. **Answer**: which state(s) hold it.

Memory/time = number of states × transitions per state.

### 7.1 Classic families

| Family | State | Archive examples | Library |
|---|---|---|---|
| 0/1 and unbounded knapsack | capacity used | *BeetleBag*, *Charlie New PC* | `knapsack01` |
| Coin change (ways / fewest) | amount | *Visit Egypt* | `coin_ways`, `coin_min` |
| Longest increasing subsequence | length → smallest tail | | `lis_length` |
| LCS, edit distance, alignment | (i, j) prefixes | *Squared Gaps* | `lcs_length`, `edit_distance` |
| Grid paths | cell | *Ice Cubes*, *Lion Territory* | |
| Intervals / weighted scheduling | sorted by end + binary search | *Telescope Scheduling* | |
| Bitmask DP | subset of items | *Preparing for Xtreme 12.0*, TSP | `tsp` |
| Tree DP | vertex (children first) | *Merchant Association* | `tree.h` order |
| Digit DP | (position, info, tight) | *Happy Numbers*, *Four Piles* | |
| Counting mod p | count of objects | *Ordered Permutations* | |

### 7.2 Knapsack in full

From [`examples/knapsack.c`](../../examples/knapsack.c) — `f[i][c]` is the best
value using the first i items within capacity c:

```c
for (int i = 1; i <= n; i++)
    for (int c = 0; c <= W; c++) {
        f[i][c] = f[i - 1][c];                                   /* skip item i */
        if (c >= w[i] && f[i - 1][c - w[i]] + v[i] > f[i][c])    /* take item i */
            f[i][c] = f[i - 1][c - w[i]] + v[i];
    }
```

Walking back from `f[n][W]` (an item was taken where `f[i][c] != f[i-1][c]`)
recovers the chosen items. With one row only, loop `c` **downwards** so each
item is used at most once; upwards gives the unbounded version.

### 7.3 Bitmask DP

For n ≤ 20 a subset is an integer mask. Travelling salesman
([`examples/tsp.c`](../../examples/tsp.c), `tsp` in [`dp.h`](../../lib/dp.h)):
`dp[mask][v]` = cheapest path that visited exactly `mask` and ends in `v`;
extend by an unvisited `u`: `dp[mask | 1<<u][u] = min(dp[mask][v] + d[v][u])`.
O(2^n · n²).

### 7.4 Digit DP

"How many numbers in [A, B] have property P?" = count(B) − count(A−1).
Build the number digit by digit from the left; the state is (position,
whatever P needs, `tight` = prefix equals the bound so far). From
[`examples/digit_dp.c`](../../examples/digit_dp.c) (digit sum divisible by K):

```c
static ll go(int pos, int sum, int tight) {
    if (pos == nd) return sum == 0;
    if (!tight && seen[pos][sum]) return memo[pos][sum];
    int limit = tight ? dig[pos] : 9;
    ll res = 0;
    for (int d = 0; d <= limit; d++) res += go(pos + 1, (sum + d) % K, tight && d == limit);
    if (!tight) { seen[pos][sum] = 1; memo[pos][sum] = res; }
    return res;
}
```

### 7.5 Making DP faster

- Sum over a range of previous states → keep prefix sums of the DP row.
- Min/max over a sliding range of states → monotonic deque.
- Only the previous row is needed → two rows (`lcs_length`).
- Transitions that are a fixed linear map applied n times (n huge) → matrix
  power (section 11.4).

## 8. Graphs

### 8.1 Representation

[`graph.h`](../../lib/graph.h) stores adjacency lists in arrays ("forward star"):

```c
g_init(n + 1);                 /* vertices 1..n */
g_add2(u, v, w);               /* undirected edge (g_add for directed) */
G_EACH(e, u) {                 /* all edges leaving u */
    int v = g_to[e];
    ll w = g_w[e];
}
```

An adjacency matrix `int adj[N][N]` is fine for n ≤ 2000. A grid is a graph
whose vertices are cells; use [`grid.h`](../../lib/grid.h) directly (`DR4/DC4`
direction arrays, `IN_GRID`, `grid_bfs`, `grid_regions` for flood fill).

### 8.2 Traversals

- **BFS** gives shortest paths when every edge costs 1
  (`bfs`, `bfs_multi` for several sources at once — e.g. distance to the
  nearest ghost, *Invisible Ghosts*). Maze: [`examples/grid_bfs.c`](../../examples/grid_bfs.c).
- **DFS** explores as deep as possible: components, cycles, topological order.
  The recursive form is the clearest, but its depth equals the path length:

```c
static int vis[MAXN];
static void dfs(int u) {          /* fine up to ~10^4..10^5 depth */
    vis[u] = 1;
    G_EACH(e, u) if (!vis[g_to[e]]) dfs(g_to[e]);
}
```

- **State-space search**: the "graph" can be implicit — board positions, lock
  combinations, sets of stones. Encode a state as an integer (bitmask, base-10
  digits) and BFS over it (*Binary Quilts*, *Magical Stones*, *Combo Lock Redux*).

### 8.3 Shortest paths

| Edge weights | Algorithm | Cost | Library |
|---|---|---|---|
| all 1 | BFS | O(V+E) | `bfs` |
| 0 or 1 | 0-1 BFS (deque) | O(V+E) | `bfs01` |
| non-negative | Dijkstra with a heap | O(E log E) | `dijkstra` + `build_path` |
| negative, no negative cycle | Bellman–Ford | O(VE) | `bellman_ford` |
| all pairs, V ≤ 400 | Floyd–Warshall | O(V³) | `floyd` |

Dijkstra in a nutshell: repeatedly take the closest unfinished vertex from the
heap and relax its edges; skip heap entries that are out of date. See
[`examples/dijkstra.c`](../../examples/dijkstra.c). Extra conditions ("at most k
free edges", "fuel left", "first five streets distinct") become extra
coordinates of the state: run Dijkstra on vertices (city, k).

### 8.4 Other classics

- **Minimum spanning tree** (Kruskal): sort edges, add an edge if it joins two
  components (DSU). [`examples/kruskal.c`](../../examples/kruskal.c). Variants:
  maximum spanning tree (sort descending), bottleneck paths (*Xtreme
  Teleportation*), edges that belong to some/all MSTs (*National Highway System*).
- **Topological order** (Kahn, `toposort`): repeatedly output a vertex with no
  incoming edges; if fewer than n come out, there is a cycle (*King's Order*).
  DP on a DAG runs in this order.
- **Strongly connected components** (`scc`, Tarjan): mutual reachability; the
  components form a DAG.
- **Bridges and articulation points** (`bridges`): edges / vertices whose
  removal disconnects the graph. An edge can be made one-way keeping strong
  connectivity iff it is not a bridge (*Bearcity Renting*).
- **Bipartite check** (`bipartite`): 2-colour with BFS; fails iff there is an odd cycle.

### 8.5 Flows and matchings

[`flow.h`](../../lib/flow.h): `max_flow` (Dinic), `bipartite_matching` (Kuhn),
`mcmf` (minimum-cost maximum flow).

Modelling tricks:

- **Assignment** (workers ↔ jobs): source → each worker (cap 1) → allowed jobs
  (cap 1) → sink (cap 1). Max flow = max matching
  ([`examples/matching.c`](../../examples/matching.c)). With costs use `mcmf`.
- **A job taking up to c workers**: capacity c on the job → sink edge (holes
  holding two Digletts, *Gotta ~ Catch 'Em All*).
- **Vertex capacities**: split v into v_in → v_out with the capacity on that edge.
- **Minimise the maximum cost of an assignment**: binary search on the limit,
  keep only cheaper edges, test for a perfect matching (*Finding Shelter*).
- **Min cut** = max flow; after `max_flow` the vertices with `fl_level[v] >= 0`
  are on the source side of a minimum cut.
- Kőnig: in bipartite graphs, minimum vertex cover = maximum matching.

## 9. Trees

A tree has n−1 edges and exactly one path between two vertices. Most tree tasks
start by rooting it ([`tree.h`](../../lib/tree.h)):

```c
g_init(n + 1);
for (i = 0; i < n - 1; i++) { scanf(...); g_add2(u, v, w); }
tree_root(1);   /* t_par, t_dep, t_dist, t_sz, t_order (parents first), t_tin/t_tout */
```

- **Tree DP**: children come after parents in `t_order`, so a reverse loop
  processes children first — no recursion needed:

```c
for (int i = n - 1; i >= 0; i--) {      /* bottom-up */
    int v = t_order[i];
    /* dp[v] is complete here; add it to the parent */
    if (t_par[v] >= 0) dp[t_par[v]] += dp[v];
}
```

- **Subtree = contiguous range**: vertex `v`'s subtree is `t_tin[v] … t_tout[v]`
  in preorder, so subtree sums/updates become range queries on a Fenwick or
  segment tree (*He Loves Data Structures*).
- **LCA** (binary lifting, `lca_init`, `lca`, `kth_ancestor`): distance
  `dist(a,b) = d(a) + d(b) − 2 d(lca)` ([`examples/lca.c`](../../examples/lca.c)).
- **Diameter** (`tree_diameter`): the farthest vertex from any vertex is one
  end of a diameter; the farthest from it is the other end. Joining two trees
  by one edge: the new diameter is max(d1, d2, r1 + r2 + 1), with r = ⌈d/2⌉
  (*Bridge Construction*).
- **Path queries with updates** (`hld_build`, `hld_path`): heavy-light
  decomposition splits any path into O(log n) ranges of a segment tree
  (*ANDman*: products on paths; *Tree Queries 2*).
- **Counting over all pairs of vertices**: count each edge's contribution —
  an edge splitting the tree into parts of sizes s and n−s lies on s·(n−s) paths.
- **Rerooting**: compute a DP for root 1, then move the root across each edge
  updating the answer in O(1) — answers for all roots in O(n).
- **Centroid decomposition** (not in the library): for "count paths with
  property P" in O(n log² n).

## 10. Strings

### 10.1 C strings in practice

A string is a `char` array ending with `'\0'`. `strlen` is O(n) — never call it
in a loop condition. Useful functions: `strcmp`, `strncmp`, `strcpy`, `strcat`,
`strstr` (find substring), `strchr`, `strtok` (split, modifies the string),
`sscanf` (parse from a string), `sprintf` / `snprintf` (format into a string),
and from `<ctype.h>`: `isalpha`, `isdigit`, `isspace`, `tolower`, `toupper`.
Map names to ids with `sm_id` in [`hashmap.h`](../../lib/hashmap.h).

**Ciphers** appear in almost every edition (*Caesar Redux*, *Gaius Letters*,
*Book Cipher*, *Restaurant Cipher*). Caesar shift by k:

```c
for (int i = 0; s[i]; i++)
    if (isupper((unsigned char)s[i])) s[i] = (char)('A' + (s[i] - 'A' + k) % 26);
    else if (islower((unsigned char)s[i])) s[i] = (char)('a' + (s[i] - 'a' + k) % 26);
```

(For decryption use `26 - k`. When the key is unknown, try all 26 and pick the
one whose letter frequencies look like English, or that contains known words.)

### 10.2 Algorithms

| Task | Algorithm | Cost | Library |
|---|---|---|---|
| All occurrences of a pattern | KMP (prefix function) | O(n+m) | `kmp_search` |
| Period of a string, borders | prefix function: period = n − π[n−1] | O(n) | `prefix_function` |
| Longest common prefix with every suffix | Z-function | O(n) | `z_function` |
| Compare any two substrings | polynomial hashing | O(1) after O(n) | `hash_build`, `hash_sub` |
| All palindromes | Manacher | O(n) | `manacher`, `longest_palindrome` |
| Many words: prefixes, counts | trie | O(length) | `trie_insert`, … |
| Many patterns in a text | Aho–Corasick | O(n + total) | `ac_build`, `ac_count` |
| Sorted suffixes, distinct substrings | suffix array + LCP | O(n log² n) | `suffix_array`, `lcp_array` |

Example: [`examples/kmp.c`](../../examples/kmp.c). Hashing with modulus 2^61−1
makes collisions practically impossible; compare substrings of two strings by
hashing their concatenation.

**Bracket sequences** (*Tweedledum…*, *EDPS*, *Expression Evaluation*): keep a
balance counter (+1 for `(`, −1 for `)`); the sequence is valid iff the
balance never drops below 0 and ends at 0. With several bracket types use a
stack of the open brackets.

## 11. Math and number theory

### 11.1 Modular arithmetic

`(a + b) mod m`, `(a − b) mod m` (add m!), `(a · b) mod m` are safe while the
product fits in 64 bits (m < 3·10^9); otherwise use `mulmod` (128-bit) from
[`numtheory.h`](../../lib/numtheory.h). **Division** by `b` = multiplication by
the inverse: `b^(p−2) mod p` for prime p (Fermat), `modinv` (extended Euclid)
for any m coprime to b.

Fast exponentiation, O(log e):

```c
ll powmod(ll b, ll e, ll m) {
    ll r = 1 % m;
    b %= m;
    for (; e > 0; e >>= 1) {          /* look at the bits of e */
        if (e & 1) r = r * b % m;
        b = b * b % m;
    }
    return r;
}
```

**Huge exponents** (*Googolplex*, *Math Challenge*): for gcd(a, m) = 1,
a^e ≡ a^(e mod φ(m)) (mod m) (Euler); with a prime m reduce e modulo m−1.
Last digits of powers repeat with a short cycle — find it by simulation.

### 11.2 Divisibility and primes

- `gcd` (Euclid), `lcm(a, b) = a / gcd · b` (divide first!), `extgcd` solves
  a·x + b·y = gcd(a, b), `crt2` combines x ≡ a1 (mod m1), x ≡ a2 (mod m2).
- **Sieve** (`sieve`): all primes up to `SIEVE_MAX` (10^6 by default; 10^7 still
  fits in memory) and the smallest prime factor of every number, then
  factorisation in O(log x) ([`examples/sieve.c`](../../examples/sieve.c)).
- Single big numbers: trial division up to √n (`factor_trial`, n ≤ 10^12),
  Miller–Rabin (`is_prime`, any 64-bit n).
- n has ∏(eᵢ+1) divisors; Euler's φ(n) = n ∏(1 − 1/p).
- Trailing zeros of n! in base B: factorise B; Legendre: the exponent of p in
  n! is ⌊n/p⌋ + ⌊n/p²⌋ + … (*Factorial Zeros*).
- XOR of 1..n is n, 1, n+1, 0 for n mod 4 = 0, 1, 2, 3 (*RecXor*).

### 11.3 Big numbers

C has no big integers. First check whether the task really needs exact digits
(often only a remainder, a comparison or a logarithm is needed). If it does,
[`bignum.h`](../../lib/bignum.h) stores numbers in base 10^9: add, subtract,
multiply, divide by small, print ([`examples/factorial.c`](../../examples/factorial.c)
prints 50!).

### 11.4 Matrices

**Linear recurrences** f(n) = c₁f(n−1) + … + c_k f(n−k) for n up to 10^18:
the vector of the last k values is multiplied by a fixed k×k matrix, so
f(n) comes from M^n in O(k³ log n) ([`examples/fib_matrix.c`](../../examples/fib_matrix.c)).
Sums like Σ P^k k^Q (*Beautiful Summation*) fit the same scheme with a bigger
state vector.

**Gaussian elimination** (`gauss_mod`, `gauss_double`): solves linear systems,
computes determinants (modulo a prime) and ranks. Over GF(2) (XOR equations,
"lights out" puzzles) use the XOR basis of section 15.

## 12. Combinatorics and probability

[`combin.h`](../../lib/combin.h) precomputes factorials and inverse factorials
modulo a prime: `nCr`, `nPr`, `catalan` in O(1) after O(N)
([`examples/ncr.c`](../../examples/ncr.c)); `lucas` for huge n with a small prime.

| Count | Formula |
|---|---|
| ordered selections of r from n | n! / (n−r)! |
| subsets of size r | C(n, r) |
| multisets of size r from n kinds ("stars and bars") | C(n+r−1, r) |
| lattice paths right/up a×b | C(a+b, a) |
| balanced bracket sequences of n pairs, binary trees | Catalan(n) = C(2n, n)/(n+1) |
| permutations of a multiset | n! / (n₁! n₂! …) |
| at least one of several properties | inclusion–exclusion Σ(−1)^(|S|+1)… |

- Pascal's rule C(n, k) = C(n−1, k−1) + C(n−1, k) gives a table for small n
  even when the modulus is not prime.
- **Permutations**: the minimum number of swaps to sort = n − (number of
  cycles) (`perm_cycles`); minimum adjacent swaps = number of inversions.
  `next_perm` enumerates all permutations in order, `nth_perm` jumps to the k-th.
- **Expected value** is linear: E[X+Y] = E[X] + E[Y] even for dependent
  variables. Write the quantity as a sum of indicator variables and add their
  probabilities (*New Casino Game*). Probability "modulo p" means P·Q⁻¹ mod p.
- **Generating functions**: the number of ways to reach sum s with several
  independent choices is a coefficient of the product of their polynomials;
  `poly_mul` in [`fft.h`](../../lib/fft.h) multiplies polynomials modulo 998244353
  in O(n log n) (*Dice*, *Candy Shop*).
- Counting answers are often easier by DP than by formula; compare both on
  small cases.

## 13. Geometry

Work in integers whenever coordinates are integers ([`geom.h`](../../lib/geom.h)).
The central tool is the **cross product**:

```c
ll cross3(Pt o, Pt a, Pt b) {      /* > 0: o→a→b turns left (counter-clockwise) */
    return (a.x - o.x) * (b.y - o.y) - (a.y - o.y) * (b.x - o.x);
}
```

It gives orientation, twice the area of a triangle, collinearity (= 0), and
from it: segment intersection (`seg_intersect`), polygon area by the shoelace
formula (`polygon_area2` returns twice the area, exact), point in polygon
(`in_polygon`: ray casting, also detects the boundary), convex hull
(`convex_hull`, Andrew's monotone chain; [`examples/convex_hull.c`](../../examples/convex_hull.c)).

- **Pick's theorem**: A = I + B/2 − 1 for lattice polygons; B = Σ gcd(|dx|, |dy|)
  over the edges (`lattice_interior`, *Polygon*).
- Distances: compare squared distances (`dist2`) instead of `sqrt`.
- Circles and ellipses: when an exact formula is hard (area of a union of
  ellipses, *Ellipse Art*), integrate numerically — split the canvas into thin
  strips or a fine grid and add up.
- **Sweep line**: sort events by x and move a vertical line, keeping the
  active objects in a data structure (union of rectangles, intersections;
  *The Defensive Walls*). Counting crossing pairs of segments between two
  parallel lines = counting inversions (*Laser Defense*), and the number of
  regions follows from Euler's formula V − E + F = 2.
- Real-valued helpers: `line_intersect`, `dist_pt_seg`; compare with an epsilon.

## 14. Game theory

- **Win/lose DP**: a position is winning iff some move leads to a losing
  position; terminal positions are given by the rules. Memoise over all
  positions (or retrograde BFS when the game graph has cycles).
- **Minimax** for scores: the player to move maximises, the opponent minimises
  (*The Gold-diggers*, *Let's Cheer Up Bob*); add memoisation when positions repeat.
- **Nim**: piles a₁…a_k, remove any number from one pile — the first player
  wins iff a₁ ⊕ … ⊕ a_k ≠ 0 (`nim_xor`).
- **Sprague–Grundy**: every impartial game position has a Grundy number
  g = mex{g of positions reachable in one move}; g = 0 means losing, and a sum
  of independent games has Grundy number = XOR of the parts
  ([`examples/grundy.c`](../../examples/grundy.c), `grundy_subtraction`, `grundy_dag`).
- Print a table of winning/losing positions for small sizes — the pattern
  (periodicity, Wythoff-like diagonals as in *Queen*) usually gives the formula.

## 15. Bit manipulation

| Expression | Meaning |
|---|---|
| `x >> i & 1` | i-th bit of x |
| `x \| (1 << i)`, `x & ~(1 << i)`, `x ^ (1 << i)` | set / clear / flip bit i |
| `x & -x` | lowest set bit (`LOWBIT`) |
| `x & (x - 1)` | x without its lowest set bit; 0 iff x is a power of two |
| `__builtin_popcountll(x)` | number of 1 bits (`POPCOUNT`) |
| `__builtin_ctzll(x)`, `63 - __builtin_clzll(x)` | trailing zeros, highest bit (`log2_floor`) |
| `1LL << 40` | 64-bit shift (plain `1 << 40` overflows) |

- **Subsets**: masks 0 … 2^n − 1; all submasks of `mask`:
  `for (s = mask; s; s = (s - 1) & mask)` (`FOR_SUBMASKS`); over all masks 3^n steps.
- **Sum over subsets** (`sos_subsets`): for each mask the sum over all its
  submasks in O(n 2^n) — counts of teams covering all topics (*Xtreme Teams*).
- **XOR basis** (`XorBasis` in [`bits.h`](../../lib/bits.h)): Gaussian elimination
  over GF(2). Maximum XOR of a subset, whether x is reachable, and the number
  of distinct subset XORs (2^rank). The XOR of a random subset is uniform over
  the span (*Do you know Expectation?*).
- **Binary trie** (`bt_*` in [`trie.h`](../../lib/trie.h)): maximum `x ^ y` with y
  in a dynamic set, count of y with `x ^ y < k`.
- OR / AND only add / remove bits: over a growing range the OR changes at most
  30 times — useful for "sum over all subarrays" tasks.

## 16. Interactive problems

The judge answers your questions while your program runs. Rules:

1. Flush after every output line, otherwise the judge never receives it:
   `printf(...); fflush(stdout);` — `ASK(...)` in [`interactive.h`](../../lib/interactive.h).
2. Read replies with `scanf`; stop when the judge says `-1` (invalid query).
3. Count your queries: the limit is part of the task (log₂ of the range for
   binary search, information-theory bounds for weighing puzzles).

[`examples/guess.c`](../../examples/guess.c) finds a hidden number with "is X ≥ y?"
questions:

```c
while (lo < hi) {                       /* X is in [lo, hi] */
    ll mid = lo + (hi - lo + 1) / 2;
    ASK("? %lld\n", mid);
    if (reply_int()) lo = mid; else hi = mid - 1;
}
ASK("! %lld\n", lo);
```

Test locally with a small judge program connected through two named pipes
(see [`examples/judge_guess.c`](../../examples/judge_guess.c) and
[`tests/run_examples.sh`](../../tests/run_examples.sh)).

## 17. Text processing (the Xplore tasks)

Almost every edition has an IEEE Xplore task: read article metadata (JSON,
CSV, XML-like text), group and aggregate it, print a sorted report
(*Xplore* h-index, *Impact Factor*, *Thesaurus*, *Disparate Data Sets*,
*Application Abuse*). The algorithms are simple; the points are lost in parsing.

- Read line by line with `fgets` into a large static buffer; strip `"\r\n"`.
- Find fields with `strstr` and parse values with `sscanf`/`strtol`/`atof`.
  [`examples/json_records.c`](../../examples/json_records.c) contains a 20-line
  `json_get(line, key, out, cap)` that handles strings with escapes and numbers.
- CSV: split on commas but respect quoted fields (`"a, b"`); empty fields are
  legal (`a,,c`) — `strtok` skips them, so walk the line by hand.
- Strip XML/HTML tags by skipping from `<` to `>` (*Book Cipher*).
- Give every name an id with `sm_id`, keep counters in arrays indexed by id,
  then sort the ids with a comparator ([`examples/word_freq.c`](../../examples/word_freq.c)).
- Read the output format three times: separators, rounding, tie-breaking
  order, trailing spaces.

## 18. Reverse engineering and emulation

Some tasks hide the rule: "produce the same output as this program"
(*Dalvik*, *Ladder*), "discover the function from the examples" (*Magic
Spell*, *Restaurant Cipher*), "emulate this number format" (*IEEE754
Emulator*, *Barrett Reduction*, *ARM Constant Multiplication*).

- Run the given code (or a hand translation) for small inputs and print a
  table; look for periodicity, powers, binomials, known sequences (OEIS).
- Translate the given program literally first, then optimise the slow part
  (usually a loop that has a closed form or a cycle).
- Floating-point bit patterns in C: copy the bits with `memcpy`, never through
  pointer casts:

```c
float f = 1.5f;
uint32_t bits;
memcpy(&bits, &f, sizeof bits);   /* sign = bits >> 31, exponent = bits >> 23 & 255, mantissa = bits & 0x7FFFFF */
```

## 19. Brute force and backtracking

When n is small, or to earn partial points, search all possibilities:

```c
static int n, choice[20];
static void search(int i) {            /* decide item i */
    if (i == n) { /* evaluate the complete choice */ return; }
    for (int c = 0; c < 2; c++) {      /* every option for item i */
        choice[i] = c;
        if (/* partial choice still can beat the best */ 1) search(i + 1);
    }
}
```

- **Pruning**: stop a branch as soon as it cannot be valid or cannot beat the
  best answer found so far; try promising options first.
- **Meet in the middle**: split n ≤ 40 items into two halves, enumerate 2^20
  sums of each, sort one side and binary search for complements.
- **Iterative deepening / BFS over states** when the shortest sequence of moves
  is wanted (*Puzzle of Rooks*, *Digits swap*).
- **Time limit guard** for optimisation tasks: `while (elapsed_sec() < 1.8)`
  keep improving a heuristic answer (`util.h`).
- Randomisation helps with heuristics (`rng_next`, `shuffle_int`).

## 20. Library reference

All headers include [`common.h`](../../lib/common.h). Sizes of static arrays are
macros (`GV_MAX`, `SEG_MAX`, …): define a smaller or larger value **before**
the `#include` when the default does not fit the task.

| Header | Contents |
|---|---|
| `common.h` | `ll`, `ull`, `MIN`, `MAX`, `SWAP`, `INF`, `LINF`, `MOD`, `MOD2` |
| `io.h` | fast `read_int`, `read_ll`, `read_word`, `read_line` |
| `util.h` | random numbers, `shuffle_int`, `floor_div`, `ceil_div`, `ipow`, `elapsed_sec` |
| `sort.h` | comparators, `sort_int`, `sort_ll`, `unique_int`, `compress`, `count_inversions`, `kth_smallest` |
| `search.h` | `lower_bound_int`, `upper_bound_int`, `bs_first_true`, `bs_real`, ternary search |
| `bits.h` | bit macros, `FOR_SUBMASKS`, Gray code, `sos_subsets`, XOR basis |
| `linear.h` | deque/queue, `next_greater`, `prev_smaller`, `sliding_max`, `max_histogram` |
| `heap.h` | binary min-heap of (key, id) |
| `hashmap.h` | `hm_*` long long → long long map, `sm_*` string → id dictionary |
| `dsu.h` | union-find, union-find with parity |
| `fenwick.h` | Fenwick tree (point/prefix, k-th), range add + range sum |
| `segtree.h` | segment tree with custom operation, lazy tree (add/assign, sum/max) |
| `sparse.h` | sparse table for idempotent range queries |
| `trie.h` | word trie, Aho–Corasick, binary trie for XOR |
| `graph.h` | adjacency arrays, BFS, components, bipartite, toposort, SCC, bridges, Kruskal |
| `paths.h` | Dijkstra, path reconstruction, 0-1 BFS, Bellman–Ford, Floyd–Warshall |
| `flow.h` | Dinic max flow, Kuhn matching, min-cost max-flow |
| `tree.h` | rooting/Euler tour, LCA, distances, diameter, heavy-light decomposition |
| `grid.h` | directions, grid BFS, flood fill regions, 2D prefix sums, rotation |
| `strutil.h` | KMP, Z-function, rolling hash, Manacher, suffix array, LCP |
| `numtheory.h` | gcd, extgcd, `powmod`, `modinv`, CRT, sieve, factorisation, Miller–Rabin, φ, `isqrt` |
| `combin.h` | factorials, `nCr`, `nPr`, Catalan, Lucas, `next_perm`, `nth_perm`, `perm_cycles` |
| `matrix.h` | matrix power, Gaussian elimination mod p and with doubles |
| `fft.h` | NTT and `poly_mul` modulo 998244353 |
| `dp.h` | Kadane, LIS, LCS, edit distance, knapsack, coin change, TSP |
| `geom.h` | integer points, cross product, segments, area, hull, point in polygon, Pick |
| `game.h` | `mex`, `nim_xor`, Grundy numbers for subtraction games and DAGs |
| `bignum.h` | big non-negative integers in base 10^9 |
| `interactive.h` | `ASK`, `reply_int` |

The library is tested by [`tests/test_lib.c`](../../tests/test_lib.c) (every
function against brute force on random data) and
[`tests/test_variants.c`](../../tests/test_variants.c); the examples by
[`tests/run_examples.sh`](../../tests/run_examples.sh).

## 21. References

Books

- A. Laaksonen, *Competitive Programmer's Handbook*, free PDF at
  <https://cses.fi/book/> — the best short introduction; and its extended
  edition *Guide to Competitive Programming*, 2nd ed., Springer, 2020.
- S. Halim, F. Halim, S. Effendy, *Competitive Programming 4*, 2020
  (<https://cpbook.net>) — classification of thousands of problems by technique.
- T. H. Cormen, C. E. Leiserson, R. L. Rivest, C. Stein, *Introduction to
  Algorithms*, 4th ed., MIT Press, 2022 — proofs and analysis (sorting, graphs,
  flows, DP, number theory, geometry).
- R. Sedgewick, *Algorithms in C*, parts 1–5, 3rd ed., Addison-Wesley — classic
  algorithms implemented in C.
- B. W. Kernighan, D. M. Ritchie, *The C Programming Language*, 2nd ed.,
  Prentice Hall, 1988.
- S. S. Skiena, *The Algorithm Design Manual*, 3rd ed., Springer, 2020 — how to
  recognise which algorithm a problem needs.
- S. S. Skiena, M. A. Revilla, *Programming Challenges*, Springer, 2003 —
  contest problems with C solutions.
- J. Kleinberg, É. Tardos, *Algorithm Design*, Pearson, 2005 — greedy
  (exchange arguments), DP and network flow modelling.
- R. L. Graham, D. E. Knuth, O. Patashnik, *Concrete Mathematics*, 2nd ed.,
  Addison-Wesley, 1994 — sums, binomials, recurrences.
- M. de Berg, O. Cheong, M. van Kreveld, M. Overmars, *Computational Geometry:
  Algorithms and Applications*, 3rd ed., Springer, 2008.

Online

- CP-Algorithms (translation of e-maxx): <https://cp-algorithms.com> — reference
  descriptions of almost every algorithm in this handbook.
- CSES Problem Set: <https://cses.fi/problemset/> — standard problems grouped by topic.
- USACO Guide: <https://usaco.guide> — structured learning path from beginner to advanced.
- IEEEXtreme: <https://ieeextreme.org>; practice archive:
  <https://csacademy.com/ieeextreme-practice/tasks/>; CS Academy lessons:
  <https://csacademy.com/lessons/>.
- OEIS: <https://oeis.org> — identify an integer sequence from its first terms.
