/* combin.h - combinatorics modulo a prime and permutation utilities.
 *
 *   comb_init nCr nPr catalan lucas | next_perm nth_perm perm_cycles
 *
 * All counting is modulo COMB_MOD (a prime). Define COMB_MOD before the
 * include to change it, e.g. #define COMB_MOD 998244353LL
 */
#ifndef XT_COMBIN_H
#define XT_COMBIN_H
#include "common.h"

#ifndef COMB_MOD
#define COMB_MOD MOD
#endif
#ifndef COMB_MAX
#define COMB_MAX 1000001
#endif

static ll fact[COMB_MAX], inv_fact[COMB_MAX];

static inline ll comb_pow(ll b, ll e) {
    ll r = 1;
    b %= COMB_MOD;
    for (; e > 0; e >>= 1) {
        if (e & 1) r = r * b % COMB_MOD;
        b = b * b % COMB_MOD;
    }
    return r;
}

/* precompute n! and 1/n! for 0..n (n < COMB_MAX, n < COMB_MOD). O(n) */
static inline void comb_init(int n) {
    fact[0] = 1;
    for (int i = 1; i <= n; i++) fact[i] = fact[i - 1] * i % COMB_MOD;
    inv_fact[n] = comb_pow(fact[n], COMB_MOD - 2); /* Fermat: a^(p-2) = 1/a */
    for (int i = n; i > 0; i--) inv_fact[i - 1] = inv_fact[i] * i % COMB_MOD;
}

/* binomial coefficient C(n, r) = n! / (r! (n-r)!), 0 if r < 0 or r > n */
static inline ll nCr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[r] % COMB_MOD * inv_fact[n - r] % COMB_MOD;
}

/* ordered selections n! / (n-r)! */
static inline ll nPr(int n, int r) {
    if (r < 0 || r > n) return 0;
    return fact[n] * inv_fact[n - r] % COMB_MOD;
}

/* Catalan number C(2n, n) / (n + 1): bracket sequences, binary trees, ... */
static inline ll catalan(int n) {
    return nCr(2 * n, n) * comb_pow(n + 1, COMB_MOD - 2) % COMB_MOD;
}

/* C(n, r) mod p for huge n, r when the prime p = COMB_MOD is small (< COMB_MAX).
 * Lucas: C(n, r) = prod C(n_i, r_i) over base-p digits. Needs comb_init(p - 1). */
static inline ll lucas(ll n, ll r) {
    ll res = 1;
    while (n > 0 || r > 0) {
        res = res * nCr((int)(n % COMB_MOD), (int)(r % COMB_MOD)) % COMB_MOD;
        n /= COMB_MOD; r /= COMB_MOD;
    }
    return res;
}

/* ---------- permutations ---------- */

/* rearrange a[0..n-1] into the next lexicographic permutation.
 * Returns 0 (and leaves a sorted ascending) after the last one.
 * Usage: sort a; do { ... } while (next_perm(a, n)); */
static inline int next_perm(int *a, int n) {
    int i = n - 2;
    while (i >= 0 && a[i] >= a[i + 1]) i--;
    if (i >= 0) {
        int j = n - 1;
        while (a[j] <= a[i]) j--;
        SWAP(int, a[i], a[j]);
    }
    for (int l = i + 1, r = n - 1; l < r; l++, r--) SWAP(int, a[l], a[r]);
    return i >= 0;
}

/* k-th (0-based) permutation of 1..n in lexicographic order, n <= 20 */
static inline void nth_perm(int n, ll k, int *out) {
    ll f[21];
    int used[21] = {0};
    f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i;
    for (int i = 0; i < n; i++) {
        ll idx = k / f[n - 1 - i];
        k %= f[n - 1 - i];
        for (int v = 1; v <= n; v++)
            if (!used[v] && idx-- == 0) { out[i] = v; used[v] = 1; break; }
    }
}

/* number of cycles of a permutation p of 0..n-1.
 * Minimum swaps to sort = n - cycles; parity of p = (n - cycles) % 2. */
static inline int perm_cycles(const int *p, int n) {
    static char seen[COMB_MAX];
    int cycles = 0;
    memset(seen, 0, (size_t)n);
    for (int i = 0; i < n; i++) {
        if (seen[i]) continue;
        cycles++;
        for (int j = i; !seen[j]; j = p[j]) seen[j] = 1;
    }
    return cycles;
}

#endif
