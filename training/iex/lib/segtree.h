/* segtree.h - segment trees, positions 0..n-1.
 *
 *   seg_init seg_set seg_get seg_query                 point update, range query
 *   lz_init lz_add lz_assign lz_sum lz_max             range add/assign, range sum/max
 *
 * The simple tree combines with SEG_OP (any associative operation) and its
 * identity SEG_ID. Default is sum; for minimum define before the include:
 *   #define SEG_OP(a, b) ((a) < (b) ? (a) : (b))
 *   #define SEG_ID LINF
 */
#ifndef XT_SEGTREE_H
#define XT_SEGTREE_H
#include "common.h"

#ifndef SEG_MAX
#define SEG_MAX 1000005
#endif
#ifndef SEG_OP
#define SEG_OP(a, b) ((a) + (b))
#define SEG_ID 0
#endif

/* ---------- bottom-up tree: leaves at seg[n .. 2n-1] ---------- */
static ll seg[2 * SEG_MAX];
static int seg_n;

/* build from a[0..n-1] (a may be NULL: all SEG_ID). O(n) */
static inline void seg_init(int n, const ll *a) {
    seg_n = n;
    for (int i = 0; i < n; i++) seg[n + i] = a ? a[i] : SEG_ID;
    for (int i = n - 1; i > 0; i--) seg[i] = SEG_OP(seg[2 * i], seg[2 * i + 1]);
}

/* a[i] = v. O(log n) */
static inline void seg_set(int i, ll v) {
    i += seg_n;
    seg[i] = v;
    for (i /= 2; i > 0; i /= 2) seg[i] = SEG_OP(seg[2 * i], seg[2 * i + 1]);
}

static inline ll seg_get(int i) { return seg[i + seg_n]; }

/* SEG_OP over a[l..r] inclusive (order is kept, so non-commutative ops work). O(log n) */
static inline ll seg_query(int l, int r) {
    ll left = SEG_ID, right = SEG_ID;
    for (l += seg_n, r += seg_n + 1; l < r; l /= 2, r /= 2) {
        if (l & 1) { left = SEG_OP(left, seg[l]); l++; }
        if (r & 1) { r--; right = SEG_OP(seg[r], right); }
    }
    return SEG_OP(left, right);
}

/* ---------- lazy propagation: range add / range assign, range sum / max ---------- */
#ifndef LSEG_MAX
#define LSEG_MAX 200005
#endif
static ll lz_s[4 * LSEG_MAX], lz_m[4 * LSEG_MAX]; /* sum and max of the node   */
static ll lz_ad[4 * LSEG_MAX], lz_as[4 * LSEG_MAX]; /* pending add / assign value */
static char lz_has_as[4 * LSEG_MAX]; /* is an assign pending?      */
static int lz_n;

static inline void lz_build_(int x, int l, int r, const ll *a) {
    lz_ad[x] = 0; lz_has_as[x] = 0;
    if (l == r) { lz_s[x] = lz_m[x] = a ? a[l] : 0; return; }
    int mid = (l + r) / 2;
    lz_build_(2 * x, l, mid, a);
    lz_build_(2 * x + 1, mid + 1, r, a);
    lz_s[x] = lz_s[2 * x] + lz_s[2 * x + 1];
    lz_m[x] = MAX(lz_m[2 * x], lz_m[2 * x + 1]);
}

static inline void lz_init(int n, const ll *a) { lz_n = n; lz_build_(1, 0, n - 1, a); }

/* apply "set every value to v" to a whole node of length len */
static inline void lz_apply_as_(int x, int len, ll v) {
    lz_s[x] = v * len; lz_m[x] = v;
    lz_as[x] = v; lz_has_as[x] = 1; lz_ad[x] = 0;
}

/* apply "add v to every value" to a whole node */
static inline void lz_apply_ad_(int x, int len, ll v) {
    lz_s[x] += v * len; lz_m[x] += v;
    if (lz_has_as[x]) lz_as[x] += v; else lz_ad[x] += v;
}

/* hand the pending operation of x down to its children */
static inline void lz_push_(int x, int l, int r) {
    int mid = (l + r) / 2;
    if (lz_has_as[x]) {
        lz_apply_as_(2 * x, mid - l + 1, lz_as[x]);
        lz_apply_as_(2 * x + 1, r - mid, lz_as[x]);
        lz_has_as[x] = 0;
    }
    if (lz_ad[x]) {
        lz_apply_ad_(2 * x, mid - l + 1, lz_ad[x]);
        lz_apply_ad_(2 * x + 1, r - mid, lz_ad[x]);
        lz_ad[x] = 0;
    }
}

static inline void lz_update_(int x, int l, int r, int ql, int qr, ll v, int assign) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        if (assign) lz_apply_as_(x, r - l + 1, v); else lz_apply_ad_(x, r - l + 1, v);
        return;
    }
    lz_push_(x, l, r);
    int mid = (l + r) / 2;
    lz_update_(2 * x, l, mid, ql, qr, v, assign);
    lz_update_(2 * x + 1, mid + 1, r, ql, qr, v, assign);
    lz_s[x] = lz_s[2 * x] + lz_s[2 * x + 1];
    lz_m[x] = MAX(lz_m[2 * x], lz_m[2 * x + 1]);
}

static inline void lz_query_(int x, int l, int r, int ql, int qr, ll *sum, ll *mx) {
    if (qr < l || r < ql) return;
    if (ql <= l && r <= qr) {
        *sum += lz_s[x];
        if (lz_m[x] > *mx) *mx = lz_m[x];
        return;
    }
    lz_push_(x, l, r);
    int mid = (l + r) / 2;
    lz_query_(2 * x, l, mid, ql, qr, sum, mx);
    lz_query_(2 * x + 1, mid + 1, r, ql, qr, sum, mx);
}

/* a[l..r] += v / a[l..r] = v. O(log n) */
static inline void lz_add(int l, int r, ll v) { lz_update_(1, 0, lz_n - 1, l, r, v, 0); }
static inline void lz_assign(int l, int r, ll v) { lz_update_(1, 0, lz_n - 1, l, r, v, 1); }

/* sum / maximum of a[l..r]. O(log n) */
static inline ll lz_sum(int l, int r) { ll s = 0, m = -LINF; lz_query_(1, 0, lz_n - 1, l, r, &s, &m); return s; }
static inline ll lz_max(int l, int r) { ll s = 0, m = -LINF; lz_query_(1, 0, lz_n - 1, l, r, &s, &m); return m; }

#endif
