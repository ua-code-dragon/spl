/* fft.h - fast polynomial multiplication (Number Theoretic Transform).
 *
 *   ntt poly_mul
 *
 * c = a * b means c[k] = sum a[i] * b[k-i]  (convolution) modulo 998244353.
 * Naive O(n^2), NTT O(n log n). Typical uses: counting sums of two choices,
 * generating functions (dice sums), string matching with wildcards.
 * The result length na + nb - 1 must not exceed NTT_MAX.
 */
#ifndef XT_FFT_H
#define XT_FFT_H
#include "common.h"

#ifndef NTT_MAX
#define NTT_MAX (1 << 20)
#endif
#define NTT_MOD 998244353LL /* = 119 * 2^23 + 1 */
#define NTT_G   3 /* primitive root   */

static inline ll ntt_pow(ll b, ll e) {
    ll r = 1;
    for (b %= NTT_MOD; e > 0; e >>= 1) {
        if (e & 1) r = r * b % NTT_MOD;
        b = b * b % NTT_MOD;
    }
    return r;
}

/* in-place transform of a[0..n-1], n a power of two; invert = 1 for inverse */
static inline void ntt(ll *a, int n, int invert) {
    for (int i = 1, j = 0; i < n; i++) { /* bit-reversal permutation */
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;
        if (i < j) SWAP(ll, a[i], a[j]);
    }
    for (int len = 2; len <= n; len <<= 1) {
        ll w = ntt_pow(NTT_G, (NTT_MOD - 1) / len);
        if (invert) w = ntt_pow(w, NTT_MOD - 2);
        for (int i = 0; i < n; i += len) {
            ll wn = 1;
            for (int j = 0; j < len / 2; j++) {
                ll u = a[i + j], v = a[i + j + len / 2] * wn % NTT_MOD;
                a[i + j] = u + v < NTT_MOD ? u + v : u + v - NTT_MOD;
                a[i + j + len / 2] = u - v >= 0 ? u - v : u - v + NTT_MOD;
                wn = wn * w % NTT_MOD;
            }
        }
    }
    if (invert) {
        ll inv_n = ntt_pow(n, NTT_MOD - 2);
        for (int i = 0; i < n; i++) a[i] = a[i] * inv_n % NTT_MOD;
    }
}

/* out = a * b; a has na coefficients, b has nb. Returns na + nb - 1.
 * Coefficients must be in [0, NTT_MOD). out may alias a or b. */
static inline int poly_mul(const ll *a, int na, const ll *b, int nb, ll *out) {
    static ll fa[NTT_MAX], fb[NTT_MAX];
    int need = na + nb - 1, n = 1;
    while (n < need) n <<= 1;
    memset(fa, 0, sizeof(ll) * (size_t)n);
    memset(fb, 0, sizeof(ll) * (size_t)n);
    memcpy(fa, a, sizeof(ll) * (size_t)na);
    memcpy(fb, b, sizeof(ll) * (size_t)nb);
    ntt(fa, n, 0);
    ntt(fb, n, 0);
    for (int i = 0; i < n; i++) fa[i] = fa[i] * fb[i] % NTT_MOD;
    ntt(fa, n, 1);
    memcpy(out, fa, sizeof(ll) * (size_t)need);
    return need;
}

#endif
