/* graph.h - graph storage (adjacency lists in arrays) and traversals.
 *
 *   g_init g_add g_add2 G_EACH
 *   bfs bfs_multi components bipartite toposort scc bridges kruskal
 *
 * Storage ("forward star"): edge e goes to g_to[e] with weight g_w[e];
 * loop over the edges leaving u:  G_EACH(e, u) { int v = g_to[e]; ... }
 * Vertices are 0..n-1. For 1-indexed input call g_init(n + 1).
 * All algorithms here are iterative: no stack overflow on 10^6 vertices.
 */
#ifndef XT_GRAPH_H
#define XT_GRAPH_H
#include "common.h"
#include "dsu.h"

#ifndef GV_MAX
#define GV_MAX 200005 /* vertices */
#endif
#ifndef GE_MAX
#define GE_MAX 400005 /* directed edges (an undirected edge takes two) */
#endif

static int g_head[GV_MAX], g_nxt[GE_MAX], g_to[GE_MAX];
static ll g_w[GE_MAX];
static int g_n, g_m;

#define G_EACH(e, u) for (int e = g_head[u]; e != -1; e = g_nxt[e])

static inline void g_init(int n) {
    g_n = n; g_m = 0;
    for (int i = 0; i < n; i++) g_head[i] = -1;
}

/* directed edge u -> v; returns its id */
static inline int g_add(int u, int v, ll w) {
    g_to[g_m] = v; g_w[g_m] = w;
    g_nxt[g_m] = g_head[u]; g_head[u] = g_m;
    return g_m++;
}

/* undirected edge: ids 2k and 2k+1 (if only g_add2 is used), reverse of e is e ^ 1 */
static inline void g_add2(int u, int v, ll w) { g_add(u, v, w); g_add(v, u, w); }

/* ---------- BFS: shortest paths counted in edges. O(V + E) ---------- */
static int g_queue[GV_MAX];

/* dist[v] = edges from the nearest of the k sources, -1 if unreachable */
static inline void bfs_multi(const int *src, int k, int *dist) {
    int h = 0, t = 0;
    for (int i = 0; i < g_n; i++) dist[i] = -1;
    for (int i = 0; i < k; i++)
        if (dist[src[i]] < 0) { dist[src[i]] = 0; g_queue[t++] = src[i]; }
    while (h < t) {
        int u = g_queue[h++];
        G_EACH(e, u) {
            int v = g_to[e];
            if (dist[v] < 0) { dist[v] = dist[u] + 1; g_queue[t++] = v; }
        }
    }
}

static inline void bfs(int src, int *dist) { bfs_multi(&src, 1, dist); }

/* connected components of an undirected graph: comp[v] in 0..k-1, returns k */
static inline int components(int *comp) {
    int k = 0;
    for (int i = 0; i < g_n; i++) comp[i] = -1;
    for (int s = 0; s < g_n; s++) {
        if (comp[s] >= 0) continue;
        int h = 0, t = 0;
        comp[s] = k; g_queue[t++] = s;
        while (h < t) {
            int u = g_queue[h++];
            G_EACH(e, u) if (comp[g_to[e]] < 0) { comp[g_to[e]] = k; g_queue[t++] = g_to[e]; }
        }
        k++;
    }
    return k;
}

/* 2-coloring color[v] in {0,1} so every edge joins different colors;
 * returns 0 if impossible (the graph has an odd cycle) */
static inline int bipartite(int *color) {
    for (int i = 0; i < g_n; i++) color[i] = -1;
    for (int s = 0; s < g_n; s++) {
        if (color[s] >= 0) continue;
        int h = 0, t = 0;
        color[s] = 0; g_queue[t++] = s;
        while (h < t) {
            int u = g_queue[h++];
            G_EACH(e, u) {
                int v = g_to[e];
                if (color[v] < 0) { color[v] = color[u] ^ 1; g_queue[t++] = v; }
                else if (color[v] == color[u]) return 0;
            }
        }
    }
    return 1;
}

/* topological order of a directed graph (Kahn's algorithm). Returns how many
 * vertices were ordered: less than g_n means the graph has a cycle. */
static inline int toposort(int *order) {
    static int indeg[GV_MAX];
    int h = 0, t = 0;
    for (int i = 0; i < g_n; i++) indeg[i] = 0;
    for (int u = 0; u < g_n; u++) G_EACH(e, u) indeg[g_to[e]]++;
    for (int i = 0; i < g_n; i++) if (indeg[i] == 0) order[t++] = i;
    while (h < t) {
        int u = order[h++];
        G_EACH(e, u) if (--indeg[g_to[e]] == 0) order[t++] = g_to[e];
    }
    return t;
}

/* ---------- strongly connected components (Tarjan, iterative) ----------
 * scc_id[v] in 0..k-1, returns k. Components come out in reverse topological
 * order: for an edge u -> v between different components scc_id[u] > scc_id[v]. */
static int scc_id[GV_MAX];

static inline int scc(void) {
    static int idx[GV_MAX], low[GV_MAX], st[GV_MAX], it[GV_MAX], cs[GV_MAX];
    static char onst[GV_MAX];
    int timer = 0, top = 0, k = 0;
    for (int i = 0; i < g_n; i++) { idx[i] = -1; onst[i] = 0; }
    for (int s = 0; s < g_n; s++) {
        if (idx[s] != -1) continue;
        int csz = 0;
        idx[s] = low[s] = timer++; st[top++] = s; onst[s] = 1; it[s] = g_head[s]; cs[csz++] = s;
        while (csz) {
            int u = cs[csz - 1];
            if (it[u] != -1) { /* next edge of u */
                int v = g_to[it[u]];
                it[u] = g_nxt[it[u]];
                if (idx[v] == -1) {
                    idx[v] = low[v] = timer++; st[top++] = v; onst[v] = 1;
                    it[v] = g_head[v]; cs[csz++] = v;
                } else if (onst[v] && idx[v] < low[u]) low[u] = idx[v];
            } else { /* u is finished */
                csz--;
                if (csz && low[u] < low[cs[csz - 1]]) low[cs[csz - 1]] = low[u];
                if (low[u] == idx[u]) {
                    int v;
                    do { v = st[--top]; onst[v] = 0; scc_id[v] = k; } while (v != u);
                    k++;
                }
            }
        }
    }
    return k;
}

/* ---------- bridges and articulation points (undirected, edges via g_add2) ----------
 * g_bridge[e] = 1 for both directions of every bridge (removal disconnects);
 * g_cut[v] = 1 for every articulation point. Returns the number of bridges. */
static char g_bridge[GE_MAX], g_cut[GV_MAX];

static inline int bridges(void) {
    static int tin[GV_MAX], low[GV_MAX], pe[GV_MAX], it[GV_MAX], cs[GV_MAX], kids[GV_MAX];
    int timer = 0, cnt = 0;
    memset(g_bridge, 0, (size_t)g_m);
    for (int i = 0; i < g_n; i++) { tin[i] = -1; g_cut[i] = 0; kids[i] = 0; }
    for (int s = 0; s < g_n; s++) {
        if (tin[s] != -1) continue;
        int csz = 0;
        tin[s] = low[s] = timer++; pe[s] = -1; it[s] = g_head[s]; cs[csz++] = s;
        while (csz) {
            int u = cs[csz - 1];
            if (it[u] != -1) {
                int e = it[u];
                it[u] = g_nxt[e];
                if ((e ^ 1) == pe[u]) continue; /* do not go back along the same edge */
                int v = g_to[e];
                if (tin[v] == -1) {
                    tin[v] = low[v] = timer++; pe[v] = e; it[v] = g_head[v]; cs[csz++] = v;
                    kids[u]++;
                } else if (tin[v] < low[u]) low[u] = tin[v];
            } else {
                csz--;
                if (pe[u] == -1) { g_cut[u] = kids[u] > 1; continue; } /* root */
                int p = g_to[pe[u] ^ 1];
                if (low[u] < low[p]) low[p] = low[u];
                if (low[u] > tin[p]) { g_bridge[pe[u]] = g_bridge[pe[u] ^ 1] = 1; cnt++; }
                if (low[u] >= tin[p] && pe[p] != -1) g_cut[p] = 1;
            }
        }
    }
    return cnt;
}

/* ---------- minimum spanning tree (Kruskal) ---------- */
typedef struct { int u, v; ll w; int used; } Edge;

static inline int edge_cmp_(const void *a, const void *b) {
    ll x = ((const Edge *)a)->w, y = ((const Edge *)b)->w;
    return (x > y) - (x < y);
}

/* minimum spanning forest of vertices 0..n-1: sorts e[], sets e[i].used,
 * returns the total weight. Connected iff dsu_sets == 1 afterwards. O(E log E) */
static inline ll kruskal(int n, Edge *e, int m) {
    ll total = 0;
    qsort(e, (size_t)m, sizeof(Edge), edge_cmp_);
    dsu_init(n);
    for (int i = 0; i < m; i++) {
        e[i].used = dsu_union(e[i].u, e[i].v);
        if (e[i].used) total += e[i].w;
    }
    return total;
}

#endif
