/* game.h - impartial games: Nim and Sprague-Grundy numbers.
 *
 *   mex nim_xor grundy_subtraction grundy_dag
 *
 * Theory in two lines: a position is losing for the player to move iff its
 * Grundy number is 0; Grundy(position) = mex of Grundy numbers of the moves;
 * a sum of independent games has Grundy number = XOR of the parts (Nim).
 * For small partizan / scoring games use plain memoized DP (win/lose states).
 */
#ifndef XT_GAME_H
#define XT_GAME_H
#include "common.h"
#include "graph.h"

#ifndef GAME_MAX
#define GAME_MAX 1000005
#endif

/* minimum excluded value: smallest non-negative integer not in v[0..k-1]. O(k) */
static inline int mex(const int *v, int k) {
    static char seen[GAME_MAX];
    memset(seen, 0, (size_t)k + 1);
    for (int i = 0; i < k; i++) if (v[i] >= 0 && v[i] <= k) seen[v[i]] = 1;
    int g = 0;
    while (seen[g]) g++;
    return g;
}

/* Nim: the first player wins iff the XOR of the pile sizes is not 0 */
static inline ll nim_xor(const ll *pile, int n) {
    ll x = 0;
    for (int i = 0; i < n; i++) x ^= pile[i];
    return x;
}

/* subtraction game: from a pile of x remove m stones for some m in moves[].
 * Fills g[0..n] with Grundy numbers. O(n k) */
static inline void grundy_subtraction(int n, const int *moves, int k, int *g) {
    static int opt[GAME_MAX];
    for (int x = 0; x <= n; x++) {
        int c = 0;
        for (int i = 0; i < k; i++) if (moves[i] <= x) opt[c++] = g[x - moves[i]];
        g[x] = mex(opt, c);
    }
}

/* game on a DAG stored in graph.h (edge u -> v = a move from u to v).
 * Fills g[v]; vertices without moves get 0. Returns 0 if the graph has a cycle. */
static inline int grundy_dag(int *g) {
    static int order[GV_MAX], opt[GV_MAX];
    if (toposort(order) < g_n) return 0;
    for (int i = g_n - 1; i >= 0; i--) { /* successors first */
        int u = order[i], c = 0;
        G_EACH(e, u) opt[c++] = g[g_to[e]];
        g[u] = mex(opt, c);
    }
    return 1;
}

#endif
