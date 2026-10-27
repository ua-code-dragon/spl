/* paths.h - shortest paths on the graph of graph.h.
 *
 *   dijkstra build_path bfs01 bellman_ford | fw_init floyd
 *
 * Which one?
 *   all weights 1 ............ bfs (graph.h)              O(V + E)
 *   weights 0 or 1 ........... bfs01                      O(V + E)
 *   weights >= 0 ............. dijkstra                   O(E log E)
 *   negative weights ......... bellman_ford               O(V E)
 *   all pairs, V <= 400 ...... floyd                      O(V^3)
 * Unreachable vertices get distance LINF.
 */
#ifndef XT_PATHS_H
#define XT_PATHS_H
#include "common.h"
#include "graph.h"
#include "heap.h"
#include "linear.h"

/* dist[v] from src; prev[v] = previous vertex on a shortest path (prev may be NULL) */
static inline void dijkstra(int src, ll *dist, int *prev) {
    static Heap pq;
    for (int i = 0; i < g_n; i++) { dist[i] = LINF; if (prev) prev[i] = -1; }
    heap_clear(&pq);
    dist[src] = 0;
    heap_push(&pq, 0, src);
    while (!heap_empty(&pq)) {
        HeapItem top = heap_pop(&pq);
        int u = top.id;
        if (top.key != dist[u]) continue; /* outdated entry, skip */
        G_EACH(e, u) {
            int v = g_to[e];
            ll nd = dist[u] + g_w[e];
            if (nd < dist[v]) {
                dist[v] = nd;
                if (prev) prev[v] = u;
                heap_push(&pq, nd, v);
            }
        }
    }
}

/* path ending at t from prev[] (dijkstra): path[0] = source ... path[k-1] = t, returns k */
static inline int build_path(const int *prev, int t, int *path) {
    int k = 0;
    for (int v = t; v != -1; v = prev[v]) path[k++] = v;
    for (int i = 0, j = k - 1; i < j; i++, j--) SWAP(int, path[i], path[j]);
    return k;
}

/* 0-1 BFS: weights must be 0 or 1. A 0-edge goes to the deque front. */
static inline void bfs01(int src, ll *dist) {
    static Deque dq;
    for (int i = 0; i < g_n; i++) dist[i] = LINF;
    dq_clear(&dq);
    dist[src] = 0;
    dq_push_back(&dq, src);
    while (!dq_empty(&dq)) {
        int u = dq_pop_front(&dq);
        G_EACH(e, u) {
            int v = g_to[e];
            if (dist[u] + g_w[e] < dist[v]) {
                dist[v] = dist[u] + g_w[e];
                if (g_w[e] == 0) dq_push_front(&dq, v); else dq_push_back(&dq, v);
            }
        }
    }
}

/* Bellman-Ford with negative weights. Returns 0 if a negative cycle is
 * reachable from src (then distances are meaningless), 1 otherwise. */
static inline int bellman_ford(int src, ll *dist) {
    for (int i = 0; i < g_n; i++) dist[i] = LINF;
    dist[src] = 0;
    for (int round = 0; round < g_n; round++) {
        int changed = 0;
        for (int u = 0; u < g_n; u++) {
            if (dist[u] == LINF) continue;
            G_EACH(e, u)
                if (dist[u] + g_w[e] < dist[g_to[e]]) { dist[g_to[e]] = dist[u] + g_w[e]; changed = 1; }
        }
        if (!changed) return 1;
    }
    return 0; /* still improving after V rounds */
}

/* ---------- Floyd-Warshall: all pairs ---------- */
#ifndef FW_N
#define FW_N 405
#endif
static ll fw[FW_N][FW_N];

/* fw[i][j] = 0 on the diagonal, LINF elsewhere; then set edges fw[u][v] = MIN(fw[u][v], w) */
static inline void fw_init(int n) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) fw[i][j] = (i == j) ? 0 : LINF;
}

/* afterwards fw[i][j] = shortest distance; fw[i][i] < 0 means i is on a negative cycle */
static inline void floyd(int n) {
    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++) {
            if (fw[i][k] == LINF) continue;
            for (int j = 0; j < n; j++)
                if (fw[k][j] != LINF && fw[i][k] + fw[k][j] < fw[i][j]) fw[i][j] = fw[i][k] + fw[k][j];
        }
}

#endif
