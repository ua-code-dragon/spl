/* matrix.h - matrix power (linear recurrences) and Gaussian elimination.
 *
 *   mat_ident mat_mul mat_pow | gauss_mod gauss_double
 *
 * Fibonacci-like recurrences f(n) = c1 f(n-1) + ... + ck f(n-k) for huge n:
 * build the k x k "companion" matrix M and compute M^n in O(k^3 log n).
 */
#ifndef XT_MATRIX_H
#define XT_MATRIX_H
#include "common.h"

#ifndef MAT_N
#define MAT_N 32 /* maximal dimension */
#endif
#define MAT_W (MAT_N + 1) /* row width for augmented systems [A | b] */

typedef struct { int n; ll a[MAT_N][MAT_N]; } Mat;

static inline Mat mat_ident(int n) {
    Mat r;
    memset(&r, 0, sizeof r);
    r.n = n;
    for (int i = 0; i < n; i++) r.a[i][i] = 1;
    return r;
}

/* x * y mod m (entries must already be in [0, m), m < 3e9) */
static inline Mat mat_mul(const Mat *x, const Mat *y, ll m) {
    Mat r;
    memset(&r, 0, sizeof r);
    r.n = x->n;
    for (int i = 0; i < r.n; i++)
        for (int k = 0; k < r.n; k++) {
            ll v = x->a[i][k];
            if (v == 0) continue;
            for (int j = 0; j < r.n; j++) r.a[i][j] = (r.a[i][j] + v * y->a[k][j]) % m;
        }
    return r;
}

/* b^e mod m by fast exponentiation */
static inline Mat mat_pow(Mat b, ll e, ll m) {
    Mat r = mat_ident(b.n);
    for (; e > 0; e >>= 1) {
        if (e & 1) r = mat_mul(&r, &b, m);
        b = mat_mul(&b, &b, m);
    }
    return r;
}

static inline ll gauss_pow(ll b, ll e, ll p) {
    ll r = 1;
    for (b %= p; e > 0; e >>= 1) {
        if (e & 1) r = r * b % p;
        b = b * b % p;
    }
    return r;
}

/* Gaussian elimination modulo a prime p on a rows x cols matrix (entries in [0,p)).
 * Brings a[][] to reduced row echelon form, returns the rank.
 * If det != NULL and rows == cols it receives the determinant mod p.
 * Linear system A x = b: put b in column n (cols = n + 1); if rank of the first
 * n columns is n then x[i] = a[i][n]. O(rows * cols * min(rows, cols)) */
static inline int gauss_mod(ll a[][MAT_W], int rows, int cols, ll p, ll *det) {
    int rank = 0;
    ll d = 1;
    for (int c = 0; c < cols && rank < rows; c++) {
        int piv = -1;
        for (int r = rank; r < rows; r++) if (a[r][c]) { piv = r; break; }
        if (piv < 0) { d = 0; continue; }
        if (piv != rank) {
            for (int j = 0; j < cols; j++) SWAP(ll, a[piv][j], a[rank][j]);
            d = (p - d) % p; /* a row swap flips the sign */
        }
        d = d * a[rank][c] % p;
        ll inv = gauss_pow(a[rank][c], p - 2, p);
        for (int j = 0; j < cols; j++) a[rank][j] = a[rank][j] * inv % p;
        for (int r = 0; r < rows; r++) {
            if (r == rank || a[r][c] == 0) continue;
            ll f = a[r][c];
            for (int j = 0; j < cols; j++) a[r][j] = ((a[r][j] - f * a[rank][j]) % p + p) % p;
        }
        rank++;
    }
    if (det) *det = (rank == rows && rows == cols) ? d : 0;
    return rank;
}

/* the same with doubles and partial pivoting; values below eps count as zero */
static inline int gauss_double(double a[][MAT_W], int rows, int cols, double eps) {
    int rank = 0;
    for (int c = 0; c < cols && rank < rows; c++) {
        int piv = rank;
        for (int r = rank; r < rows; r++)
            if (__builtin_fabs(a[r][c]) > __builtin_fabs(a[piv][c])) piv = r;
        if (__builtin_fabs(a[piv][c]) < eps) continue;
        for (int j = 0; j < cols; j++) SWAP(double, a[piv][j], a[rank][j]);
        double inv = 1.0 / a[rank][c];
        for (int j = 0; j < cols; j++) a[rank][j] *= inv;
        for (int r = 0; r < rows; r++) {
            if (r == rank) continue;
            double f = a[r][c];
            for (int j = 0; j < cols; j++) a[r][j] -= f * a[rank][j];
        }
        rank++;
    }
    return rank;
}

#endif
