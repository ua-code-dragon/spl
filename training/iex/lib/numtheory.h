/* numtheory.h - gcd, modular arithmetic, primes, factorization.
 *
 *   gcd lcm extgcd | mod_norm mulmod powmod modinv crt2
 *   sieve factor_spf factor_trial is_prime euler_phi isqrt
 */
#ifndef XT_NUMTHEORY_H
#define XT_NUMTHEORY_H
#include "common.h"

/* ---------- gcd ---------- */

static inline ll gcd(ll a, ll b) {
    while (b) { ll t = a % b; a = b; b = t; }
    return a < 0 ? -a : a;
}

static inline ll lcm(ll a, ll b) { return a / gcd(a, b) * b; }

/* returns g = gcd(a, b) and sets x, y so that a*x + b*y = g */
static inline ll extgcd(ll a, ll b, ll *x, ll *y) {
    if (b == 0) { *x = 1; *y = 0; return a; }
    ll x1, y1, g = extgcd(b, a % b, &x1, &y1);
    *x = y1;
    *y = x1 - (a / b) * y1;
    return g;
}

/* ---------- modular arithmetic ---------- */

/* a mod m in [0, m), also for negative a */
static inline ll mod_norm(ll a, ll m) { a %= m; return a < 0 ? a + m : a; }

/* (a * b) mod m, safe for any m up to 4e18 */
static inline ll mulmod(ll a, ll b, ll m) {
    a = mod_norm(a, m); b = mod_norm(b, m);
    if (m <= 3037000499LL) return a * b % m; /* product fits in 63 bits */
    return (ll)((__int128)a * b % m);
}

/* b^e mod m in O(log e) */
static inline ll powmod(ll b, ll e, ll m) {
    ll r = 1 % m;
    b = mod_norm(b, m);
    for (; e > 0; e >>= 1) {
        if (e & 1) r = mulmod(r, b, m);
        b = mulmod(b, b, m);
    }
    return r;
}

/* inverse of a modulo m, needs gcd(a, m) == 1 (m need not be prime) */
static inline ll modinv(ll a, ll m) {
    ll x, y;
    extgcd(mod_norm(a, m), m, &x, &y);
    return mod_norm(x, m);
}

/* Chinese remainder: solve x = a1 (mod m1), x = a2 (mod m2).
 * Returns 0 if impossible, else 1 with x = *a (mod *m), *m = lcm(m1, m2). */
static inline int crt2(ll a1, ll m1, ll a2, ll m2, ll *a, ll *m) {
    ll p, q, g = extgcd(m1, m2, &p, &q);
    if ((a2 - a1) % g) return 0;
    ll m2g = m2 / g;
    ll t = mulmod((a2 - a1) / g, p, m2g);
    *m = m1 / g * m2;
    *a = mod_norm(a1 + m1 * t, *m);
    return 1;
}

/* ---------- primes ---------- */

#ifndef SIEVE_MAX
#define SIEVE_MAX 1000001
#endif
static int spf[SIEVE_MAX]; /* smallest prime factor, 0 for 0 and 1 */
static int primes[SIEVE_MAX / 8 + 100]; /* all primes <= n, ascending */
static int nprimes;

/* linear sieve of Eratosthenes for 2..n, n < SIEVE_MAX. Call once. O(n) */
static inline void sieve(int n) {
    nprimes = 0;
    for (int i = 2; i <= n; i++) {
        if (!spf[i]) { spf[i] = i; primes[nprimes++] = i; }
        for (int j = 0; j < nprimes && primes[j] <= spf[i] && (ll)i * primes[j] <= n; j++)
            spf[i * primes[j]] = primes[j];
    }
}

/* n = prod p[i]^e[i], n < SIEVE_MAX, needs sieve(). Returns number of distinct primes. O(log n) */
static inline int factor_spf(int n, int *p, int *e) {
    int k = 0;
    while (n > 1) {
        int q = spf[n], c = 0;
        while (n % q == 0) { n /= q; c++; }
        p[k] = q; e[k++] = c;
    }
    return k;
}

/* same by trial division for any n up to ~1e12. O(sqrt n) */
static inline int factor_trial(ll n, ll *p, int *e) {
    int k = 0;
    for (ll q = 2; q * q <= n; q++) {
        if (n % q) continue;
        int c = 0;
        while (n % q == 0) { n /= q; c++; }
        p[k] = q; e[k++] = c;
    }
    if (n > 1) { p[k] = n; e[k++] = 1; }
    return k;
}

/* deterministic Miller-Rabin primality test for every 64-bit n */
static inline int is_prime(ull n) {
    static const ull bases[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    if (n < 2) return 0;
    for (int i = 0; i < 12; i++) {
        if (n == bases[i]) return 1;
        if (n % bases[i] == 0) return 0;
    }
    ull d = n - 1;
    int s = 0;
    while (d % 2 == 0) { d /= 2; s++; }
    for (int i = 0; i < 12; i++) {
        ull x = 1, b = bases[i], e = d;
        for (; e; e >>= 1) {
            if (e & 1) x = (ull)((unsigned __int128)x * b % n);
            b = (ull)((unsigned __int128)b * b % n);
        }
        if (x == 1 || x == n - 1) continue;
        int composite = 1;
        for (int r = 1; r < s && composite; r++) {
            x = (ull)((unsigned __int128)x * x % n);
            if (x == n - 1) composite = 0;
        }
        if (composite) return 0;
    }
    return 1;
}

/* Euler's totient: how many 1 <= k <= n are coprime to n. O(sqrt n) */
static inline ll euler_phi(ll n) {
    ll r = n;
    for (ll q = 2; q * q <= n; q++) {
        if (n % q) continue;
        while (n % q == 0) n /= q;
        r -= r / q;
    }
    if (n > 1) r -= r / n;
    return r;
}

/* floor(sqrt(n)) exactly, n >= 0 */
static inline ll isqrt(ll n) {
    ll r = (ll)__builtin_sqrtl((long double)n);
    while (r * r > n) r--;
    while ((r + 1) * (r + 1) <= n) r++;
    return r;
}

#endif
