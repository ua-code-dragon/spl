/* fenwick.h - Fenwick tree (binary indexed tree), 1-indexed.
 *
 *   fen_init fen_add fen_sum fen_range fen_lower_bound    point add, prefix sum
 *   fenr_init fenr_add fenr_sum                           range add, range sum
 *
 * Every operation is O(log n) and the code is tiny,
 * so prefer it to a segment tree whenever only sums are needed.
 */
#ifndef XT_FENWICK_H
#define XT_FENWICK_H
#include "common.h"

#ifndef FEN_MAX
#define FEN_MAX 1000005
#endif

/* ---------- point update, prefix query ---------- */
static ll fen[FEN_MAX];
static int fen_n;

static inline void fen_init(int n) { fen_n = n; memset(fen, 0, sizeof(ll) * (size_t)(n + 1)); }

static inline void fen_add(int i, ll v) { for (; i <= fen_n; i += i & -i) fen[i] += v; }

static inline ll fen_sum(int i) { /* a[1] + ... + a[i] */
    ll s = 0;
    for (; i > 0; i -= i & -i) s += fen[i];
    return s;
}

static inline ll fen_range(int l, int r) { return fen_sum(r) - fen_sum(l - 1); }

/* smallest i with a[1] + ... + a[i] >= k (all a >= 0); fen_n + 1 if none.
 * With a[v] = count of value v this finds the k-th smallest stored value. */
static inline int fen_lower_bound(ll k) {
    int pos = 0, step = 1;
    while (step * 2 <= fen_n) step *= 2;
    for (; step; step /= 2)
        if (pos + step <= fen_n && fen[pos + step] < k) {
            pos += step;
            k -= fen[pos];
        }
    return pos + 1;
}

/* ---------- range update, range query (two trees) ---------- */
static ll fenr1[FEN_MAX], fenr2[FEN_MAX];
static int fenr_n;

static inline void fenr_init(int n) {
    fenr_n = n;
    memset(fenr1, 0, sizeof(ll) * (size_t)(n + 2));
    memset(fenr2, 0, sizeof(ll) * (size_t)(n + 2));
}

static inline void fenr_upd_(ll *f, int i, ll v) { for (; i <= fenr_n; i += i & -i) f[i] += v; }
static inline ll fenr_pre_(const ll *f, int i) { ll s = 0; for (; i > 0; i -= i & -i) s += f[i]; return s; }
static inline ll fenr_prefix_(int i) { return fenr_pre_(fenr1, i) * i - fenr_pre_(fenr2, i); }

/* a[l..r] += v */
static inline void fenr_add(int l, int r, ll v) {
    fenr_upd_(fenr1, l, v);
    fenr_upd_(fenr1, r + 1, -v);
    fenr_upd_(fenr2, l, v * (l - 1));
    fenr_upd_(fenr2, r + 1, -v * r);
}

/* a[l] + ... + a[r] */
static inline ll fenr_sum(int l, int r) { return fenr_prefix_(r) - fenr_prefix_(l - 1); }

#endif
