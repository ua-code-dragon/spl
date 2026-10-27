/* bignum.h - non-negative big integers (C has no built-in arbitrary precision).
 *
 *   bn_from_ll bn_from_str bn_print bn_cmp
 *   bn_add bn_sub bn_mul_small bn_mul bn_div_small
 *
 * Stored in base 10^9, least significant limb first. Results may alias the
 * arguments except in bn_mul. Before reaching for big numbers check whether
 * the task only needs the answer modulo something, or a long double / log.
 */
#ifndef XT_BIGNUM_H
#define XT_BIGNUM_H
#include "common.h"

#ifndef BN_LIMBS
#define BN_LIMBS 1200 /* 1200 limbs = 10800 decimal digits */
#endif
#define BN_BASE 1000000000

typedef struct { int n; int d[BN_LIMBS]; } Big; /* zero is n = 1, d[0] = 0 */

static inline void bn_trim_(Big *a) { while (a->n > 1 && a->d[a->n - 1] == 0) a->n--; }

static inline void bn_from_ll(Big *a, ll x) {
    a->n = 0;
    do { a->d[a->n++] = (int)(x % BN_BASE); x /= BN_BASE; } while (x > 0);
}

/* from a decimal string without sign */
static inline void bn_from_str(Big *a, const char *s) {
    int len = (int)strlen(s);
    a->n = 0;
    for (int end = len; end > 0; end -= 9) { /* 9 digits per limb, from the right */
        int start = MAX(0, end - 9), v = 0;
        for (int i = start; i < end; i++) v = v * 10 + (s[i] - '0');
        a->d[a->n++] = v;
    }
    if (a->n == 0) a->d[a->n++] = 0;
    bn_trim_(a);
}

static inline void bn_print(const Big *a) {
    printf("%d", a->d[a->n - 1]);
    for (int i = a->n - 2; i >= 0; i--) printf("%09d", a->d[i]);
}

/* -1, 0, 1 like strcmp */
static inline int bn_cmp(const Big *a, const Big *b) {
    if (a->n != b->n) return a->n < b->n ? -1 : 1;
    for (int i = a->n - 1; i >= 0; i--)
        if (a->d[i] != b->d[i]) return a->d[i] < b->d[i] ? -1 : 1;
    return 0;
}

static inline void bn_add(Big *r, const Big *a, const Big *b) {
    int n = MAX(a->n, b->n), carry = 0;
    for (int i = 0; i < n; i++) {
        int s = carry + (i < a->n ? a->d[i] : 0) + (i < b->n ? b->d[i] : 0);
        carry = s >= BN_BASE;
        r->d[i] = s - (carry ? BN_BASE : 0);
    }
    r->n = n;
    if (carry) r->d[r->n++] = 1;
}

/* r = a - b, requires a >= b */
static inline void bn_sub(Big *r, const Big *a, const Big *b) {
    int borrow = 0;
    for (int i = 0; i < a->n; i++) {
        int s = a->d[i] - borrow - (i < b->n ? b->d[i] : 0);
        borrow = s < 0;
        r->d[i] = s + (borrow ? BN_BASE : 0);
    }
    r->n = a->n;
    bn_trim_(r);
}

/* r = a * m, 0 <= m < 2^31 */
static inline void bn_mul_small(Big *r, const Big *a, int m) {
    ll carry = 0;
    int n = a->n;
    for (int i = 0; i < n; i++) {
        ll cur = (ll)a->d[i] * m + carry;
        r->d[i] = (int)(cur % BN_BASE);
        carry = cur / BN_BASE;
    }
    r->n = n;
    while (carry) { r->d[r->n++] = (int)(carry % BN_BASE); carry /= BN_BASE; }
    bn_trim_(r);
}

/* r = a * b, r must differ from a and b. O(n m) */
static inline void bn_mul(Big *r, const Big *a, const Big *b) {
    static ull t[2 * BN_LIMBS];
    int n = a->n + b->n;
    memset(t, 0, sizeof(ull) * (size_t)n);
    for (int i = 0; i < a->n; i++) {
        ull carry = 0;
        for (int j = 0; j < b->n; j++) {
            ull cur = t[i + j] + (ull)a->d[i] * (ull)b->d[j] + carry;
            t[i + j] = cur % BN_BASE;
            carry = cur / BN_BASE;
        }
        for (int k = i + b->n; carry; k++) {
            ull cur = t[k] + carry;
            t[k] = cur % BN_BASE;
            carry = cur / BN_BASE;
        }
    }
    for (int i = 0; i < n; i++) r->d[i] = (int)t[i];
    r->n = n;
    bn_trim_(r);
}

/* r = a / m, returns a % m; 0 < m < 2^31 */
static inline int bn_div_small(Big *r, const Big *a, int m) {
    ll rem = 0;
    for (int i = a->n - 1; i >= 0; i--) {
        ll cur = a->d[i] + rem * BN_BASE;
        r->d[i] = (int)(cur / m);
        rem = cur % m;
    }
    r->n = a->n;
    bn_trim_(r);
    return (int)rem;
}

#endif
