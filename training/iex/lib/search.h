/* search.h - binary search and ternary search.
 *
 *   lower_bound_int upper_bound_int   (for ll arrays copy them and change int to ll)
 *   bs_first_true bs_real | ternary_min_int ternary_min_real
 *
 * "Binary search on the answer": if a predicate ok(x) is false,false,...,
 * true,true (monotone), the smallest true x is found with O(log range) calls.
 */
#ifndef XT_SEARCH_H
#define XT_SEARCH_H
#include "common.h"

/* first index i with a[i] >= x in sorted a[0..n-1]; n if none */
static inline int lower_bound_int(const int *a, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] < x) lo = mid + 1; else hi = mid;
    }
    return lo;
}

/* first index i with a[i] > x; n if none.
 * Count of x in a sorted array: upper_bound - lower_bound. */
static inline int upper_bound_int(const int *a, int n, int x) {
    int lo = 0, hi = n;
    while (lo < hi) {
        int mid = lo + (hi - lo) / 2;
        if (a[mid] <= x) lo = mid + 1; else hi = mid;
    }
    return lo;
}

/* smallest x in [lo, hi] with ok(x) true, for ok = F..F T..T; hi + 1 if none.
 * (largest x with T..T F..F: search the first x where !ok(x), then subtract 1) */
static inline ll bs_first_true(ll lo, ll hi, int (*ok)(ll)) {
    ll r = hi + 1;
    while (lo <= hi) {
        ll mid = lo + (hi - lo) / 2;
        if (ok(mid)) { r = mid; hi = mid - 1; } else lo = mid + 1;
    }
    return r;
}

/* real version: boundary between F and T in [lo, hi]; 100 steps ~ full double precision */
static inline double bs_real(double lo, double hi, int (*ok)(double)) {
    for (int it = 0; it < 100; it++) {
        double mid = (lo + hi) / 2;
        if (ok(mid)) hi = mid; else lo = mid;
    }
    return hi;
}

/* x in [lo, hi] minimizing f, f strictly decreasing then increasing */
static inline ll ternary_min_int(ll lo, ll hi, ll (*f)(ll)) {
    while (hi - lo > 2) {
        ll m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2 - 1; else lo = m1 + 1;
    }
    ll best = lo;
    for (ll x = lo + 1; x <= hi; x++) if (f(x) < f(best)) best = x;
    return best;
}

static inline double ternary_min_real(double lo, double hi, double (*f)(double)) {
    for (int it = 0; it < 200; it++) {
        double m1 = lo + (hi - lo) / 3, m2 = hi - (hi - lo) / 3;
        if (f(m1) < f(m2)) hi = m2; else lo = m1;
    }
    return (lo + hi) / 2;
}

#endif
