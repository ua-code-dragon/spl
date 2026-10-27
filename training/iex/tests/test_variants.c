/* test_variants.c - the configurable parts: SEG_OP = min, SP_OP = max,
 * COMB_MOD = small prime (Lucas) and io.h on stdin.
 * Run:  printf '3 -5 hello\nrest of line\n' | ./a.out
 */
#define SEG_OP(a, b) ((a) < (b) ? (a) : (b))
#define SEG_ID LINF
#define SP_OP(a, b) ((a) > (b) ? (a) : (b))
#define COMB_MOD 13LL
#define COMB_MAX 100
#include "segtree.h"
#include "sparse.h"
#include "combin.h"
#include "io.h"
#include "util.h"

static int fails, checks;
#define CHECK(cond) do { checks++; if (!(cond)) { fails++; printf("FAIL line %d: %s\n", __LINE__, #cond); } } while (0)

int main(void) {
    static ll a[300];
    int n = 300;
    for (int i = 0; i < n; i++) a[i] = rng_range(-1000, 1000);
    seg_init(n, a);
    sp_build(a, n);
    for (int q = 0; q < 2000; q++) {
        int i = (int)rng_range(0, n - 1);
        if (q % 2) { a[i] = rng_range(-1000, 1000); seg_set(i, a[i]); }
        int l = (int)rng_range(0, n - 1), r = (int)rng_range(l, n - 1);
        ll mn = LINF;
        for (int j = l; j <= r; j++) mn = MIN(mn, a[j]);
        CHECK(seg_query(l, r) == mn);
    }
    sp_build(a, n);
    for (int q = 0; q < 2000; q++) {
        int l = (int)rng_range(0, n - 1), r = (int)rng_range(l, n - 1);
        ll mx = -LINF;
        for (int j = l; j <= r; j++) mx = MAX(mx, a[j]);
        CHECK(sp_query(l, r) == mx);
    }
    comb_init(12);
    /* C(1000, 300) mod 13 by Pascal's triangle */
    static ll C[1001][1001];
    for (int i = 0; i <= 1000; i++)
        for (int j = 0; j <= i; j++) C[i][j] = (j == 0 || j == i) ? 1 : (C[i - 1][j - 1] + C[i - 1][j]) % 13;
    int ok = 1;
    for (int i = 0; i <= 1000; i += 7)
        for (int j = 0; j <= i; j += 3) ok &= lucas(i, j) == C[i][j];
    CHECK(ok);

    char w[100], line[100];
    CHECK(read_int() == 3);
    CHECK(read_ll() == -5);
    CHECK(read_word(w) == 5 && strcmp(w, "hello") == 0);
    CHECK(read_line(line) == 0);                 /* remainder of the "hello" line */
    CHECK(read_line(line) == 12 && strcmp(line, "rest of line") == 0);
    CHECK(read_line(line) == -1 && read_word(w) == 0);
    printf("%d checks, %d failed\n", checks, fails);
    return fails != 0;
}
