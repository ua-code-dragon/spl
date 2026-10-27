/* sparse.h - sparse table: O(1) range queries on a static array.
 *
 *   sp_build sp_query
 *
 * Works for idempotent operations (x op x == x): min (default), max, gcd,
 * bitwise and/or. For max define before the include:
 *   #define SP_OP(a, b) ((a) > (b) ? (a) : (b))
 * Build O(n log n), query O(1). No updates (use segtree.h for those).
 */
#ifndef XT_SPARSE_H
#define XT_SPARSE_H
#include "common.h"

#ifndef SP_MAX
#define SP_MAX 200005
#endif
#ifndef SP_LOG
#define SP_LOG 18 /* 2^SP_LOG >= SP_MAX */
#endif
#ifndef SP_OP
#define SP_OP(a, b) ((a) < (b) ? (a) : (b))
#endif

static ll sp[SP_LOG + 1][SP_MAX]; /* sp[k][i] = op of a[i .. i + 2^k - 1] */
static int sp_lg[SP_MAX + 1]; /* sp_lg[x] = floor(log2 x) */

static inline void sp_build(const ll *a, int n) {
    sp_lg[1] = 0;
    for (int i = 2; i <= n; i++) sp_lg[i] = sp_lg[i / 2] + 1;
    for (int i = 0; i < n; i++) sp[0][i] = a[i];
    for (int k = 1; (1 << k) <= n; k++)
        for (int i = 0; i + (1 << k) <= n; i++)
            sp[k][i] = SP_OP(sp[k - 1][i], sp[k - 1][i + (1 << (k - 1))]);
}

/* op over a[l..r] inclusive: two overlapping power-of-two blocks */
static inline ll sp_query(int l, int r) {
    int k = sp_lg[r - l + 1];
    return SP_OP(sp[k][l], sp[k][r - (1 << k) + 1]);
}

#endif
