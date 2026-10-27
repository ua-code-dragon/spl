/* trie.h - prefix tree, Aho-Corasick automaton, binary trie for XOR.
 *
 *   trie_insert trie_walk trie_count_prefix trie_count_word   (lowercase words)
 *   ac_build ac_count                                          (many patterns in a text)
 *   bt_insert bt_max_xor bt_count_less              (sets of integers by bits)
 */
#ifndef XT_TRIE_H
#define XT_TRIE_H
#include "common.h"

#ifndef TRIE_MAX
#define TRIE_MAX 200005 /* total length of all words + 1 */
#endif
#define TRIE_A 26 /* alphabet 'a'..'z' */

/* node 0 is the root. tr_cnt[v] = words having v's string as a prefix,
 * tr_end[v] = words equal to v's string. */
static int tr_next[TRIE_MAX][TRIE_A], tr_cnt[TRIE_MAX], tr_end[TRIE_MAX];
static int tr_nodes = 1;

static inline int trie_insert(const char *s) {
    int v = 0;
    tr_cnt[0]++;
    for (; *s; s++) {
        int c = *s - 'a';
        if (!tr_next[v][c]) tr_next[v][c] = tr_nodes++;
        v = tr_next[v][c];
        tr_cnt[v]++;
    }
    tr_end[v]++;
    return v;
}

/* node of string s, -1 if no inserted word starts with s */
static inline int trie_walk(const char *s) {
    int v = 0;
    for (; *s && v >= 0; s++) v = tr_next[v][*s - 'a'] ? tr_next[v][*s - 'a'] : -1;
    return v;
}

static inline int trie_count_prefix(const char *s) { int v = trie_walk(s); return v < 0 ? 0 : tr_cnt[v]; }
static inline int trie_count_word(const char *s) { int v = trie_walk(s); return v < 0 ? 0 : tr_end[v]; }

/* ---------- Aho-Corasick ----------
 * After inserting all patterns call ac_build(). Then tr_next[v][c] is the
 * automaton move for every v, c; tr_link[v] = longest proper suffix of v's
 * string that is a trie node; tr_out[v] = patterns ending at that position.
 * Do not insert after ac_build. Total O(sum of lengths * 26). */
static int tr_link[TRIE_MAX], tr_out[TRIE_MAX], tr_bfs[TRIE_MAX];

static inline void ac_build(void) {
    int head = 0, tail = 0;
    tr_out[0] = tr_end[0];
    for (int c = 0; c < TRIE_A; c++)
        if (tr_next[0][c]) { tr_link[tr_next[0][c]] = 0; tr_bfs[tail++] = tr_next[0][c]; }
    while (head < tail) { /* BFS: links point to shallower nodes */
        int v = tr_bfs[head++];
        tr_out[v] = tr_end[v] + tr_out[tr_link[v]];
        for (int c = 0; c < TRIE_A; c++) {
            int u = tr_next[v][c];
            if (u) { tr_link[u] = tr_next[tr_link[v]][c]; tr_bfs[tail++] = u; }
            else tr_next[v][c] = tr_next[tr_link[v]][c];
        }
    }
}

/* total number of pattern occurrences in text. O(|text|) */
static inline ll ac_count(const char *text) {
    ll total = 0;
    int v = 0;
    for (; *text; text++) {
        v = tr_next[v][*text - 'a'];
        total += tr_out[v];
    }
    return total;
}

/* ---------- binary trie over BT_BITS-bit non-negative integers (multiset) ---------- */
#ifndef BT_BITS
#define BT_BITS 30
#endif
#ifndef BT_MAX
#define BT_MAX (1 << 21) /* about (numbers inserted) * BT_BITS nodes */
#endif
static int bt_next[BT_MAX][2], bt_cnt[BT_MAX];
static int bt_nodes = 1;

/* delta = +1 inserts x, -1 removes one copy of x */
static inline void bt_insert(int x, int delta) {
    int v = 0;
    bt_cnt[0] += delta;
    for (int i = BT_BITS - 1; i >= 0; i--) {
        int b = x >> i & 1;
        if (!bt_next[v][b]) bt_next[v][b] = bt_nodes++;
        v = bt_next[v][b];
        bt_cnt[v] += delta;
    }
}

/* max of x ^ y over stored y (set not empty). O(BT_BITS). Min: prefer the same bit. */
static inline int bt_max_xor(int x) {
    int v = 0, r = 0;
    for (int i = BT_BITS - 1; i >= 0; i--) {
        int want = !(x >> i & 1); /* greedily take the opposite bit */
        int u = bt_next[v][want];
        if (u && bt_cnt[u] > 0) { r |= 1 << i; v = u; } else v = bt_next[v][!want];
    }
    return r;
}

/* how many stored y have (x ^ y) < k */
static inline int bt_count_less(int x, int k) {
    int v = 0, res = 0;
    for (int i = BT_BITS - 1; i >= 0; i--) {
        int xb = x >> i & 1, kb = k >> i & 1;
        if (kb) { /* y bit = xb gives xor bit 0 < 1 */
            int u = bt_next[v][xb];
            if (u) res += bt_cnt[u];
            v = bt_next[v][!xb];
        } else {
            v = bt_next[v][xb];
        }
        if (!v) return res;
    }
    return res;
}

#endif
