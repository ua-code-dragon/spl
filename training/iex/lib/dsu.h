/* dsu.h - disjoint set union (union-find) and its parity variant.
 *
 *   dsu_init dsu_find dsu_union dsu_same dsu_size        + dsu_sets counter
 *   pdsu_init pdsu_find pdsu_union                        (relations "same/different")
 *
 * Typical uses: connected components with edges added online, Kruskal MST,
 * grouping equal things, checking whether a graph stays bipartite.
 */
#ifndef XT_DSU_H
#define XT_DSU_H
#include "common.h"

#ifndef DSU_MAX
#define DSU_MAX 1000005
#endif

static int dsu_p[DSU_MAX], dsu_sz[DSU_MAX];
static int dsu_sets; /* current number of sets */

static inline void dsu_init(int n) { /* elements 0..n-1 */
    for (int i = 0; i < n; i++) { dsu_p[i] = i; dsu_sz[i] = 1; }
    dsu_sets = n;
}

/* representative of x's set, with path halving: almost O(1) amortized */
static inline int dsu_find(int x) {
    while (dsu_p[x] != x) {
        dsu_p[x] = dsu_p[dsu_p[x]];
        x = dsu_p[x];
    }
    return x;
}

/* merge the sets of a and b; returns 0 if they were already together */
static inline int dsu_union(int a, int b) {
    a = dsu_find(a); b = dsu_find(b);
    if (a == b) return 0;
    if (dsu_sz[a] < dsu_sz[b]) SWAP(int, a, b); /* union by size */
    dsu_p[b] = a;
    dsu_sz[a] += dsu_sz[b];
    dsu_sets--;
    return 1;
}

static inline int dsu_same(int a, int b) { return dsu_find(a) == dsu_find(b); }
static inline int dsu_size(int x) { return dsu_sz[dsu_find(x)]; }

/* ---------- DSU with parity ----------
 * Keeps, for every element, its parity (0/1) relative to the set root.
 * pdsu_union(a, b, d) states color(a) XOR color(b) == d and returns 0 if
 * that contradicts earlier statements (e.g. an odd cycle for d = 1). */
static int pd_p[DSU_MAX], pd_sz[DSU_MAX], pd_rel[DSU_MAX];

static inline void pdsu_init(int n) {
    for (int i = 0; i < n; i++) { pd_p[i] = i; pd_sz[i] = 1; pd_rel[i] = 0; }
}

/* root of x; *parity = color(x) XOR color(root). O(log n) (no path compression) */
static inline int pdsu_find(int x, int *parity) {
    int r = 0;
    while (pd_p[x] != x) { r ^= pd_rel[x]; x = pd_p[x]; }
    *parity = r;
    return x;
}

static inline int pdsu_union(int a, int b, int d) {
    int pa, pb;
    a = pdsu_find(a, &pa);
    b = pdsu_find(b, &pb);
    if (a == b) return (pa ^ pb) == d;
    if (pd_sz[a] < pd_sz[b]) SWAP(int, a, b);
    pd_p[b] = a;
    pd_rel[b] = pa ^ pb ^ d;
    pd_sz[a] += pd_sz[b];
    return 1;
}

#endif
