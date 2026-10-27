/* util.h - small helpers: random numbers, integer division, timing.
 *
 *   rng_next rng_range shuffle_int | floor_div ceil_div ipow | elapsed_sec
 */
#ifndef XT_UTIL_H
#define XT_UTIL_H
#include "common.h"
#include <time.h>

/* xorshift64 pseudo random generator (fast; not for cryptography) */
static ull rng_state = 88172645463325252ULL;

static inline void rng_seed(ull s) { rng_state = s ? s : 88172645463325252ULL; }

static inline ull rng_next(void) {
    rng_state ^= rng_state << 13;
    rng_state ^= rng_state >> 7;
    rng_state ^= rng_state << 17;
    return rng_state;
}

/* uniform integer in [lo, hi] */
static inline ll rng_range(ll lo, ll hi) { return lo + (ll)(rng_next() % (ull)(hi - lo + 1)); }

/* random permutation of a[] (Fisher-Yates) */
static inline void shuffle_int(int *a, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = (int)rng_range(0, i);
        SWAP(int, a[i], a[j]);
    }
}

/* C division truncates toward zero (-7 / 2 == -3). These round down / up, b != 0. */
static inline ll floor_div(ll a, ll b) { return a / b - ((a % b != 0) && ((a < 0) != (b < 0))); }
static inline ll ceil_div(ll a, ll b) { return a / b + ((a % b != 0) && ((a < 0) == (b < 0))); }

/* exact integer power, the caller makes sure it fits */
static inline ll ipow(ll b, int e) {
    ll r = 1;
    for (; e > 0; e >>= 1) {
        if (e & 1) r *= b;
        if (e > 1) b *= b;
    }
    return r;
}

/* seconds of CPU time since the program started (stop a search before the time limit) */
static inline double elapsed_sec(void) { return (double)clock() / CLOCKS_PER_SEC; }

#endif
