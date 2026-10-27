/* bits.h - bit manipulation, subset enumeration, XOR basis.
 *
 *   POPCOUNT CTZ LOWBIT FOR_SUBMASKS | is_pow2 log2_floor gray gray_inv
 *   sos_subsets | xb_insert xb_max xb_contains xb_rank
 */
#ifndef XT_BITS_H
#define XT_BITS_H
#include "common.h"

#define POPCOUNT(x) __builtin_popcountll((ull)(x)) /* number of 1 bits        */
#define CTZ(x)      __builtin_ctzll((ull)(x)) /* trailing zeros, x != 0  */
#define LOWBIT(x)   ((x) & -(x)) /* lowest set bit as value */
#define BIT(x, i)   (((x) >> (i)) & 1)

/* all non-empty submasks of mask, from largest to smallest.
 * Over all masks of n bits this visits 3^n pairs in total. */
#define FOR_SUBMASKS(sub, mask) for (int sub = (mask); sub > 0; sub = (sub - 1) & (mask))

static inline int is_pow2(ull x) { return x && !(x & (x - 1)); }
static inline int log2_floor(ull x) { return 63 - __builtin_clzll(x); } /* x > 0 */

/* Gray code: consecutive values differ in exactly one bit */
static inline ull gray(ull i) { return i ^ (i >> 1); }
static inline ull gray_inv(ull g) {
    ull i = 0;
    for (; g; g >>= 1) i ^= g;
    return i;
}

/* sum over subsets: f[mask] becomes sum of f[sub] over all sub of mask. O(n 2^n) */
static inline void sos_subsets(ll *f, int n) {
    for (int i = 0; i < n; i++)
        for (int mask = 0; mask < (1 << n); mask++)
            if (mask >> i & 1) f[mask] += f[mask ^ (1 << i)];
}

/* ---------- XOR linear basis (Gaussian elimination over GF(2)) ----------
 * Answers: max XOR of a subset, is x a XOR of some subset, how many distinct
 * subset XORs (= 2^rank). Usage: XorBasis b = {0}; xb_insert(&b, x); */
typedef struct { ull v[64]; int rank; } XorBasis;

/* returns 1 if x was independent (basis grew) */
static inline int xb_insert(XorBasis *b, ull x) {
    for (int i = 63; i >= 0; i--) {
        if (!(x >> i & 1)) continue;
        if (!b->v[i]) { b->v[i] = x; b->rank++; return 1; }
        x ^= b->v[i];
    }
    return 0;
}

/* maximum of start ^ (XOR of any subset) */
static inline ull xb_max(const XorBasis *b, ull start) {
    ull r = start;
    for (int i = 63; i >= 0; i--)
        if ((r ^ b->v[i]) > r) r ^= b->v[i];
    return r;
}

static inline int xb_contains(const XorBasis *b, ull x) {
    for (int i = 63; i >= 0; i--)
        if (x >> i & 1) {
            if (!b->v[i]) return 0;
            x ^= b->v[i];
        }
    return 1;
}

static inline int xb_rank(const XorBasis *b) { return b->rank; }

#endif
