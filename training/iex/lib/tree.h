/* tree.h - rooted trees on top of graph.h (add tree edges with g_add2).
 *
 *   tree_root                      parent, depth, subtree size, Euler tour
 *   lca_init lca kth_ancestor tree_dist      (binary lifting)
 *   tree_diameter
 *   hld_build hld_path hld_lca     (heavy-light decomposition: path queries)
 *
 * Tree DP pattern: children appear after their parent in t_order, so
 *   for (i = n - 1; i >= 0; i--) { v = t_order[i]; combine dp of v into dp[t_par[v]]; }
 * computes bottom-up values without recursion.
 */
#ifndef XT_TREE_H
#define XT_TREE_H
#include "common.h"
#include "graph.h"

#ifndef TREE_LOG
#define TREE_LOG 20 /* 2^TREE_LOG > number of vertices */
#endif

static int t_par[GV_MAX], t_dep[GV_MAX], t_sz[GV_MAX];
static int t_tin[GV_MAX], t_tout[GV_MAX], t_order[GV_MAX], t_cnt;
static ll t_dist[GV_MAX]; /* weighted depth (sum of g_w from the root) */

/* DFS from root r (iterative). Fills t_par (-1 for r), t_dep, t_dist, t_sz,
 * preorder t_order[0..t_cnt-1] and t_tin; subtree of v = preorder indices
 * t_tin[v] .. t_tout[v], a contiguous range (for segment/Fenwick trees). O(n) */
static inline void tree_root(int r) {
    static int stk[GV_MAX];
    int top = 0;
    t_cnt = 0;
    t_par[r] = -1; t_dep[r] = 0; t_dist[r] = 0;
    stk[top++] = r;
    while (top) {
        int u = stk[--top];
        t_tin[u] = t_cnt; t_order[t_cnt++] = u;
        G_EACH(e, u) {
            int v = g_to[e];
            if (v == t_par[u]) continue;
            t_par[v] = u; t_dep[v] = t_dep[u] + 1; t_dist[v] = t_dist[u] + g_w[e];
            stk[top++] = v;
        }
    }
    for (int i = 0; i < t_cnt; i++) t_sz[t_order[i]] = 1;
    for (int i = t_cnt - 1; i > 0; i--) t_sz[t_par[t_order[i]]] += t_sz[t_order[i]];
    for (int i = 0; i < t_cnt; i++) t_tout[t_order[i]] = i + t_sz[t_order[i]] - 1;
}

/* ---------- lowest common ancestor by binary lifting ---------- */
static int t_up[TREE_LOG][GV_MAX]; /* t_up[k][v] = 2^k-th ancestor (root -> itself) */

static inline void lca_init(int r) {
    tree_root(r);
    for (int i = 0; i < t_cnt; i++) {
        int v = t_order[i];
        t_up[0][v] = t_par[v] < 0 ? v : t_par[v];
        for (int k = 1; k < TREE_LOG; k++) t_up[k][v] = t_up[k - 1][t_up[k - 1][v]];
    }
}

static inline int kth_ancestor(int v, int k) {
    for (int i = 0; k > 0 && i < TREE_LOG; i++, k >>= 1)
        if (k & 1) v = t_up[i][v];
    return v;
}

static inline int lca(int a, int b) {
    if (t_dep[a] < t_dep[b]) SWAP(int, a, b);
    a = kth_ancestor(a, t_dep[a] - t_dep[b]);
    if (a == b) return a;
    for (int k = TREE_LOG - 1; k >= 0; k--)
        if (t_up[k][a] != t_up[k][b]) { a = t_up[k][a]; b = t_up[k][b]; }
    return t_par[a];
}

/* weighted distance; number of edges is t_dep[a] + t_dep[b] - 2 * t_dep[lca] */
static inline ll tree_dist(int a, int b) { return t_dist[a] + t_dist[b] - 2 * t_dist[lca(a, b)]; }

/* longest path (non-negative weights): ends in *a, *b. Re-roots the tree. O(n) */
static inline ll tree_diameter(int start, int *a, int *b) {
    tree_root(start);
    int x = start;
    for (int i = 0; i < t_cnt; i++) if (t_dist[t_order[i]] > t_dist[x]) x = t_order[i];
    tree_root(x);
    int y = x;
    for (int i = 0; i < t_cnt; i++) if (t_dist[t_order[i]] > t_dist[y]) y = t_order[i];
    *a = x; *b = y;
    return t_dist[y];
}

/* ---------- heavy-light decomposition ----------
 * Every path is split into O(log n) chains; t_pos numbers vertices so that
 * each chain AND each subtree is a contiguous range of positions:
 *   subtree of v = positions t_pos[v] .. t_pos[v] + t_sz[v] - 1.
 * Put values in a segment tree indexed by t_pos and query paths with hld_path. */
static int t_heavy[GV_MAX], t_head[GV_MAX], t_pos[GV_MAX];

static inline void hld_build(int r) {
    static int stk[GV_MAX];
    int top = 0, cur = 0;
    tree_root(r);
    for (int i = 0; i < t_cnt; i++) t_heavy[t_order[i]] = -1;
    for (int i = t_cnt - 1; i > 0; i--) { /* heavy child = largest subtree */
        int v = t_order[i], p = t_par[v];
        if (t_heavy[p] == -1 || t_sz[v] > t_sz[t_heavy[p]]) t_heavy[p] = v;
    }
    t_head[r] = r;
    stk[top++] = r;
    while (top) {
        int u = stk[--top];
        t_pos[u] = cur++;
        G_EACH(e, u) { /* light children start new chains */
            int v = g_to[e];
            if (v != t_par[u] && v != t_heavy[u]) { t_head[v] = v; stk[top++] = v; }
        }
        if (t_heavy[u] != -1) { /* heavy child is visited next */
            t_head[t_heavy[u]] = t_head[u];
            stk[top++] = t_heavy[u];
        }
    }
}

/* call f(l, r) for the position ranges covering the path u..v.
 * edges = 1 skips the LCA (when values live on edges, stored at the child). */
static inline void hld_path(int u, int v, int edges, void (*f)(int l, int r)) {
    while (t_head[u] != t_head[v]) {
        if (t_dep[t_head[u]] < t_dep[t_head[v]]) SWAP(int, u, v);
        f(t_pos[t_head[u]], t_pos[u]);
        u = t_par[t_head[u]];
    }
    if (t_dep[u] > t_dep[v]) SWAP(int, u, v);
    if (t_pos[u] + edges <= t_pos[v]) f(t_pos[u] + edges, t_pos[v]);
}

static inline int hld_lca(int u, int v) {
    while (t_head[u] != t_head[v]) {
        if (t_dep[t_head[u]] < t_dep[t_head[v]]) SWAP(int, u, v);
        u = t_par[t_head[u]];
    }
    return t_dep[u] < t_dep[v] ? u : v;
}

#endif
